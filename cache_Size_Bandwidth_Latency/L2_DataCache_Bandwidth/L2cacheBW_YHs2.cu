#include "cuptr.hpp"
#include "hostptr.hpp"
#include "helper_cuda.h"

#include <cuda_runtime.h>
#include <cuda.h>
#include <iostream>
#include <cstdio>

// accessed data size in byte, should be smaller than l2 cache size
const size_t DATA_SIZE_IN_BYTE = (1lu << 20) * 2;
// number of LDG instructions 希望它是 （SM数 * 一个SM能启动的BLK_SIZE数） 的倍数
const size_t N_LDG = (1lu << 20) * 90 * 8;
const size_t N_DATA = DATA_SIZE_IN_BYTE / sizeof(float);

#define WARMUP_ITER 200
#define BENCH_ITER 200

#define UNROLL 64
#define BLK_SIZE 512
#define GRD_SIZE (N_LDG / UNROLL / BLK_SIZE)

__device__ __forceinline__
float ldg_cg(const void *ptr) {
    float ret;
    asm volatile (
        "ld.global.cg.b32 %0, [%1];"
        : "=f"(ret)
        : "l"(ptr)
    );
    return ret;
}

__global__ void L2cacheBW_test_kernel(const float *x, float *y) {
    int offset = (BLK_SIZE * UNROLL * blockIdx.x + threadIdx.x) % N_DATA;
    const float *ldg_ptr = x + offset;
    float reg[UNROLL];

    #pragma unroll
    for (int i = 0; i < UNROLL; ++i) {
        reg[i] = ldg_cg(ldg_ptr + BLK_SIZE * i);
    }

    float sum = 0;
    #pragma unroll
    for (int i = 0; i < UNROLL; ++i) {
        sum += reg[i];
    }
    if(sum != 0){
        *y = sum;
    }
}

float L2cacheBW_test_run_drv(const float* x, float *y){
    static CUmodule cuModule;
    static CUfunction kernel;
    static bool isInitialized = false;

    if(!isInitialized){
        cuInit(0);
        cuModuleLoad(&cuModule, "midRes/L2cacheBW_YHs2.sm_86.cubin");
        cuModuleGetFunction(&kernel, cuModule, "_Z21L2cacheBW_test_kernelPKfPf");   //
        isInitialized = true;
    }

    void* args[] = {(void*)&x, (void*)&y};

    std::cout << "Warming Up ..." << std::endl;
    // warm up to cache data into L2
    for (int i = 0; i < WARMUP_ITER; ++i) {
        cuLaunchKernel(kernel, GRD_SIZE, 1, 1, BLK_SIZE, 1, 1, 0, 0, args, 0);
    }

    cudaEvent_t start, stop;
    checkCudaErrors(cudaEventCreate(&start));
    checkCudaErrors(cudaEventCreate(&stop));
    float time_ms;
    std::cout << "Running ..." << std::endl;
    checkCudaErrors(cudaEventRecord(start));
    for (int i = 0; i < BENCH_ITER ; ++i) {
        cuLaunchKernel(kernel, GRD_SIZE, 1, 1, BLK_SIZE, 1, 1, 0, 0, args, 0);
    }
    checkCudaErrors(cudaEventRecord(stop));
    checkCudaErrors(cudaEventSynchronize(stop));
    checkCudaErrors(cudaEventElapsedTime(&time_ms, start, stop));
    checkCudaErrors(cudaEventDestroy(start));
    checkCudaErrors(cudaEventDestroy(stop));
    return time_ms;
}

float L2cacheBW_test_run(const float* x, float *y){
    std::cout << "Warming Up ..." << std::endl;
    // warm up to cache data into L2
    for (int i = 0; i < WARMUP_ITER; ++i) {
        L2cacheBW_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(x, y);
    }

    cudaEvent_t start, stop;
    checkCudaErrors(cudaEventCreate(&start));
    checkCudaErrors(cudaEventCreate(&stop));
    float time_ms;
    std::cout << "Running ..." << std::endl;
    checkCudaErrors(cudaEventRecord(start));
    for (int i = 0; i < BENCH_ITER ; ++i) {
        L2cacheBW_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(x, y);
    }
    checkCudaErrors(cudaEventRecord(stop));
    checkCudaErrors(cudaEventSynchronize(stop));
    checkCudaErrors(cudaEventElapsedTime(&time_ms, start, stop));
    checkCudaErrors(cudaEventDestroy(start));
    checkCudaErrors(cudaEventDestroy(stop));
    return time_ms;
}

void doTest(){
    static_assert(N_DATA >= UNROLL * BLK_SIZE && N_DATA % (UNROLL * BLK_SIZE) == 0,
                  "UNROLL or BLK_SIZE is invalid");
    
    HostPtr<float> x_h(N_DATA);
    x_h.SetZeros();
    CuPtr<float> x(x_h);
    CuPtr<float> y(N_DATA);

    // float time_ms = L2cacheBW_test_run(x.GetPtr(), y.GetPtr());
    float time_ms = L2cacheBW_test_run_drv(x.GetPtr(), y.GetPtr());

    double gbps = ((double)(N_LDG * sizeof(int)) / 1e9) /
                  ((double)time_ms / BENCH_ITER / 1e3);
    printf("L2 cache bandwidth: %fGB/s\n", gbps);
}

int main(){
    doTest();
    return 0;
}


// nvcc --keep --keep-dir midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/L2cacheBW_YHs2 L2cacheBW_YHs2.cu
// cuasm --bin2asm midRes/L2cacheBW_YHs2.sm_86.cubin -o midRes/L2cacheBW_YHs2.sm_86.cuasm

// rm midRes/*

// cuasm --asm2bin midRes/L2cacheBW_YHs2.sm_86.cuasm -o midRes/L2cacheBW_YHs2.sm_86.cubin 