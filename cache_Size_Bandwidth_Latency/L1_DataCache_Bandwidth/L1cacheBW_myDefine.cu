#include "helper_cuda.h"
#include "cuptr.hpp"
#include "hostptr.hpp"

#include <cuda_runtime.h>
#include <cuda.h>

#include <iostream>
#include <cstdio>

#define WARP_SIZE 32
// Bytes for total L1/SharedMem is 128*1024; L1 max is 128*1024B
#define N_DATA 96 * 256
#define BLK_SIZE 1024
#define GRD_SIZE 1


__host__ void assignData(float *posArray){
    for(int i = 0; i < N_DATA; i++){
        posArray[i] = 1;
    }
}

__device__ __forceinline__
float ldg_ca(const void *ptr) {
    float ret;
    asm volatile (
        "ld.global.ca.b32 %0, [%1];"
        : "=f"(ret)
        : "l"(ptr)
    );
    return ret;
}

__global__ void L1DatacacheBW_test_kernel(uint32_t *startClk, uint32_t *stopClk, float *dsink, float *Arr){
    int tid = threadIdx.x;
    const float *ldg_ptr = Arr + tid;

    float sink = 0;
    // 通过填充 L1 缓存来预热 且 保证L1缓存了全部数据
    for (int i = 0; i < N_DATA; i += WARP_SIZE) {
        sink += ldg_ca(ldg_ptr + i);
    }
    asm volatile ("bar.sync 0;");

    sink = 0;
    uint32_t start = 0;
    asm volatile ("mov.u32 %0, %%clock;" :"=r"(start) :: "memory");

    for (int i = 0; i < N_DATA; i += WARP_SIZE) {
        sink += ldg_ca(ldg_ptr + i);
    }

    uint32_t stop = 0;
    asm volatile ("mov.u32 %0, %%clock;" : "=r"(stop) :: "memory");

    startClk[tid] = start;
    stopClk[tid]= stop;
    dsink[tid]= sink;
}

int main(){
    HostPtr<float> arr_h(N_DATA);
    assignData(arr_h.GetPtr());
    CuPtr<float> arr_d(arr_h);
    CuPtr<float> sink_d(BLK_SIZE);
    CuPtr<uint32_t> startClk_d(BLK_SIZE);
    CuPtr<uint32_t> stopClk_d(BLK_SIZE);

    L1DatacacheBW_test_kernel<<<1, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), sink_d.GetPtr(), arr_d.GetPtr());
    cudaDeviceSynchronize();
   
    HostPtr<uint32_t> startClk_h;
    HostPtr<uint32_t> stopClk_h;
    HostPtr<float> sink_h;
    startClk_d.ToHostPtr(startClk_h);
    stopClk_d.ToHostPtr(stopClk_h);
    sink_d.ToHostPtr(sink_h);

    float clockCycles_avg = 0.0;
    float sink_total = 0.0;
    for(int i = 0; i < BLK_SIZE; i++){
        clockCycles_avg += stopClk_h(i) - startClk_h(i);
        // std::cout << h_startClk[i] << " " << h_stopClk[i] << std::endl;
        sink_total += sink_h(i);
    }
    clockCycles_avg /= BLK_SIZE;

    std::cout << "clockCycles_avg: " << clockCycles_avg << std::endl;
    std::cout << "sink_total: " << sink_total << std::endl;
    // Block加载了全部的L1 cache Data
    uint32_t BytesAll = N_DATA * sizeof(float) * (BLK_SIZE/WARP_SIZE);  //  
    // 理论上限是64B 16个LD_ST单元 * 4B/LD_ST单元/周期 实测结果是 65B左右
    float BpCpSM = BytesAll / clockCycles_avg;
    std::cout << "L1 Data cache Bandwidth is  " << BpCpSM <<  " Bytes per cycle per SM" << std::endl;
    std::cout << "L1 Data cache Bandwidth is  " << BpCpSM * 1.7 <<  " GBps per SM" << std::endl;
}

// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/L1cacheBW_myDefine L1cacheBW_myDefine.cu

// nvcc --keep --keep-dir midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/L1cacheBW_myDefine L1cacheBW_myDefine.cu
// cuasm --bin2asm midRes/L1cacheBW_myDefine.sm_86.cubin -o midRes/L1cacheBW_myDefine.sm_86.cuasm


// 512: L1 Data cache Bandwidth is  63.7894 Bytes per cycle per SM
// 1024: L1 Data cache Bandwidth is  65.3869 Bytes per cycle per SM