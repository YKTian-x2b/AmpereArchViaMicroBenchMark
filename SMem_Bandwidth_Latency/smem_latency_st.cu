#include "helper_cuda.h"
#include "cuptr.hpp"
#include "hostptr.hpp"

#include <iostream>
#include <cstdio>
#include <cstdint>

#include <cuda_runtime.h>
#include <cuda.h>

#define GRD_SIZE 1
#define BLK_SIZE 16
#define UNROLL 50
#define WARMUP 100

// SMem(ld/st): 23/19 Cycles
__global__ void smem_st_latency_test_kernel(uint32_t *startClk, uint32_t *stopClk, uint32_t *out){
    __shared__ uint32_t Arr[BLK_SIZE+UNROLL];
    int tid = threadIdx.x;
    uint32_t start, stop;
    uint32_t *arr_addr = Arr+tid;
    // 为了让计时区间的代码干净一些，先跑一次，准备好寄存器。
    // *arr_addr = tid; 也可以。主要还是改汇编。
    #pragma unroll
    for(int i = 0; i < UNROLL; i++){
        *(arr_addr+i) = tid;
    }

    asm volatile ("bar.sync 0;");
    asm volatile ("mov.u32 %0, %%clock;" :"=r"(start) :: "memory");
    
    #pragma unroll
    for(int i = 0; i < UNROLL; i++){
        *(arr_addr+i) = tid;
    }

    asm volatile ("mov.u32 %0, %%clock;" : "=r"(stop) :: "memory");

    startClk[tid] = start;
    stopClk[tid] = stop;
    out[tid] = *(arr_addr+UNROLL-1);
}

void smem_st_latency_test_run_drv(uint32_t *startClk, uint32_t *stopClk, uint32_t *out){
    static CUmodule cuModule;
    static CUfunction kernel;
    static bool isInitialized = false;

    if (!isInitialized)
    {
        cuInit(0);

        // Create module from binary file
        cuModuleLoad(&cuModule, "latency_midRes/smem_latency_st.sm_86.cubin");

        // Get function handle from module 
        cuModuleGetFunction(&kernel, cuModule, "_Z27smem_st_latency_test_kernelPjS_S_");

        isInitialized = true;
    }

    void* args[] = { (void*)&startClk, (void*)&stopClk, (void*)&out };
    cuLaunchKernel(kernel,
                   GRD_SIZE, 1, 1, BLK_SIZE, 1, 1,
                    0, 0, args, 0);
    cudaDeviceSynchronize();
}


void doStoreTest(){
    CuPtr<uint32_t> out_d(BLK_SIZE);
    CuPtr<uint32_t> startClk_d(BLK_SIZE);
    CuPtr<uint32_t> stopClk_d(BLK_SIZE);
    // warm up
    for (int i = 0; i < WARMUP; i++) {
        smem_st_latency_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr());
    }
    cudaDeviceSynchronize();
    // run
    smem_st_latency_test_run_drv(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr());
    // smem_st_latency_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr());

    HostPtr<uint32_t> out_h;
    HostPtr<uint32_t> startClk_h;
    HostPtr<uint32_t> stopClk_h;
    startClk_d.ToHostPtr(startClk_h);
    stopClk_d.ToHostPtr(stopClk_h);

    double clockCycles = stopClk_h(0) - startClk_h(0);
    clockCycles /= UNROLL;

    printf("shared memory store latency: %lf cycles\n", clockCycles);
}

int main(){
    doStoreTest();
}

// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/smem_latency_st smem_latency_st.cu


// nvcc --keep --keep-dir latency_midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/smem_latency_st smem_latency_st.cu
// cuasm --bin2asm latency_midRes/smem_latency_st.sm_86.cubin -o latency_midRes/smem_latency_st.sm_86.cuasm

// cuasm --asm2bin latency_midRes/smem_latency_st.sm_86.cuasm -o latency_midRes/smem_latency_st.sm_86.cubin
