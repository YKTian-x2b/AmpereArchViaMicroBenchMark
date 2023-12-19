#include "helper_cuda.h"
#include "hostptr.hpp"
#include "cuptr.hpp"

#include <cuda.h>
#include <cuda_runtime.h>
#include <iostream>
#include <cstdio>

#define GRD_SIZE 1
#define BLK_SIZE 32
#define UNROLL 10
// STRIDE 应该比 L2 cacheline 大，以避免l2缓存命中。
// Turing T4是64字节
#define STRIDE (1)

// workspace size in byte to flush L2 cache
const int L2_FLUSH_SIZE = (1 << 20) * 128;

template <int BLOCK>
__global__ void flush_l2_kernel(const int *x, int *y) {
    int warp_id = threadIdx.x / 32;
    int lane_id = threadIdx.x % 32;

    const int *x_ptr = x + blockIdx.x * BLOCK + warp_id * 32;
    int sum = 0;

    #pragma unroll
    for (int i = 0; i < 32; ++i) {
        const int *ldg_ptr = x_ptr + (lane_id ^ i);

        asm volatile (
            "{.reg .s32 val;\n"
            " ld.global.cg.b32 val, [%1];\n"
            " add.s32 %0, val, %0;}\n"
            : "+r"(sum) : "l"(ldg_ptr)
        );
    }

    if (sum != 0) {
        *y = sum;
    }
}

void flush_l2() {
    int *x;
    int *y;
    cudaMalloc(&x, L2_FLUSH_SIZE);
    cudaMalloc(&y, sizeof(int));
    cudaMemset(x, 0, L2_FLUSH_SIZE);

    int n = L2_FLUSH_SIZE / sizeof(int);
    flush_l2_kernel<128><<<n / 128, 128>>>(x, y);
    cudaDeviceSynchronize();

    cudaFree(x);
    cudaFree(y);
}

__device__ __forceinline__
uint32_t ldg_cv(const void *ptr) {
    uint32_t ret;
    asm volatile (
        "ld.global.cv.b32 %0, [%1];"
        : "=r"(ret)
        : "l"(ptr)
    );
    return ret;
}

__device__ __forceinline__
uint32_t ldg_cg(const void *ptr) {
    uint32_t ret;
    asm volatile (
        "ld.global.cg.b32 %0, [%1];"
        : "=r"(ret)
        : "l"(ptr)
    );
    return ret;
}

__device__ __forceinline__
uint32_t ldg_ca(const void *ptr) {
    uint32_t ret;
    asm volatile (
        "ld.global.ca.b32 %0, [%1];"
        : "=r"(ret)
        : "l"(ptr)
    );
    return ret;
}

__global__ void gloMem_latency_test_kernel(uint32_t *startClk, uint32_t *stopClk, uint32_t *out, uint32_t* arr){
    int tid = threadIdx.x;
    uint32_t offset = tid;

    uint32_t start, stop;
    asm volatile ("bar.sync 0;");
    asm volatile ("mov.u32 %0, %%clock;" :"=r"(start) :: "memory");

    #pragma unroll
    for(int i = 0; i < UNROLL; i++){
        offset = ldg_ca(arr+offset);
        // offset = ldg_cg(arr+offset);
        // offset = ldg_ca(arr+offset);
    }

    asm volatile ("mov.u32 %0, %%clock;" : "=r"(stop) :: "memory");

    startClk[tid] = start;
    stopClk[tid] = stop;

    if(offset == ~0x0){
        *out = offset;
    }
}

int main(){
    const uint32_t ARR_NUM = (UNROLL + 2) * STRIDE;
    HostPtr<uint32_t> arr_h(ARR_NUM);
    uint32_t *arr_ptr = arr_h.GetPtr();
    for(int i = 0; i < ARR_NUM; i++){
        arr_ptr[i] = i + STRIDE;
    }
    CuPtr<uint32_t> arr_d(arr_h);

    CuPtr<uint32_t> out_d(BLK_SIZE);
    CuPtr<uint32_t> startClk_d(BLK_SIZE);
    CuPtr<uint32_t> stopClk_d(BLK_SIZE);

    // pupulate l0/l1 i-cache
    gloMem_latency_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr(), arr_d.GetPtr());

    // flush L2 cache
    flush_l2();

    // 
    gloMem_latency_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr(), arr_d.GetPtr());
    cudaDeviceSynchronize();

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

    printf("global memory load latency: %lf cycles\n", clockCycles_avg / UNROLL);
}


// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/globalMem_latency globalMem_latency.cu

// nvcc --keep --keep-dir latency_midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/globalMem_latency globalMem_latency.cu
// cuasm --bin2asm latency_midRes/globalMem_latency.sm_86.cubin -o latency_midRes/globalMem_latency.sm_86.cuasm