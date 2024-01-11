#include "cuptr.hpp"
#include "hostptr.hpp"
#include "helper_cuda.h"

#include <cuda_runtime.h>
#include <cuda.h>
#include <iostream>
#include <cstdio>

#define GRD_SIZE 1
#define BLK_SIZE 32
#define UNROLL 100
#define WARM_UP 100
// 字节步幅为32MB 
#define STRIDE (4 * 1024 * 1024)

__device__ __forceinline__
void ldg_cg(void **&ldg_ptr) {
    asm volatile (
        "ld.global.cg.b64 %0, [%0];\n"
        : "+l"(ldg_ptr)
        : : "memory"
    );
}

__global__ void L2_TLB_detect_kernel(uint32_t *startClk, uint32_t *stopClk, void **out, void **arr){
    int tid = threadIdx.x;
    void **ldg_ptr = arr +  tid;
    // populate L2 cache
    #pragma unroll
    for(int i = 0; i < UNROLL; i++){
        ldg_cg(ldg_ptr);
    } 

    ldg_ptr = arr+tid;
    uint32_t start, stop;
    asm volatile ("bar.sync 0;");
    asm volatile ("mov.u32 %0, %%clock;" :"=r"(start) :: "memory");

    #pragma unroll
    for(int i = 0; i < UNROLL; i++){
        ldg_cg(ldg_ptr);
    }  
    
    asm volatile ("mov.u32 %0, %%clock;" : "=r"(stop) :: "memory");

    startClk[tid] = start;
    stopClk[tid] = stop;

    if(ldg_ptr == nullptr){
        *out = ldg_ptr;
    }
}

void L2_TLB_detect_run(uint32_t ARR_SIZE_IN_M){
    if(ARR_SIZE_IN_M > 384){
        // 用两次memcpy将数组传递到全局内存中
        uint32_t ARR_SIZE_one = 384 * 1024 * 1024;
        uint32_t ARR_SIZE_two = (ARR_SIZE_IN_M - 384) * 1024 * 1024;
        CuPtr<void*> arr_one_d(ARR_SIZE_one);
        CuPtr<void*> arr_two_d(ARR_SIZE_two);
        HostPtr<void*> arr_one_h(ARR_SIZE_one);
        HostPtr<void*> arr_two_h(ARR_SIZE_two);
        void **arr_one_h_ptr = arr_one_h.GetPtr();
        void **arr_two_h_ptr = arr_two_h.GetPtr();
        void **arr_one_d_ptr = arr_one_d.GetPtr();
        void **arr_two_d_ptr = arr_two_d.GetPtr();

        // // 这俩数组就是连续的
        // printf("arr_one_d_ptr: %p\n", arr_one_d_ptr);
        // printf("arr_two_d_ptr: %p\n", arr_two_d_ptr);

        // 数组1的最后STRIDE个元素指向数组2的前STRIDE个元素
        for(int i = 0; i < ARR_SIZE_one; i++){
            uint32_t offset = i + STRIDE;
            if(offset >= ARR_SIZE_one){
                arr_one_h_ptr[i] = (void*)(arr_two_d_ptr + (offset - ARR_SIZE_one));
            }
            else{
                arr_one_h_ptr[i] = (void*)(arr_one_d_ptr + offset);
            }
        }
        // 数组2的最后STRIDE个元素指向数组1的前STRIDE个元素
        for(int i = 0; i < ARR_SIZE_two; i++){
            uint32_t offset = i + STRIDE;
            if(offset >= ARR_SIZE_two){
                arr_two_h_ptr[i] = (void*)(arr_one_d_ptr + (offset - ARR_SIZE_two));
            }
            else{
                arr_two_h_ptr[i] = (void*)(arr_two_d_ptr + offset);
            }
        }
        uint32_t arrBytes_one = ARR_SIZE_one * sizeof(void*);
        uint32_t arrBytes_two = ARR_SIZE_two * sizeof(void*);
        checkCudaErrors(cudaMemcpy(arr_one_d_ptr, arr_one_h_ptr, arrBytes_one, cudaMemcpyHostToDevice));
        checkCudaErrors(cudaMemcpy(arr_two_d_ptr, arr_two_h_ptr, arrBytes_two, cudaMemcpyHostToDevice));
        
        CuPtr<void*> out_d(BLK_SIZE);
        CuPtr<uint32_t> startClk_d(BLK_SIZE);
        CuPtr<uint32_t> stopClk_d(BLK_SIZE);

        // warmup i-cache
        for(int i = 0; i < WARM_UP; i++){
            L2_TLB_detect_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr(), arr_two_d_ptr);
        }
        cudaDeviceSynchronize();

        // 
        L2_TLB_detect_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr(), arr_two_d_ptr);
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
        std::cout << "ARR_SIZE_IN_MB: " << (ARR_SIZE_IN_M * 8) << ", Global Mem access latency: " << clockCycles_avg << " cycles" << std::endl;
    }
    else{
        uint32_t ARR_SIZE = ARR_SIZE_IN_M * 1024 * 1024;

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
            L2_TLB_detect_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr(), arr_d.GetPtr());
        }
        cudaDeviceSynchronize();

        // 
        L2_TLB_detect_kernel<<<GRD_SIZE, BLK_SIZE>>>(startClk_d.GetPtr(), stopClk_d.GetPtr(), out_d.GetPtr(), arr_d.GetPtr());
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
        std::cout << "ARR_SIZE_IN_MB: " << (ARR_SIZE_IN_M * 8) << ", Global Mem access latency: " << clockCycles_avg << " cycles" << std::endl;
    }
}

int main(){
    // 理论上应该是
    // 一个元素8B 数组字节大小上限为8192 + 1024 = 9216MB 元素上限为1152M
    // 从64M个元素(512MB) 每次递增64M(512MB) 一直到1152M个(9216MB)

    // 但是阉割版的3060只有不到6G的全局内存 数组字节大小上限为4096 + 1024 = 5120MB 元素上限为640M
    // 4096MB / 8B = 512M ; 3072MB / 8B = 3*128M = 384M
    // 6144MB/8B = 3*256 = 768M 就out of memory了。至此没有 L2TLB miss的情况。
    for(uint32_t arr_size = 64; arr_size < 768; arr_size += 64){
        L2_TLB_detect_run(arr_size);
    }
}


// nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/L2_TLB_detect L2_TLB_detect.cu