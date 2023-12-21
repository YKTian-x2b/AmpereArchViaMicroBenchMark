#include "cuda_runtime.h"
#include "helper_cuda.h"
#include "cuptr.hpp"
#include "cuda.h"

#include <cstdio>
#include <iostream>
using namespace std;

#define GRD_SIZE (1)
#define BLK_SIZE (256)
#define N_UNROLL (4)

__global__ void L0CacheSize_test_kernel(const float4 v, int n_unroll, unsigned *startClk, unsigned *stopClk, float *a, int warpAIdx, int warpBIdx)
{
    int tid = threadIdx.x;
    int bid = blockIdx.x;
    int bdx = blockDim.x;
    int wid = tid >> 5;
    int lid = tid & 31;

    float v0 = v.x;
    float v1 = v.y;
    float v2 = v.z;
    float v3 = v.w;
    
    // 开始计时 start
    unsigned start = 0;
    asm volatile ("mov.u32 %0, %%clock;" : "=r"(start) :: "memory");

    if(wid == warpAIdx){
        #pragma unroll
        for(int n = 0; n < n_unroll; n++)
            v0 = fmaf(v0, v2, v1);
    }
    else if(wid == warpBIdx){
        #pragma unroll
        for(int n = 0; n < n_unroll; n++)
            v0 = fmaf(v0, v2, v3);
    }
    else{
        ;
    }
    
    // 停止计时 stop
    unsigned stop = 0;
    asm volatile ("mov.u32 %0, %%clock;" : "=r"(stop) :: "memory");

    // 将时间和数据写回内存  
    // only first lane of warp writes to memory
    if(lid == 0){
        int index = ((bid * bdx) >> 5) + wid;
        a[index] = v0;
        startClk[index] = start;
        stopClk[index]= stop;
    }  
}

float L0CacheSize_test_run(const float4 v, int n_unroll, unsigned *startClk, unsigned *stopClk, float *a, int warpAIdx, int warpBIdx)
{
    cudaEvent_t event_start, event_stop;
    checkCudaErrors(cudaEventCreate(&event_start));
    checkCudaErrors(cudaEventCreate(&event_stop));
    float elapsedTime;
    checkCudaErrors(cudaEventRecord(event_start, 0));

    L0CacheSize_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(v, n_unroll, startClk, stopClk, a, warpAIdx, warpBIdx);

    checkCudaErrors(cudaEventRecord(event_stop, 0));
    checkCudaErrors(cudaEventSynchronize(event_stop));
    checkCudaErrors(cudaEventElapsedTime(&elapsedTime, event_start, event_stop));
    checkCudaErrors(cudaEventDestroy(event_start));
    checkCudaErrors(cudaEventDestroy(event_stop));
    return elapsedTime;
}

float L0CacheSize_test_run_drv(const float4 v, int n_unroll, unsigned *startClk, unsigned *stopClk, float *a, int warpAIdx, int warpBIdx)
{
    static CUmodule cuModule;
    static CUfunction kernel;
    static bool isInitialized = false;

    if (!isInitialized)
    {
        cuInit(0);

        // Create module from binary file
        cuModuleLoad(&cuModule, "warpScheduleTest.sm_86.cubin");

        // Get function handle from module
        cuModuleGetFunction(&kernel, cuModule, "_Z23L0CacheSize_test_kernel6float4iPjS0_Pfii");

        printf("cuModule = %#llx\n", (unsigned long long)cuModule);
        printf("cuFunction = %#llx\n", (unsigned long long)kernel);
        isInitialized = true;
    }

    cudaEvent_t event_start, event_stop;
    checkCudaErrors(cudaEventCreate(&event_start));
    checkCudaErrors(cudaEventCreate(&event_stop));
    float elapsedTime;
    checkCudaErrors(cudaEventRecord(event_start, 0));

    void* args[] = { (void*)&v, (void*)&n_unroll, (void*)&startClk, (void*)&stopClk, (void*)&a, (void*)&warpAIdx, (void*)&warpBIdx};
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

void doTest()
{
    size_t eleSize = GRD_SIZE * BLK_SIZE / 32;
    CuPtr<float> da(eleSize);
    CuPtr<unsigned> d_startClk(eleSize);
    CuPtr<unsigned> d_stopClk(eleSize);

    float4 v = make_float4(1.0f, 1.0f, 1.0f, 1.0f);

    printf("### Warming Up...\n");
    da.SetZeros();
    d_startClk.SetZeros();
    d_stopClk.SetZeros();
    int n_unroll = N_UNROLL;

    int warpAIdx = 0;
    int warpBIdx = 4;
    L0CacheSize_test_run_drv(v, n_unroll, d_startClk.GetPtr(), d_stopClk.GetPtr(), da.GetPtr(), warpAIdx, warpBIdx);
    
    printf("### Runing...\n");

    // for(int warpAIdx = 3; warpAIdx < 4; warpAIdx++){
    //     for(int warpBIdx = 4; warpBIdx < 8; warpBIdx++){
            da.SetZeros();
            d_startClk.SetZeros();
            d_stopClk.SetZeros();
        
            float elapsedAll = L0CacheSize_test_run_drv(v, n_unroll, d_startClk.GetPtr(), d_stopClk.GetPtr(), da.GetPtr(), warpAIdx, warpBIdx);
            // L0CacheSize_test_run(v, n_unroll, d_startClk.GetPtr(), d_stopClk.GetPtr(), da.GetPtr(), warpAIdx, warpBIdx);
            
            printf("\n### Result checking...\n");
            HostPtr<float> ha;
            da.ToHostPtr(ha);
            HostPtr<unsigned> h_startClk;
            d_startClk.ToHostPtr(h_startClk);
            HostPtr<unsigned> h_stopClk;
            d_stopClk.ToHostPtr(h_stopClk);
            for(int i = 0; i < eleSize; i++)
            {
                // if(i == warpAIdx || i == warpBIdx){
                    unsigned elapsed = h_stopClk(i)-h_startClk(i);
                    printf("index[%2d],  res: %8.3f, warpIdx: %d,  startClk: %10u,  elapsed %10uclks\n", i, ha(i), i%4, h_startClk(i), elapsed);
                // }
            }
            printf("elapsed_all: %10fms\n", elapsedAll);
    //     }
    // }    
}

int main(){
    doTest();
    return 0;
}

// nvcc --keep -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I/opt/kaiProjects/GEMM_kai/Utils -L /usr/local/cuda/lib64 -l cuda -o warpScheduleTest save/warpScheduleTest.cu

// cuasm --bin2asm warpScheduleTest.sm_86.cubin

// cp warpScheduleTest.sm_86.cuasm save/warpScheduleTest.template.sm_86.cuasm && cp warpScheduleTest.sm_86.cuasm save/warpScheduleTest.origin.sm_86.cuasm

// @CUASM_INSERT_MARKER_POS.WORK_1

// python3 save/test_warpSchedule.py