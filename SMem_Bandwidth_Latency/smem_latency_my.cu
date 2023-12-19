#include "helper_cuda.h"
#include "cuptr.hpp"
#include "hostptr.hpp"

#include <iostream>
#include <cstdio>
#include <cstdint>

#include <cuda_runtime.h>
#include <cuda.h>

#define GRD_SIZE 1
#define BLK_SIZE 32
#define SMEM_SIZE 32
#define UNROLL 50
#define WARMUP 100

// SMem(ld/st): 23/19 Cycles
__global__ __launch_bounds__(32, 1)
void smem_ld_latency_test_kernel(uint32_t *startClk, uint32_t *stopClk, uint32_t *out){
    __shared__ uint32_t Arr[SMEM_SIZE];
    int tid = threadIdx.x;
    uint32_t start, stop;
    
    // Arr[tid] = ((tid + SMEM_SIZE/2) % SMEM_SIZE) * sizeof(uint32_t);
    Arr[tid] = tid * sizeof(uint32_t);

    uint32_t arr_addr;
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

    // 这儿可能可以加个同步
    // asm volatile ("bar.sync 0;");
    asm volatile ("mov.u32 %0, %%clock;" : "=r"(stop) :: "memory");

    startClk[tid] = start;
    stopClk[tid] = stop;

    if(arr_addr == ~0x0){
        *out = arr_addr;
    }
}

__global__ __launch_bounds__(32, 1)
void smem_st_latency_test_kernel(uint32_t *startClk, uint32_t *stopClk, uint32_t *out){
    __shared__ uint32_t Arr[SMEM_SIZE+UNROLL];
    int tid = threadIdx.x;
    uint32_t start, stop;

    Arr[tid] = tid * sizeof(uint32_t);

    uint32_t arr_addr;
    asm volatile (
        "{.reg .u64 u64addr;\n"
        " cvta.to.shared.u64 u64addr, %1;\n"
        " cvt.u32.u64 %0, u64addr;}\n"
        : "=r"(arr_addr)
        : "l"(Arr + tid)
    );

    asm volatile ("bar.sync 0;");
    asm volatile ("mov.u32 %0, %%clock;" :"=r"(start) :: "memory");
    
    // #pragma unroll
    // for(int i = 0; i < UNROLL; i++){
    //     asm volatile (
    //         "st.shared.b32 [%0], %1;\n"
    //         : "=r"(arr_addr) : "r"(tid) : "memory"
    //     );
    // }

    asm volatile (
        "st.shared.b32 [%0], %1;\n"
        : "=r"(arr_addr) : "r"(tid) : "memory"
    );

    asm volatile ("mov.u32 %0, %%clock;" : "=r"(stop) :: "memory");

    startClk[tid] = start;
    stopClk[tid] = stop;

    if(arr_addr == ~0x0){
        *out = Arr[tid];
    }
}

void smem_st_latency_test_run_drv(uint32_t *startClk, uint32_t *stopClk, uint32_t *out){
    static CUmodule cuModule;
    static CUfunction kernel;
    static bool isInitialized = false;

    if (!isInitialized)
    {
        cuInit(0);

        // Create module from binary file
        cuModuleLoad(&cuModule, "latency_midRes/smem_latency_my.sm_86.cubin");

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

int main(){
    // CuPtr<uint32_t> out_d(BLK_SIZE);
    // CuPtr<uint32_t> startClk_d(BLK_SIZE);
    // CuPtr<uint32_t> stopClk_d(BLK_SIZE);

    // for (int i = 0; i < WARMUP; i++) {
    //     smem_ld_latency_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr());
    // }
    // cudaDeviceSynchronize();

    // smem_ld_latency_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr());
    // cudaDeviceSynchronize();

    // HostPtr<uint32_t> out_h;
    // HostPtr<uint32_t> startClk_h;
    // HostPtr<uint32_t> stopClk_h;
    // startClk_d.ToHostPtr(startClk_h);
    // stopClk_d.ToHostPtr(stopClk_h);

    // double clockCycles_avg = 0.0;
    // for(int i = 0; i < BLK_SIZE; i++){
    //     std::cout << startClk_h(i) << " " << stopClk_h(i) << std::endl;
    //     clockCycles_avg += stopClk_h(i) - startClk_h(i);
    // }
    // clockCycles_avg /= BLK_SIZE;

    // printf("shared memory load latency: %lf cycles\n", clockCycles_avg / UNROLL);



    CuPtr<uint32_t> out_d(BLK_SIZE);
    CuPtr<uint32_t> startClk_d(BLK_SIZE);
    CuPtr<uint32_t> stopClk_d(BLK_SIZE);

    // for (int i = 0; i < WARMUP; i++) {
    //     smem_st_latency_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr());
    // }
    // cudaDeviceSynchronize();

    smem_st_latency_test_run_drv(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr());
    // smem_st_latency_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr());

    HostPtr<uint32_t> out_h;
    HostPtr<uint32_t> startClk_h;
    HostPtr<uint32_t> stopClk_h;
    startClk_d.ToHostPtr(startClk_h);
    stopClk_d.ToHostPtr(stopClk_h);

    double clockCycles_avg = 0.0;
    for(int i = 0; i < BLK_SIZE; i++){
        std::cout << startClk_h(i) << " " << stopClk_h(i) << std::endl;
        clockCycles_avg += stopClk_h(i) - startClk_h(i);
    }
    clockCycles_avg /= BLK_SIZE;

    printf("shared memory store latency: %lf cycles\n", clockCycles_avg);
}

// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/smem_latency_my smem_latency_my.cu

// nvcc --keep --keep-dir latency_midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/smem_latency_my smem_latency_my.cu
// cuasm --bin2asm latency_midRes/smem_latency_my.sm_86.cubin -o latency_midRes/smem_latency_my.sm_86.cuasm

// cuasm --asm2bin latency_midRes/smem_latency_my.sm_86.cuasm -o latency_midRes/smem_latency_my.sm_86.cubin





// ld结果是：22.9620 约等于 23 个时钟周期