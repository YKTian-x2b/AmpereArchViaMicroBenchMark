#include "cuptr.hpp"
#include "hostptr.hpp"
#include "helper_cuda.h"

#include <cuda_runtime.h>
#include <cuda.h>
#include <iostream>
#include <cstdio>

// 如果用物理地址访问L1cache，则会用到L1TLB，就会存在TLB未命中的情况。 L1TLB的覆盖范围大概是32MB。
// 开一个远大于 L1TLB 覆盖范围的数组 用足够大的步幅将要访问的元素缓存在L1cache中 但元素间隔会使 L1TLB 未命中
// 观察是否存在 L1TLB 未命中的情况，以确定L1cache indexed by 虚拟地址还是物理地址
#define GRD_SIZE 1
#define BLK_SIZE 32
// [10, 30, 50, 100, 200, 500]
#define UNROLL 100
#define WARM_UP 100
// 字节步幅为 L1 TLB entry大小 大概是2MB 
#define STRIDE (256 * 1024)

__device__ __forceinline__
void ldg_ca(void **&ldg_ptr) {
    asm volatile (
        "ld.global.ca.b64 %0, [%0];\n"
        : "+l"(ldg_ptr)
        : : "memory"
    );
}

__device__ __forceinline__
void ldg_cg(void **&ldg_ptr) {
    asm volatile (
        "ld.global.cg.b64 %0, [%0];\n"
        : "+l"(ldg_ptr)
        : : "memory"
    );
}

__global__ void L1_TLB_detect_kernel(uint32_t *startClk, uint32_t *stopClk, void **out, void **arr){
    int tid = threadIdx.x;
    void **ldg_ptr = arr +  tid;
    // populate L1 cache
    #pragma unroll
    for(int i = 0; i < UNROLL; i++){
        // 这里如果用ca结果无法解释,用cg可以看到类似TuringT4的情况
        // ldg_ca(ldg_ptr);
        ldg_cg(ldg_ptr);
    } 

    ldg_ptr = arr+tid;
    uint32_t start, stop;
    asm volatile ("bar.sync 0;");
    asm volatile ("mov.u32 %0, %%clock;" :"=r"(start) :: "memory");

    #pragma unroll
    for(int i = 0; i < UNROLL; i++){
        // 这里如果用ca结果无法解释,用cg可以看到类似TuringT4的情况
        // ldg_ca(ldg_ptr);
        ldg_cg(ldg_ptr);
    }  
    
    asm volatile ("mov.u32 %0, %%clock;" : "=r"(stop) :: "memory");

    startClk[tid] = start;
    stopClk[tid] = stop;

    if(ldg_ptr == nullptr){
        *out = ldg_ptr;
    }
}

void L1_TLB_detect_run(uint32_t ARR_SIZE_IN_K){
    uint32_t ARR_SIZE = 1024 * ARR_SIZE_IN_K;

    CuPtr<void*> arr_d(ARR_SIZE);
    HostPtr<void*> arr_h(ARR_SIZE);
    void **h_ptr = arr_h.GetPtr();
    void **d_ptr = arr_d.GetPtr();
    for(int i = 0; i < ARR_SIZE; i++){
        uint32_t offset = (i + STRIDE) % ARR_SIZE;
        h_ptr[i] = (void*)(d_ptr + offset);
    }
    uint32_t arrBytes = ARR_SIZE * sizeof(void*);
    checkCudaErrors(cudaMemcpy(d_ptr, h_ptr, arrBytes, cudaMemcpyHostToDevice));

    CuPtr<void*> out_d(BLK_SIZE);
    CuPtr<uint32_t> startClk_d(BLK_SIZE);
    CuPtr<uint32_t> stopClk_d(BLK_SIZE);

    // warmup i-cache
    for(int i = 0; i < WARM_UP; i++){
        L1_TLB_detect_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr(), arr_d.GetPtr());
    }
    cudaDeviceSynchronize();

    // 
    L1_TLB_detect_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr(), arr_d.GetPtr());
    cudaDeviceSynchronize();

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
    std::cout << "ARR_SIZE_IN_MB: " << (ARR_SIZE_IN_K * 8 / 1024) << ", Global Mem access latency: " << clockCycles_avg << " cycles" << std::endl;
    
}

int main(){
    // 一个元素8B 数组字节大小上限为512MB 元素上限为64M
    // 从128K个元素(1MB) 每次递增256K(2MB) 一直到128*128K个(128MB)
    for(uint32_t arr_size = 128; arr_size < 128 * 128; arr_size += 256){
        L1_TLB_detect_run(arr_size);
    }
    // 从128*128 K个元素(128MB) 每次递增1024K(8MB) 一直到64M(512MB)个
    for(uint32_t arr_size = 128 * 128; arr_size < 64 * 1024; arr_size +=1024){
        L1_TLB_detect_run(arr_size);
    }
}


// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/L1_TLB_detect L1_TLB_detect.cu

// python3 L1_TLB_detect_res_process.py