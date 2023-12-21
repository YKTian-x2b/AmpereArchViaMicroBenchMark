#include "helper_cuda.h"
#include "hostptr.hpp"
#include "cuptr.hpp"
#include "flushL2.cuh"

#include <cuda.h>
#include <cuda_runtime.h>
#include <iostream>
#include <cstdio>

#define GRD_SIZE 1
#define BLK_SIZE 32
// 【10, 50, 100]
#define UNROLL 50
// STRIDE 应该比 L2 cacheline 大，避免l2缓存命中。同时应该保证数组能让BLK_SIZE个线程访问
// Turing T4的cacheline是64字节
// latency会随着STRIDE的增大而增大
#define STRIDE 128

__device__ __forceinline__
void ldg_ca(void **&ldg_ptr) {
    asm volatile (
        "ld.global.ca.b64 %0, [%0];\n"
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

__global__ void gloMem_latency_test_kernel(uint32_t *startClk, uint32_t *stopClk, void **out, void **arr){
    int tid = threadIdx.x;
    void **ldg_ptr = arr +  tid;
    // populate L2 TLB
    ldg_cg(ldg_ptr);

    uint32_t start, stop;
    asm volatile ("bar.sync 0;");
    asm volatile ("mov.u32 %0, %%clock;" :"=r"(start) :: "memory");

    #pragma unroll
    for(int i = 0; i < UNROLL; i++){
        ldg_cg(ldg_ptr);
    }

    asm volatile ("mov.u32 %0, %%clock;" : "=r"(stop) :: "memory");

    startClk[tid] = start;
    stopClk[tid] = stop;

    if(ldg_ptr == nullptr){
        *out = ldg_ptr;
    }
}

double doTest(){
    uint32_t ARR_SIZE = (UNROLL + 2) * STRIDE;

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

    // pupulate l0/l1 i-cache
    gloMem_latency_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr(), d_ptr);

    // flush L2 cache
    flush_l2();

    // 
    gloMem_latency_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr(), d_ptr);
    cudaDeviceSynchronize();

    HostPtr<uint32_t> startClk_h;
    HostPtr<uint32_t> stopClk_h;
    startClk_d.ToHostPtr(startClk_h);
    stopClk_d.ToHostPtr(stopClk_h);

    double clockCycles = stopClk_h(0) - startClk_h(0);
    return clockCycles/UNROLL;
}

int main(){
    // 因为结果不稳定 所以10次实验取均值
    int times = 10;
    double Avg_res = 0.0;
    for(int i = 0; i < times; i++){
        Avg_res += doTest();
    }
    printf("In the case of L2 miss and L2 TLB hit, global memory load latency is: %lf cycles\n", (Avg_res/times));
}


// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/globalMem_latency_None globalMem_latency_None.cu

// nvcc --keep --keep-dir latency_midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/globalMem_latency_None globalMem_latency_None.cu
// cuasm --bin2asm latency_midRes/globalMem_latency_None.sm_86.cubin -o latency_midRes/globalMem_latency_None.sm_86.cuasm