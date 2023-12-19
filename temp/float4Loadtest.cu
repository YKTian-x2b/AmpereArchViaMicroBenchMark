#include "helper_cuda.h"
#include "cuptr.hpp"
#include "hostptr.hpp"

#include <cuda_runtime.h>
#include <cuda.h>

#include <iostream>
#include <cstdio>

#define GRD_SIZE 1
#define BLK_SIZE 128
#define N_DATA 1024

// __device__ __forceinline__
// float ldg_cg(const void *ptr) {
//     float ret;
//     asm volatile (
//         "ld.global.cg.f32 %0, [%1];"
//         : "=f"(ret)
//         : "l"(ptr)
//     );
//     return ret;
// }

__global__ void float4Loadtest(float* gloArr, float* res){
    int tid = threadIdx.x;
    float4 *ldg_ptr = (float4 *)(gloArr + tid);
    float4 reg = *ldg_ptr;
    *res = reg.x + reg.y + reg.z + reg.w;

    __syncthreads();
    reg = *(ldg_ptr+1);
    *res = reg.x + reg.y + reg.z + reg.w;
}

int main(){
    CuPtr<float> gloArr(N_DATA+4);
    gloArr.SetZeros();
    CuPtr<float> res(N_DATA);
    float4Loadtest<<<GRD_SIZE, BLK_SIZE>>>(gloArr.GetPtr(), res.GetPtr());
}

// nvcc --keep --keep-dir midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda float4Loadtest.cu -o float4Loadtest
// cuasm --bin2asm midRes/float4Loadtest.sm_86.cubin