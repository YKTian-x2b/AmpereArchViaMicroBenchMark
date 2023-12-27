#include "cuptr.hpp"
#include "hostptr.hpp"
#include "helper_cuda.h"

#include <cuda_runtime.h>
#include <cuda.h>
#include <iostream>
#include <cstdio>

#define GRD_SIZE 1
// 16*8=128字节
// 这里的BLK_SIZE最大是16，取32就会使测试结果从33cycles变为35cycles。可能是因为两次L1事务中间需要间隔2个cycle吗？
// 结合L1的吞吐峰值是一个cycle64B，那么发射指令之后的两个cycle就会读两次64B作为一个整体结束，然后再读两次64B作为一个整体结束吗？
// 所以结束的时间点是按 每两次读取完全结束的时间算的，这两次就叫 一个transaction 吗？
#define BLK_SIZE 16
// [10, 50, 100, 200, 400] 别超过L0_I-Cache 都可以试试 结果差不多
#define UNROLL 10
#define WARM_UP 100

__global__ void l1Cache_latency_test_kernel(uint32_t *startClk, uint32_t *stopClk, void **out, void **arr){
    int tid = threadIdx.x;
    void **ldg_ptr = arr + tid;

    // fill in l1 cache
    for(int i = 0; i < UNROLL; i++){
        asm volatile (
            "ld.global.ca.nc.b64 %0, [%0];\n"
            : "+l"(ldg_ptr)
            : : "memory"
        );
    }

    uint32_t start, stop;
    asm volatile ("bar.sync 0;");
    asm volatile ("mov.u32 %0, %%clock;" :"=r"(start) :: "memory");

    #pragma unroll
    for(int i = 0; i < UNROLL; i++){
        asm volatile (
            "ld.global.ca.nc.b64 %0, [%0];\n"
            : "+l"(ldg_ptr)
            : : "memory"
        );
    }
    
    // 不用同步的原因有三：只有一个warp；保持kernel的sass干净；latency只需测本warp的时间间隔，不需要整个SM/Block的性能；
    asm volatile ("mov.u32 %0, %%clock;" : "=r"(stop) :: "memory");

    startClk[tid] = start;
    stopClk[tid] = stop;
    if(ldg_ptr == nullptr){
        *out = ldg_ptr;
    }
}

int main(){
    // 为了非常精准的测试latency，理想情况需要，两个计时clock之间，全都是背靠背的访存指令
    // 所以这里除了要用pointerChase，还要让读取结果直接就是指针，而不是偏移量，移除掉指针计算的那条指令
    // 太精彩了写的
    CuPtr<void*> arr_d(BLK_SIZE);
    HostPtr<void*> arr_h(BLK_SIZE);
    void **h_ptr = arr_h.GetPtr();
    void **d_ptr = arr_d.GetPtr();
    for(int i = 0; i < BLK_SIZE; i++){
        h_ptr[i] = (void*)(d_ptr + i);
    }
    uint32_t arrBytes = BLK_SIZE * sizeof(void*);
    checkCudaErrors(cudaMemcpy(d_ptr, h_ptr, arrBytes, cudaMemcpyHostToDevice));

    CuPtr<void*> out_d(BLK_SIZE);
    CuPtr<uint32_t> startClk_d(BLK_SIZE);
    CuPtr<uint32_t> stopClk_d(BLK_SIZE);

    // warmup i-cache
    for(int i = 0; i < WARM_UP; i++){
        l1Cache_latency_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr(), arr_d.GetPtr());
    }
    cudaDeviceSynchronize();

    // 
    l1Cache_latency_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr(), arr_d.GetPtr());
    cudaDeviceSynchronize();

    HostPtr<uint32_t> startClk_h;
    HostPtr<uint32_t> stopClk_h;
    startClk_d.ToHostPtr(startClk_h);
    stopClk_d.ToHostPtr(stopClk_h);

    double clockCycles = stopClk_h(0) - startClk_h(0);
    clockCycles /= UNROLL;
    std::cout << "l1 cache access latency: " << clockCycles << " cycles" << std::endl;
}

// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/l1Cache_latency_my l1Cache_latency_my.cu

// nvcc --keep --keep-dir midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/l1Cache_latency_my l1Cache_latency_my.cu
// cuasm --bin2asm midRes/l1Cache_latency_my.sm_86.cubin midRes/l1Cache_latency_my.sm_86.cuasm

// l1 cache access latency: 33 cycles