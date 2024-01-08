#include "cuptr.hpp"
#include "hostptr.hpp"
#include "helper_cuda.h"

#include <cuda_runtime.h>
#include <cuda.h>
#include <iostream>
#include <cstdio>

#define GRD_SIZE 1
#define BLK_SIZE 32
#define UNROLL 10
#define WARM_UP 100

__global__ void l2Cache_latency_test_kernel(uint32_t *startClk, uint32_t *stopClk, void **out, void **arr){
    int tid = threadIdx.x;
    void ** ldg_ptr = arr + tid;

    // pupulate L2 TLB
    asm volatile (
        "ld.global.cg.b64 %0, [%0];\n"
        : "+l"(ldg_ptr)
        : : "memory"
    );


    uint32_t start, stop;
    asm volatile ("bar.sync 0;");
    asm volatile ("mov.u32 %0, %%clock;" :"=r"(start) :: "memory");

    #pragma unroll
    for(int i = 0; i < UNROLL; i++){
        asm volatile (
            "ld.global.cg.b64 %0, [%0];\n"
            : "+l"(ldg_ptr)
            : : "memory"
        );
    }  
    
    asm volatile ("mov.u32 %0, %%clock;" : "=r"(stop) :: "memory");

    startClk[tid] = start;
    stopClk[tid] = stop;

    if(ldg_ptr == nullptr){
        *out = ldg_ptr;
    }
}

int main(){
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

    // warmup i-cache and l2 cache
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

    double clockCycles = stopClk_h(0) - startClk_h(0);
    clockCycles /=  UNROLL;
    std::cout << "l2 cache access latency: " << clockCycles << " cycles" << std::endl;
}

// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/l2Cache_latency_my l2Cache_latency_my.cu

// nvcc --keep --keep-dir midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/l2Cache_latency_my l2Cache_latency_my.cu
// cuasm --bin2asm midRes/l2Cache_latency_my.sm_86.cubin midRes/l2Cache_latency_my.sm_86.cuasm

// l2 cache access latency: 221.9 cycles