#include "cuptr.hpp"
#include "hostptr.hpp"
#include "helper_cuda.h"
#include "flushL2.cuh"

#include <cuda_runtime.h>
#include <cuda.h>
#include <iostream>
#include <cstdio>

#define GRD_SIZE 1
#define BLK_SIZE 32
#define UNROLL 10
#define WARM_UP 100
#define STRIDE 1

__device__ __forceinline__
void ldg_cv(void **&ldg_ptr) {
    asm volatile (
        "ld.global.cv.b64 %0, [%0];\n"
        : "+l"(ldg_ptr)
        : : "memory"
    );
}

__device__ __forceinline__
void ldg_cg(void **&ldg_ptr) {
    asm volatile (
        "ld.global.cg.b64 %0, [%0];\n"
        : "+l"(ldg_ptr)
        : : "memory"
    );
}

__device__ __forceinline__
void ldg_ca(void **&ldg_ptr) {
    asm volatile (
        "ld.global.ca.b64 %0, [%0];\n"
        : "+l"(ldg_ptr)
        : : "memory"
    );
}


__global__ void gloMem_latency_test_kernel(uint32_t *startClk, uint32_t *stopClk, void **out, void **arr){
    int tid = threadIdx.x;
    void ** ldg_ptr = arr + tid;

    // pupulate L2 TLB
    ldg_ca(ldg_ptr);

    uint32_t start, stop;
    asm volatile ("bar.sync 0;");
    asm volatile ("mov.u32 %0, %%clock;" :"=r"(start) :: "memory");

    #pragma unroll
    for(int i = 0; i < UNROLL; i++){
        ldg_ca(ldg_ptr);
    }  
    
    asm volatile ("mov.u32 %0, %%clock;" : "=r"(stop) :: "memory");

    startClk[tid] = start;
    stopClk[tid] = stop;

    if(ldg_ptr == nullptr){
        *out = ldg_ptr;
    }
}

int main(){
    // 得保证ARR_SIZE至少是BLK_SIZE 设置最小为128个元素
    const uint32_t min_arr_size = 128;
    const uint32_t ARR_SIZE = max(min_arr_size, (UNROLL + 2) * STRIDE);
    CuPtr<void*> arr_d(ARR_SIZE);
    HostPtr<void*> arr_h(ARR_SIZE);
    void **h_ptr = arr_h.GetPtr();
    void **d_ptr = arr_d.GetPtr();
    for(int i = 0; i < ARR_SIZE; i++){
        uint32_t offset = (i + STRIDE) % ARR_SIZE;
        h_ptr[i] = (void*)(d_ptr + offset);
    }
    uint32_t arrBytes = ARR_SIZE * sizeof(void*);
    checkCudaErrors(cudaMemcpy(d_ptr, h_ptr, arrBytes, cudaMemcpyHostToDevice));

    CuPtr<void*> out_d(BLK_SIZE);
    CuPtr<uint32_t> startClk_d(BLK_SIZE);
    CuPtr<uint32_t> stopClk_d(BLK_SIZE);

    // warmup i-cache
    for(int i = 0; i < WARM_UP; i++){
        gloMem_latency_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr(), arr_d.GetPtr());
    }
    cudaDeviceSynchronize();

    // flush_l2();

    // 
    gloMem_latency_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr(), arr_d.GetPtr());
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
    clockCycles_avg /= (BLK_SIZE * UNROLL);
    std::cout << "Global Memory access latency: " << clockCycles_avg << " cycles" << std::endl;
}

// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/globalMem_latency_my5 globalMem_latency_my5.cu

// nvcc --keep --keep-dir latency_midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/globalMem_latency_my5 globalMem_latency_my5.cu
// cuasm --bin2asm latency_midRes/globalMem_latency_my5.sm_86.cubin -o latency_midRes/globalMem_latency_my5.sm_86.cuasm