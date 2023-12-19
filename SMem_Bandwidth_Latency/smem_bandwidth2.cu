#include "helper_cuda.h"
#include "hostptr.hpp"
#include "cuptr.hpp"

#include <cuda_runtime.h>
#include <cuda.h>

#include <iostream>
#include <cstdio>

#define GRD_SIZE 1
#define BLK_SIZE 1024
// 一个Block的共享内存上限是48KB 1<<15是32KB
#define SMEM_SIZE (1<<11)
#define WARP_SIZE 32
#define WARMUP 100


__global__ void SMem_writeBW_test_kernel(uint32_t *startClk, uint32_t *stopClk, float *out){
    int tid = threadIdx.x;
    __shared__ float4 Arr[SMEM_SIZE+BLK_SIZE]; // 很极限
    float4 reg = make_float4(tid+1.0, tid+2.0, tid+3.0, tid+4.0);

    uint32_t start = 0;
    asm volatile ("mov.u32 %0, %%clock;" :"=r"(start) :: "memory");

    for(int i = 0; i < SMEM_SIZE; i += WARP_SIZE){
        Arr[tid + i] = reg;
    }

    uint32_t stop = 0;
    asm volatile ("mov.u32 %0, %%clock;" : "=r"(stop) :: "memory");
    asm volatile ("bar.sync 0;");

    startClk[tid] = start;
    stopClk[tid]= stop;
    float tmp = ((float*)Arr)[tid];
    if(tmp < 0){
        *out = tmp;
    }
}

int main(){
    CuPtr<float> out_d(SMEM_SIZE + BLK_SIZE);
    CuPtr<uint32_t> startClk_d(BLK_SIZE);
    CuPtr<uint32_t> stopClk_d(BLK_SIZE);

    for (int i = 0; i < WARMUP; ++i) {
        SMem_writeBW_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr());
    }
    cudaDeviceSynchronize();

    SMem_writeBW_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr());
    cudaDeviceSynchronize();
   
    HostPtr<uint32_t> startClk_h;
    HostPtr<uint32_t> stopClk_h;
    HostPtr<float> out_h;
    startClk_d.ToHostPtr(startClk_h);
    stopClk_d.ToHostPtr(stopClk_h);
    out_d.ToHostPtr(out_h);

    float clockCycles_avg = 0.0;
    float out_total = 0.0;
    for(int i = 0; i < BLK_SIZE; i++){
        clockCycles_avg += stopClk_h(i) - startClk_h(i);
        // std::cout << h_startClk[i] << " " << h_stopClk[i] << std::endl;
        out_total += out_h(i);
    }
    clockCycles_avg /= BLK_SIZE;

    std::cout << "clockCycles_avg: " << clockCycles_avg << std::endl;
    std::cout << "out_total: " << out_total << std::endl;
    // Block加载了全部的L1 cache Data
    uint32_t BytesAll = SMEM_SIZE * sizeof(float4) * (BLK_SIZE/WARP_SIZE);  // * (BLK_SIZE/WARP_SIZE);   //  * BLK_SIZE;
    //
    float BpCpSM = BytesAll / clockCycles_avg;
    std::cout << "Shared Mem Bandwidth is  " << BpCpSM <<  " Bytes per cycle per SM" << std::endl;
    std::cout << "Shared Mem Bandwidth is  " << BpCpSM * 1.7 <<  " GBps per SM" << std::endl;
}

// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/smem_bandwidth2 smem_bandwidth2.cu

// nvcc --keep --keep-dir midRes_2 -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/smem_bandwidth2 smem_bandwidth2.cu
// cuasm --bin2asm midRes_2/smem_bandwidth2.sm_86.cubin -o midRes_2/smem_bandwidth2.sm_86.cuasm