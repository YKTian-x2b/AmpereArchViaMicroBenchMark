#include <iostream>
#include <cstdio>

const int L2_FLUSH_SIZE = (1 << 20) * 128;

template <int BLOCK>
__global__ void flush_l2_kernel(const int *x, int *y) {
    int warp_id = threadIdx.x / 32;
    int lane_id = threadIdx.x % 32;

    const int *x_ptr = x + blockIdx.x * BLOCK + warp_id * 32;
    int sum = 0;

    #pragma unroll
    for (int i = 0; i < 32; ++i) {
        const int *ldg_ptr = x_ptr + (lane_id ^ i);

        asm volatile (
            "{.reg .s32 val;\n"
            " ld.global.cg.b32 val, [%1];\n"
            " add.s32 %0, val, %0;}\n"
            : "+r"(sum) : "l"(ldg_ptr)
        );
    }

    if (sum != 0) {
        *y = sum;
    }
}

void flush_l2() {
    int *x;
    int *y;
    cudaMalloc(&x, L2_FLUSH_SIZE);
    cudaMalloc(&y, sizeof(int));
    cudaMemset(x, 0, L2_FLUSH_SIZE);

    int n = L2_FLUSH_SIZE / sizeof(int);
    flush_l2_kernel<128><<<n / 128, 128>>>(x, y);

    cudaFree(x);
    cudaFree(y);
}


int main(){
    flush_l2();
}

