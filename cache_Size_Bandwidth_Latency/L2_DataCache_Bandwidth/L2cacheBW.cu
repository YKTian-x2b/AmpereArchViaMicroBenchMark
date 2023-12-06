#include "helper_cuda.h"
#include "cuptr.hpp"
#include "hostptr.hpp"

#include <iostream>
#include <random>
#include <ctime>

#include "cublas_v2.h"

// Bytes for L2_SIZE is 3 * 1024 * 1024 B
#define L2_SIZE 1024 * 256
#define GRD_SIZE 1800
#define THREADS_NUM 512
#define WARP_SIZE 32

float posArray[L2_SIZE];

__host__ void assignData(){
    std::default_random_engine e;
    e.seed(time(0));
    std::uniform_real_distribution<float> u(1, 65536);
    for(int i = 0; i < L2_SIZE; i++){
        posArray[i] = i;
    }
}

__global__ void l2_bw(uint32_t *startClk, uint32_t *stopClk, float *dsink, float *posArray){
    // 块和线程索引 
    uint32_t tid = threadIdx.x;
    uint32_t bid = blockIdx.x;
    //
    float sink = 0;
    // 通过填充 L2 缓存来预热 且保证L2缓存了全部数据
    for (uint32_t i = tid; i < L2_SIZE; i += THREADS_NUM) {
        float * ptr = posArray+i;
        // sink += *ptr;
        asm volatile ("{\t\n"
            ".reg .f32 data;\n\t"
            "ld.global.cg.f32 data, [%1];\n\t"
            "add.f32 %0, data, %0;\n\t"
            "}" : "+f"(sink) : "l"(ptr): "memory"
        );
    }
    // 同步所有线程
    asm volatile ("bar.sync 0;");
    // 开始计时 uint32_t
    uint32_t start = 0;
    asm volatile ("mov.u32 %0, %%clock;" :"=r"(start) :: "memory");
    // 从二级缓存中加载数据并累加
    for (uint32_t i = 0; i < L2_SIZE; i += THREADS_NUM) {
        float* ptr = posArray+i;
        // 每次warp都会加载二级缓存中的所有数据
        for (uint32_t j = 0; j < THREADS_NUM; j += WARP_SIZE){
            uint32_t offset = (tid+j)%THREADS_NUM;
            asm volatile ("{\t\n"
                ".reg .f32 data;\n\t" 
                "ld.global.cg.f32 data, [%1];\n\t"
                "add.f32 %0, data, %0;\n\t"
                "}" : "+f"(sink) :"l"(ptr+offset) :"memory"
            );
        }
    }
    // 同步所有线程
    asm volatile ("bar.sync 0;");
    // 停止计时 uint32_t
    uint32_t stop = 0;
    asm volatile ("mov.u32 %0, %%clock;" : "=r"(stop) :: "memory");
    // 将时间和数据写回内存
    startClk[tid] = start;
    stopClk[tid]= stop;
    dsink[tid] = sink;
}

int main(){
    assignData();

    CuPtr<float> d_arr(L2_SIZE);
    CuPtr<uint32_t> d_startClk(THREADS_NUM);
    CuPtr<uint32_t> d_stopClk(THREADS_NUM);
    CuPtr<float> dsink(THREADS_NUM);
    
    unsigned arrBytes = sizeof(float) * L2_SIZE;
    checkCudaErrors(cudaMemcpy(d_arr.GetPtr(), posArray, arrBytes, cudaMemcpyHostToDevice));

    l2_bw<<<GRD_SIZE, THREADS_NUM>>>(d_startClk.GetPtr(), d_stopClk.GetPtr(), dsink.GetPtr(), d_arr.GetPtr());
    cudaDeviceSynchronize();
   
    HostPtr<uint32_t> h_startClk;
    HostPtr<uint32_t> h_stopClk;
    HostPtr<float> hsink;
    d_startClk.ToHostPtr(h_startClk);
    d_stopClk.ToHostPtr(h_stopClk);
    dsink.ToHostPtr(hsink);

    float clockCycles_avg = 0.0;
    float sink_total = 0.0;
    for(int i = 0; i < THREADS_NUM; i++){
        clockCycles_avg += h_stopClk(i) - h_startClk(i);
        // std::cout << h_startClk(i) << " " << h_stopClk(i) << std::endl;
        sink_total += hsink(i);
    }
    clockCycles_avg /= THREADS_NUM;
    std::cout << h_startClk(0) << " " << h_stopClk(0) << std::endl;
    std::cout << "clockCycles_avg: " << clockCycles_avg << std::endl; 
    std::cout << "sink_total: " << sink_total << std::endl;
    // 每个warp都会加载一级缓存中的所有数据 一个SM启动了 128/32个warp 所以一共读取了BytesAll个字节 per SM
    uint32_t BytesAll = L2_SIZE * sizeof(float) * (THREADS_NUM / WARP_SIZE); 
    // 理论上限是64B 16个LD_ST单元 * 4B/LD_ST单元/周期 实测结果是62B左右
    float BpCpSM = BytesAll / clockCycles_avg;
    std::cout << "L2 real throughput is  " << BpCpSM <<  " Bytes per cycle per SM" << std::endl;
    float Bandwidth = BpCpSM * (THREADS_NUM / WARP_SIZE)
}

// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/L2cacheBW L2cacheBW.cu