#include "helper_cuda.h"
#include "cuptr.hpp"
#include "hostptr.hpp"
#include <cuda.h>
#include <cuda_runtime.h>
#include <iostream>
#include <cstdio>

#define GRD_SIZE 1
#define BLK_SIZE 1
#define UNROLL 256

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

__device__ __forceinline__
uint32_t ldg_nc(const void *ptr) {
    uint32_t ret;
    asm volatile (
        "ld.global.nc.b32 %0, [%1];"
        : "=r"(ret)
        : "l"(ptr)
    );
    return ret;
}


__global__ void gloMem_latency_test_kernel(uint32_t *elapsedTime, uint32_t *out, uint32_t *arr){
    __shared__ uint32_t s_tvalue[UNROLL];
    __shared__ uint32_t s_index[UNROLL];

    uint32_t sum = 0;
    uint32_t j = 0;
    // j= ldg_ca(arr+j);

    uint32_t start_time, stop_time;
    for(int it = 0; it < UNROLL; it++){
        
        asm volatile ("mov.u32 %0, %%clock;" :"=r"(start_time) :: "memory");

        j= ldg_ca(arr+j);
        sum += j;

        asm volatile ("mov.u32 %0, %%clock;" :"=r"(stop_time) :: "memory");
        
        s_tvalue[it] = stop_time - start_time;
    }

    for(int i = 0; i < UNROLL; i++){
        elapsedTime[i] = s_tvalue[i];
    }
    
    *out = sum;
}

void gloMem_latency_test_run(const uint32_t STRIDE, const uint32_t ARR_NUM){
    HostPtr<uint32_t> arr_h(ARR_NUM);
    uint32_t *arr_ptr = arr_h.GetPtr();
    for(uint32_t  i = 0; i < ARR_NUM; i++){
        arr_ptr[i] = (i + STRIDE) % ARR_NUM;
    }
    CuPtr<uint32_t> arr_d(arr_h);
    CuPtr<uint32_t> out_d(1);
    CuPtr<uint32_t> elapsedTime_d(UNROLL);

    gloMem_latency_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(elapsedTime_d.GetPtr(), out_d.GetPtr(), arr_d.GetPtr());
    cudaDeviceSynchronize();

    flush_l2();

    gloMem_latency_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(elapsedTime_d.GetPtr(), out_d.GetPtr(), arr_d.GetPtr());
    cudaDeviceSynchronize();

    // HostPtr<uint32_t> out_h;
    HostPtr<uint32_t> elapsedTime_h;
    elapsedTime_d.ToHostPtr(elapsedTime_h);
    // out_d.ToHostPtr(out_h);

    for(int i = 0; i < UNROLL; i++){
        std::cout << "elapsedTime_h(" << i << "): " << elapsedTime_h(i) << std::endl;
    }
}

void doTest(){
    const uint32_t stride = 1;
    const uint32_t arr_size = 512;
    gloMem_latency_test_run(stride, arr_size);
}

int main(){
    doTest();
}

// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/globalMem_latency_my4 globalMem_latency_my4.cu

// nvcc --keep --keep-dir latency_midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/globalMem_latency_my4 globalMem_latency_my4.cu
// cuasm --bin2asm latency_midRes/globalMem_latency_my4.sm_86.cubin -o latency_midRes/globalMem_latency_my4.sm_86.cuasm