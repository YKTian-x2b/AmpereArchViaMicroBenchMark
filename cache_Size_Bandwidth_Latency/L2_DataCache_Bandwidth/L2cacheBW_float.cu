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
// 希望是90（SM个数 * 一个SM能启动的ThreadBlock数） 的倍数，且要超大才能形成有效流水线
#define GRD_SIZE 90000
#define UNROLL 16
// L2 cache size 3*1024*1024字节 3*1024*256个元素
const size_t N_DATA = 2*1024*256;

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

__global__ void L2cacheBW_float_kernel(const float *Arr, float *out) {
    int offset = (BLK_SIZE * UNROLL * blockIdx.x + threadIdx.x) % N_DATA;
    const float *ldg_ptr = Arr + offset;
    float sum = 0;

    #pragma unroll
    for (int i = 0; i < UNROLL; ++i) {
        sum += ldg_cg(ldg_ptr + BLK_SIZE * i);
    }

    if(sum != 0){
        *out = sum;
    }
}

int main(){
    // 添加尾数据，保证核函数正确且干净。
    HostPtr<float> arr_h(N_DATA + BLK_SIZE * UNROLL);
    arr_h.SetZeros();
    CuPtr<float> arr_d(arr_h);
    CuPtr<float> out_d(BLK_SIZE);

    std::cout << "Warming Up ..." << std::endl;
    // warm up to cache data into L2
    for (int i = 0; i < WARMUP_ITER; ++i) {
        L2cacheBW_float_kernel<<<GRD_SIZE, BLK_SIZE>>>(arr_d.GetPtr(), out_d.GetPtr());
    }

    cudaEvent_t start, stop;
    checkCudaErrors(cudaEventCreate(&start));
    checkCudaErrors(cudaEventCreate(&stop));
    float time_ms;
    std::cout << "Running ..." << std::endl;
    checkCudaErrors(cudaEventRecord(start));
    for (int i = 0; i < BENCH_ITER ; ++i) {
        L2cacheBW_float_kernel<<<GRD_SIZE, BLK_SIZE>>>(arr_d.GetPtr(), out_d.GetPtr());
    }
    checkCudaErrors(cudaEventRecord(stop));
    checkCudaErrors(cudaEventSynchronize(stop));
    checkCudaErrors(cudaEventElapsedTime(&time_ms, start, stop));
    checkCudaErrors(cudaEventDestroy(start));
    checkCudaErrors(cudaEventDestroy(stop));

    double gbps = ((double)((GRD_SIZE*BLK_SIZE*UNROLL) * sizeof(float)) / 1e9) /
                  ((double)time_ms / BENCH_ITER / 1e3);
    printf("L2 cache bandwidth: %lfGB/s\n", gbps);
}

// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/L2cacheBW_float L2cacheBW_float.cu

// 驱动调试
// nvcc --keep --keep-dir midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/L2cacheBW_float L2cacheBW_float.cu
// cuasm --bin2asm midRes/L2cacheBW_float.sm_86.cubin -o midRes/L2cacheBW_float.sm_86.cuasm 


// GRD_SIZE90000的结果
// L2 cache bandwidth: 1276.236447GB/s
// GRD_SIZE9000的结果
// L2 cache bandwidth: 1126.735069GB/s
