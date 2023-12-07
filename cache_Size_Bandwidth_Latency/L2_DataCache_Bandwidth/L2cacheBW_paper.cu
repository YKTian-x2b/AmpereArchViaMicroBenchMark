#include "helper_cuda.h"
#include "cuptr.hpp"
#include "hostptr.hpp"

#include <iostream>

#define GRD_SIZE 900
#define BLK_SIZE 512
#define WARP_SIZE 32
// MAX Bytes for L2_SIZE is 3 * 1024 * 1024 B
#define L2_SIZE (GRD_SIZE * BLK_SIZE)

#define WARMUP_ITER 100
#define BENCH_ITER 100

float posArray[L2_SIZE];

__host__ void assignData(){
    for(int i = 0; i < L2_SIZE; i++){
        posArray[i] = i;
    }
}

// 与访存延迟相比，浮点加消耗的时间可以忽略不计。
__global__ void l2_bw1(float *dsink, float *posArray){
    // 块和线程索引 
    uint32_t tid = threadIdx.x;
    uint32_t bid = blockIdx.x;
    float sink = 0;
    // 从二级缓存中加载数据并累加
    for (uint32_t i = 0; i < L2_SIZE; i += BLK_SIZE) {
        float* ptr = posArray + i;
        // 每次warp都会加载二级缓存中的所有数据
        #pragma unroll
        for (uint32_t j = 0; j < BLK_SIZE; j += WARP_SIZE){
            uint32_t offset = (tid+j)%BLK_SIZE;
            asm volatile ("{\t\n"
                ".reg .f32 data;\n\t" 
                "ld.global.cg.f32 data, [%1];\n\t"
                "add.f32 %0, data, %0;\n\t"
                "}" : "+f"(sink) : "l"(ptr+offset) : "memory"
            );
        }
    }
    if(bid == 0)
        dsink[tid] = sink;
}

// 与访存延迟相比，浮点加消耗的时间可以忽略不计。
__global__ void l2_bw2(float *dsink, float *posArray){
    // 块和线程索引 
    uint32_t tid = threadIdx.x;
    uint32_t bid = blockIdx.x;
    float sink = 0;
    // 从二级缓存中加载数据并累加
    for (uint32_t i = 0; i < L2_SIZE; i += BLK_SIZE) {
        float* ptr = posArray + ((i + bid * BLK_SIZE) % L2_SIZE);
        // 每次warp都会加载二级缓存中的所有数据
        #pragma unroll
        for (uint32_t j = 0; j < BLK_SIZE; j += WARP_SIZE){
            uint32_t offset = (tid+j)%BLK_SIZE;
            asm volatile ("{\t\n"
                ".reg .f32 data;\n\t" 
                "ld.global.cg.f32 data, [%1];\n\t"
                "add.f32 %0, data, %0;\n\t"
                "}" : "+f"(sink) : "l"(ptr+offset) : "memory"
            );
        }
    }
    if(bid == 0)
        dsink[tid] = sink;
}

__global__ void l2_bw3(float *dsink, float *posArray){
    // 块和线程索引 
    uint32_t tid = threadIdx.x;
    uint32_t bid = blockIdx.x;
    float sink = 0;
    // 从二级缓存中加载数据并累加
    for (uint32_t i = 0; i < L2_SIZE; i += BLK_SIZE) {
        float* ptr = posArray + ((i + bid * BLK_SIZE) % L2_SIZE);
        // 每次warp都会加载二级缓存中的所有数据
        float reg[BLK_SIZE/WARP_SIZE];
        #pragma unroll
        for (uint32_t j = 0; j < BLK_SIZE; j += WARP_SIZE){
            uint32_t offset = (tid+j)%BLK_SIZE;
            float ret;
            asm volatile (
                "ld.global.cg.b32 %0, [%1];"
                : "=f"(ret)
                : "l"(ptr+offset)
            );
            reg[j/WARP_SIZE] = ret;
            // asm volatile ("{\t\n"
            //     ".reg .f32 data;\n\t" 
            //     "ld.global.cg.f32 data, [%1];\n\t"
            //     "add.f32 %0, data, %0;\n\t"
            //     "}" : "+f"(sink) : "l"(ptr+offset) : "memory"
            // );
        }
        #pragma unroll
        for (uint32_t j = 0; j < BLK_SIZE/WARP_SIZE; j += 1){
            sink += reg[j];
        }

    }
    if(bid == 0)
        dsink[tid] = sink;
}


int main(){
    assignData();

    CuPtr<float> d_arr(L2_SIZE);
    CuPtr<float> dsink(BLK_SIZE);
    
    unsigned arrBytes = sizeof(float) * L2_SIZE;
    checkCudaErrors(cudaMemcpy(d_arr.GetPtr(), posArray, arrBytes, cudaMemcpyHostToDevice));

    std::cout << "WarmUp ing ..." << std::endl;
    for(int i = 0; i < WARMUP_ITER; i++){
        l2_bw1<<<GRD_SIZE, BLK_SIZE>>>(dsink.GetPtr(), d_arr.GetPtr());
    }
    cudaDeviceSynchronize();

    cudaEvent_t startE, stopE;
    float elapsedTime;
    checkCudaErrors(cudaEventCreate(&startE));
    checkCudaErrors(cudaEventCreate(&stopE));
    std::cout << "Running ..." << std::endl;
    checkCudaErrors(cudaEventRecord(startE, 0));
    for(int i = 0; i < BENCH_ITER; i++){
        l2_bw1<<<GRD_SIZE, BLK_SIZE>>>(dsink.GetPtr(), d_arr.GetPtr());
    }
    checkCudaErrors(cudaEventRecord(stopE, 0));
    checkCudaErrors(cudaEventSynchronize(stopE));
    checkCudaErrors(cudaEventElapsedTime(&elapsedTime, startE, stopE));
    checkCudaErrors(cudaEventDestroy(startE));
    checkCudaErrors(cudaEventDestroy(stopE));

    std::cout << "elapsedTime: " << elapsedTime << "ms" << std::endl;
  
    HostPtr<float> hsink;
    dsink.ToHostPtr(hsink);
    float sink_total = 0.0;
    for(int i = 0; i < BLK_SIZE; i++){
        sink_total += hsink(i);
    }
    std::cout << "sink_total: " << sink_total << std::endl;

    // 每个warp都会加载一级缓存中的所有数据
    unsigned long long  BytesAll = L2_SIZE * sizeof(float) * (GRD_SIZE * BLK_SIZE / WARP_SIZE); 
    // 理论上限 16个LD_ST单元 * 30个SM * 4B/LD_ST单元/周期 * 1702M = 3.26784TB/s
    float Bandwidth = (BytesAll / (elapsedTime/BENCH_ITER)) / 1000000;
    
    std::cout << "L2 data cache Bandwidth is: " << Bandwidth << "GB/s" << std::endl;
    
}

// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/L2cacheBW_my2 L2cacheBW_my2.cu


// nvcc --keep --keep-dir midRes_paper -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/L2cacheBW_my2 L2cacheBW_my2.cu

// cuasm --bin2asm midRes_paper/L2cacheBW_my2.sm_86.cubin midRes_paper/L2cacheBW_my2.sm_86.cuasm


// GRD_SIZE 9000的结果
// elapsedTime: 255733ms
// sink_total: 1.69868e+14
// L2 data cache Bandwidth is: 1037.88GB/s

// GRD_SIZE 900的结果
// elapsedTime: 2263.39ms
// sink_total: 1.69869e+12
// L2 data cache Bandwidth is: 1172.67GB/s