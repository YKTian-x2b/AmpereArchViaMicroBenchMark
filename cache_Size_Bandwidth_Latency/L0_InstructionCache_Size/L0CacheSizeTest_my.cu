#include "helper_cuda.h"
#include "hostptr.hpp"
#include "cuptr.hpp"

#include <iostream>
#include <cstdio>
#include <cuda.h>
#include <cuda_runtime.h>

#define GRD_SIZE 1
#define BLK_SIZE 512
#define UNROLL 10

__global__ void L0CacheSize_test_kernel(){

}

int main(){

    // 预热L0/L1/L2 i-cache
    L0CacheSize_test_kernel<<<GRD_SIZE, BLK_SIZE>>>();
    cudaDeviceSynchronize();

    // run
    L0CacheSize_test_kernel<<<GRD_SIZE, BLK_SIZE>>>();
    cudaDeviceSynchronize();

}