#pragma once

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

template <typename T>
void check(T result, const char* const func, const char *const file, int const line){
    if(result){
        const cudaError_t error = result;
        fprintf(stderr, "CUDA error at %s:%d code=%d, reason: %s, \"%s\" \n", 
                    file, line, error, cudaGetErrorString(error), func);
        exit(EXIT_FAILURE);
    }
}

// 宏定义中 ##用来拼接字符串 #用来将宏参数做字符串操作
#define checkCudaErrors(val) check((val), #val, __FILE__, __LINE__)