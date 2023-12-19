#include "helper_cuda.h"
#include "hostptr.hpp"
#include "cuptr.hpp"
#include <cuda.h>
#include <cuda_runtime.h>
#include <iostream>
#include <cstdio>

#define GRD_SIZE 1
#define BLK_SIZE 32
#define WARM_UP 100
#define UNROLL 10
#define ARR_SIZE 1024 * 256
#define STRIDE 16

__device__ __forceinline__
uint32_t ldg_cg(const void *ptr){
    uint32_t ret;
    asm volatile(
        "ld.global.cg.b32 %0, [%1];\n\t"
        : "=r"(ret)
        : "l"(ptr)
        : "memory"
    );
    return ret;
}

__global__ void l2Cache_latency_test_kernel(uint32_t *startClk, uint32_t *stopClk, uint32_t *out, uint32_t* arr){
    int tid = threadIdx.x;
    uint32_t offset = tid;
    uint32_t start, stop;

    // pupulate L2 TLB
    offset = ldg_cg(arr+offset);

    asm volatile (
        "bar.sync 0;\n"
        "mov.u32 %0, %%clock;\n"
        : "=r"(start) : : "memory"
    );

    #pragma unroll
    for(int i = 0; i < UNROLL; i++){
        offset = ldg_cg(arr+offset);
    }

    asm volatile (
        "bar.sync 0;\n"
        "mov.u32 %0, %%clock;\n"
        : "=r"(stop) : : "memory"
    );

    startClk[tid] = start;
    stopClk[tid] = stop;

    if(offset == ~0x0){
        *out = offset;
    }
}

int main(){
    HostPtr<uint32_t> arr_h(ARR_SIZE);
    uint32_t *arr_ptr = arr_h.GetPtr();
    for(int i = 0; i < ARR_SIZE; i++){
        arr_ptr[i] = (i + STRIDE) % ARR_SIZE;
    }
    CuPtr<uint32_t> arr_d(arr_h);

    CuPtr<uint32_t> out_d(BLK_SIZE);
    CuPtr<uint32_t> startClk_d(BLK_SIZE);
    CuPtr<uint32_t> stopClk_d(BLK_SIZE);

    // pupulate l0/l1 i-cache  l2 d-cache
    for(int i = 0; i < WARM_UP; i++){
        l2Cache_latency_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr(), arr_d.GetPtr());
    }
    cudaDeviceSynchronize();

    // 
    l2Cache_latency_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr(), arr_d.GetPtr());
    cudaDeviceSynchronize();

    HostPtr<uint32_t> startClk_h;
    HostPtr<uint32_t> stopClk_h;
    startClk_d.ToHostPtr(startClk_h);
    stopClk_d.ToHostPtr(stopClk_h);

    double clockCycles_avg = 0.0;
    for(int i = 0; i < BLK_SIZE; i++){
        // std::cout << startClk_h(i) << " " << stopClk_h(i) << std::endl;
        clockCycles_avg += stopClk_h(i) - startClk_h(i);
    }
    clockCycles_avg /= (BLK_SIZE*UNROLL);

    printf("l2 cache load latency: %lf cycles\n", clockCycles_avg);
}

// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/l2Cache_latency_my l2Cache_latency_my.cu

// nvcc --keep --keep-dir midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/l2Cache_latency_my l2Cache_latency_my.cu
// cuasm --bin2asm midRes/l2Cache_latency_my.sm_86.cubin midRes/l2Cache_latency_my.sm_86.cuasm