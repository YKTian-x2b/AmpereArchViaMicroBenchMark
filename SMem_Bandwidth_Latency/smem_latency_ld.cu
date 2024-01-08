#include "helper_cuda.h"
#include "cuptr.hpp"
#include "hostptr.hpp"

#include <iostream>
#include <cstdio>
#include <cstdint>

#include <cuda_runtime.h>
#include <cuda.h>

#define GRD_SIZE 1
// 这里BLK_SIZE取32,结果也相同，我感觉跟 L1Cache和SharedMemory 取数据的方式有关系，一个按bank，一个按cacheline。
#define BLK_SIZE 16
#define UNROLL 50
#define WARMUP 100

// SMem(ld/st): 23/19 Cycles
__global__ void smem_ld_latency_test_kernel(uint32_t *startClk, uint32_t *stopClk, uint32_t *out){
    __shared__ uint32_t Arr[BLK_SIZE];
    int tid = threadIdx.x;
    uint32_t start, stop;
    
    // Arr[tid] = ((tid + BLK_SIZE/2) % BLK_SIZE) * sizeof(uint32_t);
    Arr[tid] = tid * sizeof(uint32_t);

    uint32_t arr_addr;
    // 之所以能64位强转32位，是因为共享内存是靠偏移量访问的（多次共享内存的分配是连续的）。
    // 声明一个64位寄存器u64addr，将通用地址转换为指向共享内存空间的指针并赋值给该寄存器，截断高位。
    asm volatile (
        "{.reg .u64 u64addr;\n"
        " cvta.to.shared.u64 u64addr, %1;\n"
        " cvt.u32.u64 %0, u64addr;}\n"
        : "=r"(arr_addr)
        : "l"(Arr + tid)
    );

    asm volatile ("bar.sync 0;");
    asm volatile ("mov.u32 %0, %%clock;" :"=r"(start) :: "memory");
    
    #pragma unroll
    for(int i = 0; i < UNROLL; i++){
        asm volatile (
            "ld.shared.b32 %0, [%0];\n"
            : "+r"(arr_addr) : : "memory"
        );
    }
 
    asm volatile ("mov.u32 %0, %%clock;" : "=r"(stop) :: "memory");

    startClk[tid] = start;
    stopClk[tid] = stop;
    out[tid] = arr_addr;
}

void doLoadTest(){
    CuPtr<uint32_t> out_d(BLK_SIZE);
    CuPtr<uint32_t> startClk_d(BLK_SIZE);
    CuPtr<uint32_t> stopClk_d(BLK_SIZE);
    // warmup
    for (int i = 0; i < WARMUP; i++) {
        smem_ld_latency_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr());
    }
    cudaDeviceSynchronize();
    // run
    smem_ld_latency_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr());
    cudaDeviceSynchronize();

    HostPtr<uint32_t> startClk_h;
    HostPtr<uint32_t> stopClk_h;
    startClk_d.ToHostPtr(startClk_h);
    stopClk_d.ToHostPtr(stopClk_h);

    double clockCycles = stopClk_h(0) - startClk_h(0);
    clockCycles /= UNROLL;

    printf("shared memory load latency: %lf cycles\n", clockCycles);
}

int main(){
    doLoadTest();
}

// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/smem_latency_ld smem_latency_ld.cu

// nvcc --keep --keep-dir latency_midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/smem_latency_ld smem_latency_ld.cu
// cuasm --bin2asm latency_midRes/smem_latency_ld.sm_86.cubin -o latency_midRes/smem_latency_ld.sm_86.cuasm


// UNROLL500次的ld结果是：22.9620 约等于 23 个时钟周期