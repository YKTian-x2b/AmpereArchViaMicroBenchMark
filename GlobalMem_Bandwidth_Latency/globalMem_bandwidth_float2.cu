#include "helper_cuda.h"
#include "cuptr.hpp"
#include "hostptr.hpp"

#include <cuda_runtime.h>
#include <cuda.h>

#include <iostream>
#include <cstdio>

#define WARMUP_ITER 200
#define BENCH_ITER 200
#define WARP_SIZE 32
#define BLK_SIZE 512
// 希望是 （SM个数 * 一个SM能启动的ThreadBlock数） 90 的倍数 要超大才能形成有效流水线
#define GRD_SIZE 90000
#define UNROLL 16
// Global Mem size 不到 6 * 1024*1024*1024字节
const size_t N_DATA = 1024*1024*128;

__device__ __forceinline__
float2 ldg_cv_v2(const void *ptr) {
    float2 ret;
    asm volatile (
        "ld.global.cv.v2.f32 {%0, %1}, [%2];"
        : "=f"(ret.x), "=f"(ret.y)
        : "l"(ptr)
    );
    return ret;
}

__global__ void globalMemBW_test_kernel(const float2 *Arr, float *out) {
    int offset = (BLK_SIZE * UNROLL * blockIdx.x + threadIdx.x) % N_DATA;
    const float2 *ldg_ptr = Arr + offset;
    float sum = 0;

    #pragma unroll
    for (int i = 0; i < UNROLL; ++i) {
        float2 tmp = ldg_cv_v2(ldg_ptr + BLK_SIZE * i);
        sum += tmp.x + tmp.y;
    }

    if(sum != 0){
        *out = sum;
    }
}

int main(){
    HostPtr<float2> arr_h(N_DATA);
    arr_h.SetZeros();
    CuPtr<float2> arr_d(arr_h);
    CuPtr<float> out_d(N_DATA);

    std::cout << "Warming Up ..." << std::endl;
    // warm up
    for (int i = 0; i < WARMUP_ITER; ++i) {
        globalMemBW_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(arr_d.GetPtr(), out_d.GetPtr());
    }

    cudaEvent_t start, stop;
    checkCudaErrors(cudaEventCreate(&start));
    checkCudaErrors(cudaEventCreate(&stop));
    float time_ms;
    std::cout << "Running ..." << std::endl;
    checkCudaErrors(cudaEventRecord(start));
    for (int i = 0; i < BENCH_ITER ; ++i) {
        globalMemBW_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(arr_d.GetPtr(), out_d.GetPtr());
    }
    checkCudaErrors(cudaEventRecord(stop));
    checkCudaErrors(cudaEventSynchronize(stop));
    checkCudaErrors(cudaEventElapsedTime(&time_ms, start, stop));
    checkCudaErrors(cudaEventDestroy(start));
    checkCudaErrors(cudaEventDestroy(stop));

    double gbps = ((double)((GRD_SIZE*BLK_SIZE*UNROLL) * sizeof(float2)) / 1e9) /
                  ((double)time_ms / BENCH_ITER / 1e3);
    printf("Global Memory Bandwidth: %lfGB/s\n", gbps);
}

// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/globalMem_bandwidth_float2 globalMem_bandwidth_float2.cu

// 驱动调试
// nvcc --keep --keep-dir midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/globalMem_bandwidth_float2 globalMem_bandwidth_float2.cu
// cuasm --bin2asm midRes/globalMem_bandwidth_float2.sm_86.cubin -o midRes/globalMem_bandwidth_float2.sm_86.cuasm

// cuasm --asm2bin midRes/globalMem_bandwidth_float2.sm_86.cuasm -o midRes/globalMem_bandwidth_float2.sm_86.cubin 


// GRD_SIZE 90000 的结果
// Global Memory Bandwidth: 321.044992GB/s
