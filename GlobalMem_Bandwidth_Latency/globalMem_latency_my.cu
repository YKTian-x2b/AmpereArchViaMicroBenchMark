#include "helper_cuda.h"
#include "hostptr.hpp"
#include "cuptr.hpp"

#include <cuda.h>
#include <cuda_runtime.h>
#include <iostream>
#include <fstream>
#include <cstdio>

#define GRD_SIZE 1
#define BLK_SIZE 32
#define WARM_UP 100
#define UNROLL 10

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


__global__ void gloMem_latency_test_kernel(uint32_t *startClk, uint32_t *stopClk, uint32_t *out, uint32_t* arr){
    int tid = threadIdx.x;
    uint32_t offset = tid;
    // uint32_t *lg_ptr = arr+offset;

    uint32_t start, stop;
    asm volatile ("bar.sync 0;");
    asm volatile ("mov.u32 %0, %%clock;" :"=r"(start) :: "memory");

    #pragma unroll
    for(int i = 0; i < UNROLL; i++){
        // offset = ldg_cv(arr+offset);
        // offset = ldg_cg(arr+offset);
        // offset = ldg_ca(arr+offset);
        offset = ldg_nc(arr+offset);

        // asm volatile (
        //     "ld.global.ca.b32 %0, [%1];"
        //     : "=r"(offset)
        //     : "l"(lg_ptr)
        // );
        // lg_ptr += offset;

        // offset = arr[offset];
    }

    asm volatile ("mov.u32 %0, %%clock;" : "=r"(stop) :: "memory");

    startClk[tid] = start;
    stopClk[tid] = stop;

    if(offset == ~0x0){
        *out = offset;
    }
}

void gloMem_latency_test_run(uint32_t STRIDE){
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

    // // warmup i-cache
    // for(int i = 0; i < WARM_UP; i++){
    //     gloMem_latency_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr(), arr_d.GetPtr());
    // }
    // cudaDeviceSynchronize();

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
        // std::cout << startClk_h(i) << " " << stopClk_h(i) << std::endl;
        clockCycles_avg += stopClk_h(i) - startClk_h(i);
    }
    clockCycles_avg /= (BLK_SIZE * UNROLL);
    std::cout << "stride: " << STRIDE << ", global memory load latency: " << clockCycles_avg << " cycles" << std::endl;
    // // 不能用
    // std::string path("res/globalMem_latency_res1.txt");
    // std::ofstream fout(path); 
	// std::streambuf* pOld = std::cout.rdbuf(fout.rdbuf());
}

void doTest(){
    // for(int i = 256*256; i < 1024*1024*4; i += 256*256){
    //     gloMem_latency_test_run(i);
    // }

    // for(int i = 1; i < 128; i++){
    //     gloMem_latency_test_run(i);
    // }
    
    gloMem_latency_test_run(1024*256);
    // gloMem_latency_test_run(2*1024*256);
    // gloMem_latency_test_run(3*1024*256);
    // gloMem_latency_test_run(4*1024*256);
}

int main(){
    doTest();
}


// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/globalMem_latency_my globalMem_latency_my.cu

// nvcc --keep --keep-dir latency_midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/globalMem_latency_my globalMem_latency_my.cu
// cuasm --bin2asm latency_midRes/globalMem_latency_my.sm_86.cubin -o latency_midRes/globalMem_latency_my.sm_86.cuasm