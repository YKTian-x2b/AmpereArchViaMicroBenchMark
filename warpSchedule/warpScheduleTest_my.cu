#include "cuda_runtime.h"
#include "helper_cuda.h"
#include "cuptr.hpp"
#include "cuda.h"

#include <cstdio>
#include <iostream>
using namespace std;

#define GRD_SIZE 1
// [512, 512+32, 512+64, 512+96, 512+128]
#define BLK_SIZE (512+64)
#define N_UNROLL 10

__global__ void warpSchedule_test_kernel(const float4 v, unsigned *startClk, unsigned *stopClk, float *out)
{
    int tid = threadIdx.x;
    int bid = blockIdx.x;
    int bdx = blockDim.x;
    int wid = tid >> 5;
    int lid = tid & 31;

    float v0 = v.x;
    float v1 = v.y;
    float v2 = v.z;
    
    // 开始计时 start
    unsigned start = 0;
    asm volatile ("mov.u32 %0, %%clock;" : "=r"(start) :: "memory");

    #pragma unroll
    for(int n = 0; n < N_UNROLL; n++){
        v0 = fmaf(v0, v2, v1);
    }
    
    // 停止计时 stop
    unsigned stop = 0;
    asm volatile ("mov.u32 %0, %%clock;" : "=r"(stop) :: "memory");

    // 将时间和数据写回内存  
    // only first lane of warp writes to memory
    if(lid == 0){
        int index = ((bid * bdx) >> 5) + wid;
        out[index] = v0;
        startClk[index] = start;
        stopClk[index]= stop;
    }  
}

float warpSchedule_test_run(const float4 v, unsigned *startClk, unsigned *stopClk, float *out)
{
    cudaEvent_t event_start, event_stop;
    checkCudaErrors(cudaEventCreate(&event_start));
    checkCudaErrors(cudaEventCreate(&event_stop));
    float elapsedTime;
    checkCudaErrors(cudaEventRecord(event_start, 0));

    warpSchedule_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(v, startClk, stopClk, out);

    checkCudaErrors(cudaEventRecord(event_stop, 0));
    checkCudaErrors(cudaEventSynchronize(event_stop));
    checkCudaErrors(cudaEventElapsedTime(&elapsedTime, event_start, event_stop));
    checkCudaErrors(cudaEventDestroy(event_start));
    checkCudaErrors(cudaEventDestroy(event_stop));
    return elapsedTime;
}

float warpSchedule_test_run_drv(const float4 v, unsigned *startClk, unsigned *stopClk, float *out)
{
    static CUmodule cuModule;
    static CUfunction kernel;
    static bool isInitialized = false;

    if (!isInitialized)
    {
        cuInit(0);

        // Create module from binary file
        cuModuleLoad(&cuModule, "midRes2/warpScheduleTest_my.sm_86.cubin");

        // Get function handle from module
        cuModuleGetFunction(&kernel, cuModule, "_Z24warpSchedule_test_kernel6float4PjS0_Pf");

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

void doTest()
{
    size_t eleSize = GRD_SIZE * BLK_SIZE / 32;
    CuPtr<float> d_out(eleSize);
    CuPtr<unsigned> d_startClk(eleSize);
    CuPtr<unsigned> d_stopClk(eleSize);

    float4 v = make_float4(1.0f, 1.0f, 1.0f, 1.0f);

    printf("### Warming Up...\n");
    d_out.SetZeros();
    d_startClk.SetZeros();
    d_stopClk.SetZeros();

    warpSchedule_test_run_drv(v, d_startClk.GetPtr(), d_stopClk.GetPtr(), d_out.GetPtr());
    // warpSchedule_test_run(v, d_startClk.GetPtr(), d_stopClk.GetPtr(), d_out.GetPtr());
    
    printf("### Runing...\n");
    d_out.SetZeros();
    d_startClk.SetZeros();
    d_stopClk.SetZeros();

    float elapsedAll = warpSchedule_test_run_drv(v, d_startClk.GetPtr(), d_stopClk.GetPtr(), d_out.GetPtr());
    // float elapsedAll = warpSchedule_test_run(v, d_startClk.GetPtr(), d_stopClk.GetPtr(), d_out.GetPtr());
    
    printf("\n### Result checking...\n");
    HostPtr<float> h_out;
    HostPtr<unsigned> h_startClk;
    HostPtr<unsigned> h_stopClk;
    d_out.ToHostPtr(h_out);
    d_startClk.ToHostPtr(h_startClk);
    d_stopClk.ToHostPtr(h_stopClk);
    for(int i = 0; i < eleSize; i++){
        unsigned elapsed = h_stopClk(i)-h_startClk(i);
        printf("index[%2d],  res: %8.3f, warpIdx: %d,  startClk: %10u,  elapsed %10uclks\n", i, h_out(i), i%4, h_startClk(i), elapsed);
    }
    printf("elapsed_all: %10fms\n", elapsedAll);
}

int main(){
    doTest();
    return 0;
}

// nvcc --keep --keep-dir midRes2 -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/warpScheduleTest_my warpScheduleTest_my.cu

// cuasm --bin2asm midRes2/warpScheduleTest_my.sm_86.cubin -o midRes2/warpScheduleTest_my.sm_86.cuasm

// cp midRes2/warpScheduleTest_my.sm_86.cuasm res/warpScheduleTest_my.template.sm_86.cuasm && cp midRes2/warpScheduleTest_my.sm_86.cuasm res/warpScheduleTest_my.origin.sm_86.cuasm

// @CUASM_INSERT_MARKER_POS.

// python3 test_warpSchedule_my.py