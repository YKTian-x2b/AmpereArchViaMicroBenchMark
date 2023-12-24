#include "helper_cuda.h"
#include "hostptr.hpp"
#include "cuptr.hpp"

#include <iostream>
#include <cstdio>
#include <cuda.h>
#include <cuda_runtime.h>

#define GRD_SIZE 1
#define BLK_SIZE 128
#define N_UNROLL 10
#define WARM_UP 100

__global__ void L0CacheSize_test_kernel(const float4 v, unsigned *startClk, unsigned *stopClk, float *out){
    int tid = threadIdx.x;
    float v0 = v.x;
    float v1 = v.y;
    float v2 = v.z;
    // populate l0 i-cache
    #pragma unroll
    for(int n = 0; n < N_UNROLL; n++){
        v0 = fmaf(v0, v2, v1);
    }

    // 开始计时 start
    unsigned start, stop;
    asm volatile (
        "mov.u32 %0, %%clock;\n"
        : "=r"(start) : : "memory"
    );

    #pragma unroll
    for(int n = 0; n < N_UNROLL; n++){
        v0 = fmaf(v0, v2, v1);
    }
    
    // 停止计时 stop
    asm volatile ("mov.u32 %0, %%clock;" : "=r"(stop) :: "memory");

    // 将时间和数据写回内存  
    startClk[tid] = start;
    stopClk[tid]= stop;
    if(v0 == 0){
        out[tid] = v0;
    }  
}

float L0CacheSize_test_run(const float4 v, unsigned *startClk, unsigned *stopClk, float *out)
{
    cudaEvent_t event_start, event_stop;
    checkCudaErrors(cudaEventCreate(&event_start));
    checkCudaErrors(cudaEventCreate(&event_stop));
    float elapsedTime;
    checkCudaErrors(cudaEventRecord(event_start, 0));

    L0CacheSize_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(v, startClk, stopClk, out);

    checkCudaErrors(cudaEventRecord(event_stop, 0));
    checkCudaErrors(cudaEventSynchronize(event_stop));
    checkCudaErrors(cudaEventElapsedTime(&elapsedTime, event_start, event_stop));
    checkCudaErrors(cudaEventDestroy(event_start));
    checkCudaErrors(cudaEventDestroy(event_stop));
    return elapsedTime;
}

float L0CacheSize_test_run_drv(const float4 v, unsigned *startClk, unsigned *stopClk, float *out)
{
    static CUmodule cuModule;
    static CUfunction kernel;
    static bool isInitialized = false;

    if (!isInitialized)
    {
        cuInit(0);

        // Create module from binary file
        cuModuleLoad(&cuModule, "midRes_my/L0CacheSizeTest_my.sm_86.cubin");

        // Get function handle from module
        cuModuleGetFunction(&kernel, cuModule, "_Z23L0CacheSize_test_kernel6float4PjS0_Pf");

        isInitialized = true;
    }

    cudaEvent_t event_start, event_stop;
    checkCudaErrors(cudaEventCreate(&event_start));
    checkCudaErrors(cudaEventCreate(&event_stop));
    float elapsedTime;
    checkCudaErrors(cudaEventRecord(event_start, 0));

    void* args[] = { (void*)&v, (void*)&startClk, (void*)&stopClk, (void*)&out};
    cuLaunchKernel(kernel,
                   GRD_SIZE, 1, 1, BLK_SIZE, 1, 1,
                    0, 0, args, 0);

    checkCudaErrors(cudaEventRecord(event_stop, 0));
    checkCudaErrors(cudaEventSynchronize(event_stop));
    checkCudaErrors(cudaEventElapsedTime(&elapsedTime, event_start, event_stop));
    checkCudaErrors(cudaEventDestroy(event_start));
    checkCudaErrors(cudaEventDestroy(event_stop));
    return elapsedTime;
}

int main(){
    size_t eleSize = GRD_SIZE * BLK_SIZE;
    CuPtr<float> d_out(eleSize);
    CuPtr<unsigned> d_startClk(eleSize);
    CuPtr<unsigned> d_stopClk(eleSize);

    float4 v = make_float4(1.0f, 1.0f, 1.0f, 1.0f);

    printf("### Warming Up...\n");
    d_out.SetZeros();
    d_startClk.SetZeros();
    d_stopClk.SetZeros();
    // warm up
    // for(int i = 0; i < WARM_UP; i++){
    //     // L0CacheSize_test_run(v, d_startClk.GetPtr(), d_stopClk.GetPtr(), d_out.GetPtr());
    //     L0CacheSize_test_run_drv(v, d_startClk.GetPtr(), d_stopClk.GetPtr(), d_out.GetPtr());
    // }
    
    // L0CacheSize_test_run(v, d_startClk.GetPtr(), d_stopClk.GetPtr(), d_out.GetPtr());
    L0CacheSize_test_run_drv(v, d_startClk.GetPtr(), d_stopClk.GetPtr(), d_out.GetPtr());

    printf("### Runing...\n");
    d_out.SetZeros();
    d_startClk.SetZeros();
    d_stopClk.SetZeros();
    // float elapsedAll = L0CacheSize_test_run(v, d_startClk.GetPtr(), d_stopClk.GetPtr(), d_out.GetPtr());
    float elapsedAll = L0CacheSize_test_run_drv(v, d_startClk.GetPtr(), d_stopClk.GetPtr(), d_out.GetPtr());

    printf("\n### Result checking...\n");
    HostPtr<float> h_out;
    HostPtr<unsigned> h_startClk;
    HostPtr<unsigned> h_stopClk;
    d_out.ToHostPtr(h_out);
    d_startClk.ToHostPtr(h_startClk);
    d_stopClk.ToHostPtr(h_stopClk);
    double avgCycles = 0;
    for(int i = 0; i < eleSize; i++)
    {
        unsigned elapsed = h_stopClk(i)-h_startClk(i);
        avgCycles += elapsed;
    }
    printf("avg Cycles: %lf\n", avgCycles/eleSize);
}

// nvcc --keep --keep-dir midRes_my -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/L0CacheSizeTest_my L0CacheSizeTest_my.cu

// cuasm --bin2asm midRes_my/L0CacheSizeTest_my.sm_86.cubin -o midRes_my/L0CacheSizeTest_my.sm_86.cuasm

// cp midRes_my/L0CacheSizeTest_my.sm_86.cuasm res/L0CacheSizeTest_my.template.sm_86.cuasm && cp midRes_my/L0CacheSizeTest_my.sm_86.cuasm res/L0CacheSizeTest_my.origin.sm_86.cuasm

// @CUASM_INSERT_MARKER_POS.

// python3 test_L0_Cache_my.py