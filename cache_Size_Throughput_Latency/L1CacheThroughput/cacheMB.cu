// #include "../Common.cuh"
// #include <iostream>
// #include <random>
// #include <ctime>
// #include "cublas_v2.h"

// #define BLOCK_XY 64

// #define STRIDE 64

// #define ARRSIZE 2048
// int arr[ARRSIZE];

// __host__ void assignData(){
//     std::default_random_engine e;
//     e.seed(time(0));
//     std::uniform_real_distribution<int> u(-65536, 65536);
//     for(int i = 0; i < ARRSIZE; i++){
//         arr[i] = u(e);
//     }
// }

// // for L1 cache
// __global__ void L1cacheMB(int * arr){
//     int idx = blockIdx.x * blockDim.x + threadIdx.x;
//     int x = arr[idx];
// }

// float L1cacheMB_run(int * d_arr, cudaEvent_t &event_start, cudaEvent_t &event_stop)
// {
//     dim3 blockDim(BLOCK_XY);
//     dim3 gridDim(1);

//     float elapsedTime;
//     CHECK(cudaEventRecord(event_start, 0));

//     L1cacheMB<<<gridDim, blockDim>>>(d_arr);

//     CHECK(cudaEventRecord(event_stop, 0));
//     CHECK(cudaEventSynchronize(event_stop));

//     CHECK(cudaEventElapsedTime(&elapsedTime, event_start, event_stop));
//     return elapsedTime;
// }

// int main(){
//     assignData();
//     int * d_arr;
//     unsigned arrBytes = sizeof(int) * ARRSIZE;
//     CHECK(cudaMalloc(&d_arr, arrBytes));
//     CHECK(cudaMemcpy(d_arr, A, arrBytes, cudaMemcpyHostToDevice));

//     cudaEvent_t event_start, event_stop;
//     CHECK(cudaEventCreate(&event_start));
//     CHECK(cudaEventCreate(&event_stop));

//     float elapsedTime = regbank_test_run();

//     CHECK(cudaEventDestroy(event_start));
//     CHECK(cudaEventDestroy(event_stop));
    
    
// }