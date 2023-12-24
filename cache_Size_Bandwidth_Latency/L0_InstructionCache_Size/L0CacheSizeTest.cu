#include "cuda_runtime.h"
#include "helper_cuda.h"
#include "cuptr.hpp"
#include "cuda.h"

#include <cstdio>
#include <iostream>
using namespace std;

#define GRD_SIZE (30)
#define BLK_SIZE (128)
#define N_UNROLL (4)

__global__ void L0CacheSize_test_kernel(const float4 v, int n_unroll, unsigned *startClk, unsigned *stopClk, float *a)
{
    int tid = threadIdx.x;
    int bid = blockIdx.x;
    int bdx = blockDim.x;
    int wid = tid / 32;
    int lid = tid % 32;

    float v0 = v.x;
    float v1 = v.y;
    float v2 = v.z;

    // 填充L0指令缓存 预热
    #pragma unroll
    for(int n = 0; n < n_unroll; n++)
        v0 = fmaf(v0, v2, v1);
    
    asm volatile ("bar.sync 0;");

    // 开始计时 start
    unsigned start = 0;
    asm volatile ("mov.u32 %0, %%clock;" : "=r"(start) :: "memory");

    #pragma unroll
    for(int n = 0; n < n_unroll; n++)
        v0 = fmaf(v0, v2, v1);
    
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

void L0CacheSize_test_run(const float4 v, int n_unroll, unsigned *startClk, unsigned *stopClk, float *a)
{
    L0CacheSize_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(v, n_unroll, startClk, stopClk, a);
    cudaDeviceSynchronize();
}

void L0CacheSize_test_run_drv(const float4 v, int n_unroll, unsigned *startClk, unsigned *stopClk, float *a)
{
    static CUmodule cuModule;
    static CUfunction kernel;
    static bool isInitialized = false;

    if (!isInitialized)
    {
        cuInit(0);

        // Create module from binary file
        cuModuleLoad(&cuModule, "L0CacheSizeTest.sm_86.cubin");

        // Get function handle from module _Z23L0CacheSize_test_kernel6float4iPjS0_Pf
        cuModuleGetFunction(&kernel, cuModule, "_Z23L0CacheSize_test_kernel6float4iPjS0_Pf");

        printf("cuModule = %#llx\n", (unsigned long long)cuModule);
        printf("cuFunction = %#llx\n", (unsigned long long)kernel);
        isInitialized = true;
    }


    void* args[] = { (void*)&v, (void*)&n_unroll, (void*)&startClk, (void*)&stopClk, (void*)&a };
    cuLaunchKernel(kernel,
                   GRD_SIZE, 1, 1, BLK_SIZE, 1, 1,
                    0, 0, args, 0);
    cudaDeviceSynchronize();
}

void doTest()
{
    size_t eleSize = GRD_SIZE * BLK_SIZE / 32;
    CuPtr<float> da(eleSize);
    CuPtr<unsigned> d_startClk(eleSize);
    CuPtr<unsigned> d_stopClk(eleSize);

    float4 v = make_float4(1.0f, 1.0f, 1.0f, 0);
    
    printf("### Runing...\n");

    da.SetZeros();
    d_startClk.SetZeros();
    d_stopClk.SetZeros();
    int n_unroll = N_UNROLL;

    L0CacheSize_test_run_drv(v, n_unroll, d_startClk.GetPtr(), d_stopClk.GetPtr(), da.GetPtr());
    

    printf("\n### Result checking...\n");
    HostPtr<float> ha;
    da.ToHostPtr(ha);
    HostPtr<unsigned> h_startClk;
    d_startClk.ToHostPtr(h_startClk);
    HostPtr<unsigned> h_stopClk;
    d_stopClk.ToHostPtr(h_stopClk);
    double avgCycles = 0;
    for(int i = 0; i < eleSize; i++)
    {
        unsigned elapsed = h_stopClk(i)-h_startClk(i);
        avgCycles += elapsed;
    }
    printf("avg Cycles: %lf\n", avgCycles/eleSize);
}

int main(){
    doTest();
    return 0;
}

// nvcc --keep -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I/opt/kaiProjects/GEMM_kai/Utils -L /usr/local/cuda/lib64 -l cuda -o L0CacheSizeTest save/L0CacheSizeTest.cu

// cuasm --bin2asm L0CacheSizeTest.sm_86.cubin

// cp L0CacheSizeTest.sm_86.cuasm save/L0CacheSizeTest.template.sm_86.cuasm && cp L0CacheSizeTest.sm_86.cuasm save/L0CacheSizeTest.origin.sm_86.cuasm

// @CUASM_INSERT_MARKER_POS.WORK_1

// python3 save/test_L0_Cache.py