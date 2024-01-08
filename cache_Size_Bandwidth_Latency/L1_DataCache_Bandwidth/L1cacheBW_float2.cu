#include "helper_cuda.h"
#include "cuptr.hpp"
#include "hostptr.hpp"

#include <cuda_runtime.h>
#include <cuda.h>

#include <iostream>
#include <cstdio>

#define WARP_SIZE 32
// 得保证数据能被L1_D-Cache装下
// Bytes for total L1/SharedMem is 128*1024B; L1 max is 128*1024B；这里用64*1024B；
#define N_DATA 32 * 256
#define BLK_SIZE 1024
#define GRD_SIZE 1

__host__ void assignData(float2 *posArray){
    for(int i = 0; i < N_DATA+BLK_SIZE; i++){
        posArray[i] = make_float2(i+1.0, i+2.0);
    }
}

__device__ __forceinline__
float2 ldg_ca_v2(const void *ptr) {
    float2 ret;
    asm volatile (
        "ld.global.ca.v2.f32 {%0, %1}, [%2];"
        : "=f"(ret.x), "=f"(ret.y)
        : "l"(ptr)
    );
    return ret;
}

__global__ void L1DatacacheBW_test_kernel(uint32_t *startClk, uint32_t *stopClk, float2 *dsink, float2 *Arr){
    int tid = threadIdx.x;
    const float2* ldg_ptr = Arr + tid;

    float2 sink = make_float2(0.0, 0.0);
    // 保证L1缓存了全部数据
    for (int i = 0; i < N_DATA; i += BLK_SIZE) {
        float2 res = ldg_ca_v2(ldg_ptr + i);
        sink.y += res.x + res.y;
    }

    uint32_t start, stop;
    asm volatile ("bar.sync 0;");
    asm volatile ("mov.u32 %0, %%clock;" :"=r"(start) :: "memory");
    // LDG指令发射有4个cycle的间隔且 FADD和LDG不是一个port 所以TLP+ILP情况下 基本不影响满流水的形成
    #pragma unroll
    for (int i = 0; i < N_DATA; i += WARP_SIZE) {
        float2 res = ldg_ca_v2(ldg_ptr + i);
        sink.x += res.x + res.y;
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
    HostPtr<float2> arr_h(N_DATA+BLK_SIZE);
    assignData(arr_h.GetPtr());
    CuPtr<float2> arr_d(arr_h);
    CuPtr<float2> sink_d(BLK_SIZE);
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
    HostPtr<float2> sink_h;
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
        sink_total += sink_h(i).x;
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
    uint32_t BytesAll = N_DATA * sizeof(float2) * (BLK_SIZE/WARP_SIZE);  // * (BLK_SIZE/WARP_SIZE);   //  * BLK_SIZE;
    float BpCpSM = BytesAll / clockCycles;
    std::cout << "L1 Data cache Bandwidth is  " << BpCpSM <<  " Bytes per cycle per SM" << std::endl;
    std::cout << "L1 Data cache Bandwidth is  " << BpCpSM * 1.7 <<  " GBps per SM" << std::endl;
}

// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/L1cacheBW_float2 L1cacheBW_float2.cu

// nvcc --keep --keep-dir midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/L1cacheBW_float2 L1cacheBW_float2.cu
// cuasm --bin2asm midRes/L1cacheBW_float2.sm_86.cubin -o midRes/L1cacheBW_float2.sm_86.cuasm

// L1 Data cache Bandwidth is  124.652 Bytes per cycle per SM
// L1 Data cache Bandwidth is  211.909 GBps per SM