

#define ARR_SIZE 1024
float A[ARR_SIZE];

__host__ void assignData(int stride){
    for(int i = 0; i < ARR_SIZE; i++){
        A[i] = (i+stride) % ARR_SIZE;
    }
}

__global__ void P_chase(int n_iter, float* res){

    uint32_t start_time;
    asm volatile ("mov.u32 %0, %%clock;" :"=r"(start_time) :: "memory");

    float sum = 0;
    float j = 0;
    for(int it = 0; it < n_iter; it++){
        j = A[j];
        sum += j;
    }

    uint32_t stop_time;
    asm volatile ("mov.u32 %0, %%clock;" :"=r"(stop_time) :: "memory");

    if(){
        *res = sum;
    }
}

int main(){

    std::cout << "WarmUping ..." << std::endl;
    P_chase<<<>>>();
    cudaDeviceSynchronize();

    std::cout << "Running ..." << std::endl;
    P_chase<<<>>>();
}