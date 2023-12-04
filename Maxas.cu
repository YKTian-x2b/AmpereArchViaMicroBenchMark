#include "../Common.cuh"
#include <cuda_runtime.h>
#include <iostream>
#include <random>
#include <ctime>
#include "cublas_v2.h"

#include <device_functions.h>
#include <device_launch_parameters.h>
#include <cuda_texture_types.h>
#include <texture_fetch_functions.h>

// 四元向量加载 要求数据是 4 word alignment  这至少要求lda ldb是被四整除的 
// 缓存性能由L2 主导
typedef texture<float4, cudaTextureType1D, cudaReadModeElementType> floatTex;

floatTex  texA(0, cudaFilterModePoint, cudaAddressModeBorder);
floatTex  texB(0, cudaFilterModePoint, cudaAddressModeBorder);

// track registers用来持有纹理加载索引 这将削减主循环里半数的整数加法指令数量 提高FFMA和非FFMA指令的比例 这是使用纹理内存的主要优点
// 还需要额外4个单独的track变量来避免纹理加载间的 Idx*2 依赖屏障 这不会产生额外的IADD指令，只需要3个额外的寄存器
// 另外 纹理内存的使用让我们无需担心全局内存加载的越界问题，代码更简单；而且同样的代码还能加载半精度和更小精度的应用（!!!)

// STS.128指令会造成bank冲突，这不可避免且不会影响性能，因为 批加载和向量存储是 a net win
// bank冲突导致的指令reply可能与FFMA 双发

// 4 vec4 4 byte loads per thread per loop 
__global__ void sgemm_kernel_64(float *C,
	const int m,   const int n,   const int k,
	const int lda, const int ldb, const int ldc,
	float alpha, int *D)
{
    int tid = threadIdx.x;
    int bx = blockIdx.x;
    int by = blockIdx.y;
    // 前32个线程处理A 后32个线程处理B
    // 列存A的lda是x维 行存B的ldb是y维
    int blk = tid >= 32 ? by : bx;
    int ldx = tid >= 32 ? ldb/4 : lda/4;
    floatTex tex = tid >= 32 ? texB : texA;

    // warpid 0前1后
    int tid2 = (tid>>4)&1;
    // laneid
    int tid15 = tid & 15;
    // tex的索引
    int track0 = blk*64/4 + tid15 + (ldx * tid2);
    int track2 = track0 + ldx * 2;
    int track4 = track0 + ldx * 4;
    int track6 = track0 + ldx * 6;
    // 
    int end = track0 + (k-8)*ldx;
    // write Shared
    int writeS = tid15*4*4 + tid2*64*4;
    int writeS += tid >= 32 ? 2048 : 0;

    while(track0 < end){
        // load tex store shared
        tex.1d.v4.f32.s32 loadX0, [tex, track0];
        tex.1d.v4.f32.s32 loadX2, [tex, track2];
        tex.1d.v4.f32.s32 loadX4, [tex, track4];
        tex.1d.v4.f32.s32 loadX6, [tex, track6];

        st.shared.v4.f32 [writeS + 4*0*64], loadX0;
        st.shared.v4.f32 [writeS + 4*2*64], loadX2;
        st.shared.v4.f32 [writeS + 4*4*64], loadX4;
        st.shared.v4.f32 [writeS + 4*6*64], loadX6;

        bar.sync 0;

        track0 += ldx * 8;
        track2 += ldx * 8;
        track4 += ldx * 8;
        track6 += ldx * 8;
        // 切buffer
        writeS ^= 4*16*64;
    }

    // 1111,1111 ~ 0000,0000   ----,xyz- => 0xyz,0000
    int readAs = ((tid >> 1) & 7) << 4;
    // ((tid & 0x30) >> 3):  0011,0000 --ab,---c => 00ab,0000 => 0000,0ab0 
    // (((tid & 0x30) >> 3) | (tid & 1)):  --ab,---c => 0000,000c => 0000,0abc 
    // (((tid & 0x30) >> 3) | (tid & 1)) << 4:  0abc,0000
    // +2048:  1000,0000,0000 => 1000,0abc,0000
    int readBs = (((tid & 0x30) >> 3) | (tid & 1)) << 4 + 2048;
    // --ab,xyzc readAs=0xyz,0000 readBs=1000,0abc,0000

    while(track0 < end){
        for(j = 0; j < 8; j++){
            // 计算当前行的时候预取后一行 最后一行换到第一行
            int prefetch = (j+1) % 8;
            // 双缓冲用奇偶行来实现
            if(j & 1){
                ld.shared.v4.f32 j0Ax00, [readAs + 4*(prefetch*64+0)];
                ld.shared.v4.f32 j0By00, [readBs + 4*(prefetch*64+0)];
                ld.shared.v4.f32 j0Ax32, [readAs + 4*(prefetch*64+32)];
                ld.shared.v4.f32 j0By32, [readBs + 4*(prefetch*64+32)];
            }
            else{
                ld.shared.v4.f32 j1Ax00, [readAs + 4*(prefetch*64+0)];
                ld.shared.v4.f32 j1By00, [readBs + 4*(prefetch*64+0)];
                ld.shared.v4.f32 j1Ax32, [readAs + 4*(prefetch*64+32)];
                ld.shared.v4.f32 j1By32, [readBs + 4*(prefetch*64+32)];
            }
        }
        // 2048
        readAs ^= 4*16*64;
        readBs ^= 4*16*64;
    }
    // 操作数重用缓存的每个源操作数槽有8个字节的数据。像FFMA这样的指令有3个源操作数插槽。
    // 每次发出指令时，都有一个标志可用于指定是否将再次使用每个操作数。
    // 因此，在同一操作数插槽中使用相同寄存器的下一条指令将不必转到寄存器库来获取其值。使用此功能，您可以看到如何避免寄存器bank冲突
    // 通过显式选择寄存器，可以通过operand reuse cache来避免register bank conflict
    // ptxas在避免reg bank conflict方面做得很好但不够完美，涉及向量指令的时候做的很差

    // 0-63 to be the C registers
    // 64-71 and 80-87 to be the double buffered blocking registers for matrix A
    // 72-79 and 88-95 to be the double buffered blocking registers for matrix B
    
}


int main(){
    
    dim3 blockSize(64);
    dim3 gridSize(Y/64, X/64);
    sgemm_kernel_64<<<gridSize, blockSize>>>();
}