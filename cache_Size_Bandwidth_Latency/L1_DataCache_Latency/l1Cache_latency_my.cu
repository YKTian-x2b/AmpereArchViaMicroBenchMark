#include "cuptr.hpp"
#include "hostptr.hpp"
#include "helper_cuda.h"

#include <cuda_runtime.h>
#include <cuda.h>
#include <iostream>
#include <cstdio>

#define GRD_SIZE 1
#define BLK_SIZE 4
#define UNROLL 50
#define WARM_UP 100

__global__ void l1Cache_latency_test_kernel(uint32_t *startClk, uint32_t *stopClk, void **out, void **arr){
    int tid = threadIdx.x;
    void ** ldg_ptr = arr + tid;

    // fill in l1 cache
    for(int i = 0; i < UNROLL; i++){
        // asm volatile (
        //     "ld.global.ca.b64 %0, [%0];\n"
        //     : "+l"(ldg_ptr)
        //     : : "memory"
        // );
        asm volatile (
            "ld.global.nc.b64 %0, [%0];\n"
            : "+l"(ldg_ptr)
            : : "memory"
        );
    }

    uint32_t start, stop;
    asm volatile ("bar.sync 0;");
    asm volatile ("mov.u32 %0, %%clock;" :"=r"(start) :: "memory");

    #pragma unroll
    for(int i = 0; i < UNROLL; i++){
        // asm volatile (
        //     "ld.global.ca.b64 %0, [%0];\n"
        //     : "+l"(ldg_ptr)
        //     : : "memory"
        // );
        asm volatile (
            "ld.global.nc.b64 %0, [%0];\n"
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

    double clockCycles_avg = 0.0;
    for(int i = 0; i < BLK_SIZE; i++){
        // std::cout << startClk_h(i) << " " << stopClk_h(i) << std::endl;
        clockCycles_avg += stopClk_h(i) - startClk_h(i);
    }
    clockCycles_avg /= (BLK_SIZE * UNROLL);
    std::cout << "l1 cache access latency: " << clockCycles_avg << " cycles" << std::endl;
}

// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/l1Cache_latency_my l1Cache_latency_my.cu

// nvcc --keep --keep-dir midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/l1Cache_latency_my l1Cache_latency_my.cu
// cuasm --bin2asm midRes/l1Cache_latency_my.sm_86.cubin midRes/l1Cache_latency_my.sm_86.cuasm

// l1 cache access latency: 33 cycles