#include "helper_cuda.h"
#include "cuptr.hpp"
#include "hostptr.hpp"

#include <iostream>
#include <random>
#include <ctime>

#include "cublas_v2.h"

#define GRD_SIZE 900
#define BLK_SIZE 512
#define WARP_SIZE 32
// MAX Bytes for L2_SIZE is 3 * 1024 * 1024 B
#define L2_SIZE (GRD_SIZE * BLK_SIZE)

float posArray[L2_SIZE];

__host__ void assignData(){
    std::default_random_engine e;
    e.seed(time(0));
    std::uniform_real_distribution<float> u(1, 65536);
    for(int i = 0; i < L2_SIZE; i++){
        posArray[i] = i;
    }
}

// 与访存延迟相比，浮点加消耗的时间可以忽略不计。
__global__ void l2_bw(float *dsink, float *posArray){
    // 块和线程索引 
    uint32_t tid = threadIdx.x;
    uint32_t bid = blockIdx.x;
    //
    float sink = 0;

    // 从二级缓存中加载数据并累加
    for (uint32_t i = 0; i < L2_SIZE; i += BLK_SIZE) {
        float* ptr = posArray+i;
        // 每次warp都会加载二级缓存中的所有数据
        for (uint32_t j = 0; j < BLK_SIZE; j += WARP_SIZE){
            uint32_t offset = (tid+j)%BLK_SIZE;
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
    dsink[tid] = sink;
}

int main(){
    assignData();

    CuPtr<float> d_arr(L2_SIZE);
    CuPtr<float> dsink(BLK_SIZE);
    
    unsigned arrBytes = sizeof(float) * L2_SIZE;
    checkCudaErrors(cudaMemcpy(d_arr.GetPtr(), posArray, arrBytes, cudaMemcpyHostToDevice));

    std::cout << "WarmUp ing ..." << std::endl;
    l2_bw<<<GRD_SIZE, BLK_SIZE>>>(dsink.GetPtr(), d_arr.GetPtr());
    cudaDeviceSynchronize();

    cudaEvent_t startE, stopE;
    float elapsedTime;
    checkCudaErrors(cudaEventCreate(&startE));
    checkCudaErrors(cudaEventCreate(&stopE));
    std::cout << "Running ..." << std::endl;
    checkCudaErrors(cudaEventRecord(startE, 0));

    l2_bw<<<GRD_SIZE, BLK_SIZE>>>(dsink.GetPtr(), d_arr.GetPtr());

    checkCudaErrors(cudaEventRecord(stopE, 0));
    checkCudaErrors(cudaEvnetSynchronize(stopE));
    checkCudaErrors(cudaEventElapsedTime(&elapsedTime, event_start, event_stop));
    checkCudaErrors(cudaEventDestroy(event_start));
    checkCudaErrors(cudaEventDestroy(event_stop));

  
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
    float Bandwidth = (BytesAll / elapsedTime) * 1000;
    std::cout << "L2 data cache Bandwidth is: " << Bandwidth << "B/s" << std::endl;
    
}

// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/L2cacheBW L2cacheBW.cu