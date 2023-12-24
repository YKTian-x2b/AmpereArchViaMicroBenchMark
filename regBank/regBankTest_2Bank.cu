#include "cuda_runtime.h"
#include "helper_cuda.h"
#include "cuptr.hpp"
#include "cuda.h"

#include <cstdio>
#include <iostream>
using namespace std;

typedef unsigned int uint;

#define GRD_SIZE 1800
#define BLK_SIZE 512
#define UNROLL 10
#define N_WARMUP 10
#define N_TEST 5

__global__ void regbank_test_kernel(const float4 v, float *out)
{
    int tid = threadIdx.x;
    float v0 = v.x;
    float v1 = v.y;
    float v2 = v.z;

    #pragma unroll
    for(int n = 0; n < UNROLL; n++){
        v0 = fmaf(v0, v2, v1);
    }

    if(v0 == 0){
        out[tid] = v0;
    }  
}

float regbank_test_run(const float4 v, float *out, cudaEvent_t &event_start, cudaEvent_t &event_stop)
{
    float elapsedTime;
    checkCudaErrors(cudaEventRecord(event_start, 0));

    regbank_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(v, out);

    checkCudaErrors(cudaEventRecord(event_stop, 0));
    checkCudaErrors(cudaEventSynchronize(event_stop));
    checkCudaErrors(cudaEventElapsedTime(&elapsedTime, event_start, event_stop));

    return elapsedTime;
}

float regbank_test_run_drv(const float4 v, float *out, cudaEvent_t &event_start, cudaEvent_t &event_stop)
{
    static CUmodule cuModule;
    static CUfunction kernel;
    static bool isInitialized = false;

    if (!isInitialized)
    {
        cuInit(0);

        // Create module from binary file
        cuModuleLoad(&cuModule, "midRes/regBankTest_2Bank.sm_86.cubin");

        // Get function h_outndle from module 
        cuModuleGetFunction(&kernel, cuModule, "_Z19regbank_test_kernel6float4Pf");

        isInitialized = true;
    }

    float elapsedTime;
    checkCudaErrors(cudaEventRecord(event_start, 0));

    void* args[] = {(void*)&v, (void*)&out};
    cuLaunchKernel(kernel,
                   GRD_SIZE, 1, 1, BLK_SIZE, 1, 1,
                    0, 0, args, 0);

    checkCudaErrors(cudaEventRecord(event_stop, 0));
    checkCudaErrors(cudaEventSynchronize(event_stop));
    checkCudaErrors(cudaEventElapsedTime(&elapsedTime, event_start, event_stop));

    return elapsedTime;
}

void dotest()
{
    CuPtr<float> d_out(BLK_SIZE);

    cudaEvent_t event_start, event_stop;
    checkCudaErrors(cudaEventCreate(&event_start));
    checkCudaErrors(cudaEventCreate(&event_stop));

    float4 v = make_float4(0, 1.0f, 0, 0);

    printf("### Warm up...\n");
    for(int i=0; i<N_WARMUP; i++)
    {
        d_out.SetZeros();
        float elapsedTime = regbank_test_run_drv(v, d_out.GetPtr(), event_start, event_stop); // in ms
        // float elapsedTime = regbank_test_run(v, d_out.GetPtr(), event_start, event_stop);
        // printf("  Warmup %2d: %10.3f ms\n", i, elapsedTime);
    }
    
    printf("### Testing...\n");
    float elapsed_avg = 0.0;
    for(int i=0; i<N_TEST; i++)
    {
        d_out.SetZeros();
        float elapsedTime = regbank_test_run_drv(v, d_out.GetPtr(), event_start, event_stop); // in ms
        // float elapsedTime = regbank_test_run(v, d_out.GetPtr(), event_start, event_stop);
        // printf("  Test %2d: %10.3f ms\n", i, elapsedTime);
        elapsed_avg += elapsedTime;
    }
    printf("elapsedTime_avg: %10.3fms\n", elapsed_avg/N_TEST);

    checkCudaErrors(cudaEventDestroy(event_start));
    checkCudaErrors(cudaEventDestroy(event_stop));

    printf("\n### Result checking...\n");

    HostPtr<float> h_out;
    d_out.ToHostPtr(h_out);
    for(int i=0; i<BLK_SIZE/32; i++)
    {
        unsigned int xa = *(unsigned int *)(&h_out(i));
        // printf("res[%2d] : %8g  0x%08x\n", i, h_out(i), xa);
    }
}

int main()
{
    dotest();
    return 0;
}


// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I/opt/kaiProjects/GEMM_kai/Utils -L /usr/local/cuda/lib64 -l cuda -o res/regBankTest_2Bank regBankTest_2Bank.cu




// nvcc --keep --keep-dir midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I/opt/kaiProjects/GEMM_kai/Utils -L /usr/local/cuda/lib64 -l cuda -o res/regBankTest_2Bank regBankTest_2Bank.cu

// cuasm --bin2asm midRes/regBankTest_2Bank.sm_86.cubin -o midRes/regBankTest_2Bank.sm_86.cuasm

// cp midRes/regBankTest_2Bank.sm_86.cuasm res/regBankTest_2Bank.template.sm_86.cuasm && cp midRes/regBankTest_2Bank.sm_86.cuasm res/regBankTest_2Bank.origin.sm_86.cuasm

// @CUASM_INSERT_MARKER_POS.

// python3 test_regBank_2Bank.py