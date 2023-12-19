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

#define UNROLL 16
#define BLK_SIZE 512
#define GRD_SIZE (N_LDG / UNROLL / BLK_SIZE)

__device__ __forceinline__
float ldg_cg(const void *ptr) {
    float ret;
    asm volatile (
        "ld.global.cg.f32 %0, [%1];"
        : "=f"(ret)
        : "l"(ptr)
    );
    return ret;
}

__global__ void L2cacheBW_test_kernel(const float *x, float *y) {
    int offset = (BLK_SIZE * UNROLL * blockIdx.x + threadIdx.x) % N_DATA;
    const float *ldg_ptr = x + offset;

    float sum = 0;
    // 每个元素都得用，要不然编译器优化，就不会产生读指令
    #pragma unroll
    for (int i = 0; i < UNROLL; ++i) {
        sum += ldg_cg(ldg_ptr + BLK_SIZE * i);
    }
    // 欺骗编译器？
    if(sum != 0){
        *y = sum;
    }
}

void doTest(){
    static_assert(N_DATA >= UNROLL * BLK_SIZE && N_DATA % (UNROLL * BLK_SIZE) == 0,
                  "UNROLL or BLK_SIZE is invalid");
    
    HostPtr<float> x_h(N_DATA);
    x_h.SetZeros();
    CuPtr<float> x(x_h);
    CuPtr<float> y(N_DATA);

    std::cout << "Warming Up ..." << std::endl;
    // warm up to cache data into L2
    for (int i = 0; i < WARMUP_ITER; ++i) {
        L2cacheBW_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(x.GetPtr(), y.GetPtr());
    }

    cudaEvent_t start, stop;
    checkCudaErrors(cudaEventCreate(&start));
    checkCudaErrors(cudaEventCreate(&stop));
    float time_ms;
    std::cout << "Running ..." << std::endl;
    checkCudaErrors(cudaEventRecord(start));
    for (int i = 0; i < BENCH_ITER ; ++i) {
        L2cacheBW_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(x.GetPtr(), y.GetPtr());
    }
    checkCudaErrors(cudaEventRecord(stop));
    checkCudaErrors(cudaEventSynchronize(stop));
    checkCudaErrors(cudaEventElapsedTime(&time_ms, start, stop));
    checkCudaErrors(cudaEventDestroy(start));
    checkCudaErrors(cudaEventDestroy(stop));

    double gbps = ((double)(N_LDG * sizeof(int)) / 1e9) /
                  ((double)time_ms / BENCH_ITER / 1e3);
    printf("L2 cache bandwidth: %fGB/s\n", gbps);
}

int main(){
    doTest();
    return 0;
}


// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/L2cacheBW_test L2cacheBW_test.cu

// 驱动调试
// nvcc --keep --keep-dir midRes_test -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/L2cacheBW_test L2cacheBW_test.cu
// cuasm --bin2asm midRes_test/L2cacheBW_test.sm_86.cubin -o midRes_test/L2cacheBW_test.sm_86.cuasm
// rm midRes_test/*
// cuasm --asm2bin midRes_test/L2cacheBW_test.sm_86.cuasm -o midRes_test/L2cacheBW_test.sm_86.cubin 