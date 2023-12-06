#include "helper_cuda.h"
#include <iostream>
#include <random>
#include <ctime>
#include "cublas_v2.h"

// Bytes for total L1/SharedMem is 128*1024; L1 max is 128*1024B
#define L1_SIZE 96 * 256
#define THREADS_NUM 512
#define WARP_SIZE 32

float posArray[L1_SIZE];

__host__ void assignData(){
    std::default_random_engine e;
    e.seed(time(0));
    std::uniform_real_distribution<float> u(1, 65536);
    for(int i = 0; i < L1_SIZE; i++){
        posArray[i] = i;
    }
}

__global__ void l1_bw(uint32_t *startClk, uint32_t *stopClk, float *dsink, float *posArray){
    // 线程索引
    uint32_t tid = threadIdx.x;
    // 侧效变量，目的是避免编译器删除这段代码
    float sink = 0;
    // 通过填充 L1 缓存来预热 且 保证L1缓存了全部数据
    for (uint32_t i = tid; i < L1_SIZE; i += THREADS_NUM) {
        float * ptr = posArray+i;
        // sink += *ptr;
        asm volatile ("{\t\n"
        ".reg .f32 data;\n\t"
        "ld.global.ca.f32 data, [%1];\n\t"
        "add.f32 %0, data, %0;\n\t"
        "}" : "+f"(sink) : "l"(ptr): "memory"
        );
    }
    // 同步所有线程
    asm volatile ("bar.sync 0;");
    // 开始计时 uint32_t
    uint32_t start = 0;
    asm volatile ("mov.u32 %0, %%clock;" :"=r"(start) :: "memory");
    // 从 L1 缓存加载数据，累加
    for (uint32_t i = 0; i < L1_SIZE; i += THREADS_NUM) {
        float * ptr = posArray+i;
        // 每个warp都会加载一级缓存中的所有数据
        for (uint32_t j = 0; j < THREADS_NUM; j += WARP_SIZE) {
            uint32_t offset = (tid+j)%THREADS_NUM;
            // sink += ptr[offset];
            asm volatile ("{\t\n"
                ".reg .f32 data;\n\t" 
                "ld.global.ca.f32 data, [%1];\n\t"
                "add.f32 %0, data, %0;\n\t"
                "}" : "+f"(sink) : "l"(ptr+offset) : "memory"
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
    dsink[tid]= sink;
}

int main(){
    assignData();

    unsigned arrBytes = sizeof(float) * L1_SIZE;
    unsigned clkBytes = sizeof(uint32_t) * THREADS_NUM;
    unsigned sinkBytes = sizeof(float) * THREADS_NUM;

    uint32_t *d_startClk, *d_stopClk;
    float *d_arr, *dsink;
    uint32_t *h_startClk, *h_stopClk;
    float *hsink;

    checkCudaErrors(cudaMalloc(&d_arr, arrBytes));
    checkCudaErrors(cudaMalloc(&d_startClk, clkBytes));
    checkCudaErrors(cudaMalloc(&d_stopClk, clkBytes));
    checkCudaErrors(cudaMalloc(&dsink, sinkBytes));
    checkCudaErrors(cudaMemcpy(d_arr, posArray, arrBytes, cudaMemcpyHostToDevice));

    l1_bw<<<1, THREADS_NUM>>>(d_startClk, d_stopClk, dsink, d_arr);
    cudaDeviceSynchronize();
   
    h_startClk = (uint32_t*)malloc(clkBytes);
    h_stopClk = (uint32_t*)malloc(clkBytes);
    hsink = (float*)malloc(sinkBytes);
    checkCudaErrors(cudaMemcpy(h_startClk, d_startClk, clkBytes, cudaMemcpyDeviceToHost));
    checkCudaErrors(cudaMemcpy(h_stopClk, d_stopClk, clkBytes, cudaMemcpyDeviceToHost));
    checkCudaErrors(cudaMemcpy(hsink, dsink, sinkBytes, cudaMemcpyDeviceToHost));

    float clockCycles_avg = 0.0;
    float sink_total = 0.0;
    for(int i = 0; i < THREADS_NUM; i++){
        clockCycles_avg += h_stopClk[i] - h_startClk[i];
        // std::cout << h_startClk[i] << " " << h_stopClk[i] << std::endl;
        sink_total += hsink[i];
    }
    clockCycles_avg /= THREADS_NUM;
    std::cout << h_startClk[0] << " " << h_stopClk[0] << std::endl;
    std::cout << "clockCycles_avg: " << clockCycles_avg << std::endl; // 63433
    std::cout << "sink_total: " << sink_total << std::endl;
    // 每个warp都会加载一级缓存中的所有数据 一个SM启动了 128/32个warp 所以一共读取了BytesAll个字节 per SM
    uint32_t BytesAll = L1_SIZE * sizeof(float) * (THREADS_NUM / WARP_SIZE); 
    // 理论上限是64B 16个LD_ST单元 * 4B/LD_ST单元/周期 实测结果是62B左右
    float BpCpSM = BytesAll / clockCycles_avg;
    std::cout << "L1 real throughput is  " << BpCpSM <<  " Bytes per cycle per SM" << std::endl;

    checkCudaErrors(cudaFree(d_arr));
    checkCudaErrors(cudaFree(d_startClk));
    checkCudaErrors(cudaFree(d_stopClk));
    checkCudaErrors(cudaFree(dsink));
    free(h_startClk);
    free(h_stopClk);
    free(hsink);
}

// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/L1cacheBW L1cacheBW.cu