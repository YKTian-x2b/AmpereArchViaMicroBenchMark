#include "helper_cuda.h"
#include "cuptr.hpp"
#include "hostptr.hpp"

#include <cuda_runtime.h>
#include <cuda.h>

#include <iostream>
#include <cstdio>

#define WARP_SIZE 32
// 得保证数据能被L1_D-Cache装下
// Bytes for total L1/SharedMem is 128*1024B; L1 max is 128*1024B；这里用96*1024B；
#define N_DATA 96 * 256
#define BLK_SIZE 1024
#define GRD_SIZE 1

__host__ void assignData(float *posArray){
    for(int i = 0; i < N_DATA+BLK_SIZE; i++){
        posArray[i] = 1;
    }
}

__device__ __forceinline__
float ldg_ca(const void *ptr) {
    float ret;
    asm volatile (
        "ld.global.ca.f32 %0, [%1];"
        : "=f"(ret)
        : "l"(ptr)
    );
    return ret;
}

__global__ void L1DatacacheBW_test_kernel(uint32_t *startClk, uint32_t *stopClk, float *dsink, float *Arr){
    int tid = threadIdx.x;
    const float* ldg_ptr = Arr + tid;

    float sink = 0;
    // 保证L1缓存了全部数据
    for (int i = 0; i < N_DATA; i += WARP_SIZE) {
        sink += ldg_ca(ldg_ptr + i);
    }
    asm volatile ("bar.sync 0;");

    sink = 0;
    uint32_t start, stop;
    asm volatile ("mov.u32 %0, %%clock;" :"=r"(start) :: "memory");
    // LDG指令发射有4个cycle的间隔且 FADD和LDG不是一个port 所以TLP+ILP情况下 基本不影响满流水的形成
    for (int i = 0; i < N_DATA; i += WARP_SIZE) {
        sink += ldg_ca(ldg_ptr + i);
    }
    // 因为要小心准确的获取整个SM的吞吐，所以这里应该有一个同步，保证最后测得的时间间隔是整个Block的开始-结束时间，不是某个warp的，也不是所有warp的均值。
    // asm volatile ("bar.sync 0;");
    asm volatile ("mov.u32 %0, %%clock;" : "=r"(stop) :: "memory");

    startClk[tid] = start;
    stopClk[tid]= stop;
    dsink[tid]= sink;
}

int main(){
    // 为了让kernel的sass中ldg指令占比尽量高，我们把kernel写的干净一点，尾数据(+BLK_SIZE)最多可以保证每个thread读取全部数据而不出现问题
    HostPtr<float> arr_h(N_DATA+BLK_SIZE);
    assignData(arr_h.GetPtr());
    CuPtr<float> arr_d(arr_h);
    CuPtr<float> sink_d(BLK_SIZE);
    CuPtr<uint32_t> startClk_d(BLK_SIZE);
    CuPtr<uint32_t> stopClk_d(BLK_SIZE);
    // warm up
    L1DatacacheBW_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), sink_d.GetPtr(), arr_d.GetPtr());
    cudaDeviceSynchronize();

    // run
    L1DatacacheBW_test_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), sink_d.GetPtr(), arr_d.GetPtr());
    cudaDeviceSynchronize();
   
    HostPtr<uint32_t> startClk_h;
    HostPtr<uint32_t> stopClk_h;
    HostPtr<float> sink_h;
    startClk_d.ToHostPtr(startClk_h);
    stopClk_d.ToHostPtr(stopClk_h);
    sink_d.ToHostPtr(sink_h);

    uint32_t minStartClk = ~0x0;
    uint32_t maxStopClk = 0;
    float sink_total = 0.0;
    // 需要注意的是 每cycle字节数 需要cycle尽量精准。
    // 如果在kernel访存结束的时候没有同步Block，且这里用了均值时间，就会发现实测值超过理论值，就是因为用的时间不够精准。
    // 最佳方式应该是 在kernel访存结束的时候没有同步Block。
    // 这里选择的方式是不同步，但用最大时间间隔。
    for(int i = 0; i < BLK_SIZE; i++){
        sink_total += sink_h(i);
        if(startClk_h(i) < minStartClk){
            minStartClk = startClk_h(i);
        }
        if(stopClk_h(i) > maxStopClk){
            maxStopClk = stopClk_h(i);
        }
        // if(i % 32 == 0)
        //     std::cout << i << ": " << startClk_h(i) << " " << stopClk_h(i) << std::endl;
    }
    float clockCycles = maxStopClk - minStartClk;

    std::cout << "clockCycles: " << clockCycles << std::endl;
    std::cout << "sink_total: " << sink_total << std::endl;
    // warp加载了全部的L1 cache Data
    uint32_t BytesAll = N_DATA * sizeof(float) * (BLK_SIZE/WARP_SIZE);  // * (BLK_SIZE/WARP_SIZE);   //  * BLK_SIZE;
    float BpCpSM = BytesAll / clockCycles;
    std::cout << "L1 Data cache Bandwidth is  " << BpCpSM <<  " Bytes per cycle per SM" << std::endl;
    std::cout << "L1 Data cache Bandwidth is  " << BpCpSM * 1.7 <<  " GBps per SM" << std::endl;
}

// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/L1cacheBW_float L1cacheBW_float.cu

// nvcc --keep --keep-dir midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/L1cacheBW_float L1cacheBW_float.cu
// cuasm --bin2asm midRes/L1cacheBW_float.sm_86.cubin -o midRes/L1cacheBW_float.sm_86.cuasm

// L1 Data cache Bandwidth is  63.5629 Bytes per cycle per SM
// L1 Data cache Bandwidth is  108.057 GBps per SM