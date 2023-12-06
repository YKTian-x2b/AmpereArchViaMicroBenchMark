

#define ARR_SIZE 1024
float A[ARR_SIZE];

__host__ void assignData(int stride){
    for(int i = 0; i < ARR_SIZE; i++){
        A[i] = (i+stride) % ARR_SIZE;
    }
}

__global__ void FG_P_chase(int n_iter, float* res){

    __shared__ unsigned int s_tvalue[];
    __shared__ unsigned int s_index[];

    float sum = 0;
    float j = 0;
    for(int it = 0; it < n_iter; it++){
        uint32_t start_time;
        asm volatile ("mov.u32 %0, %%clock;" :"=r"(start_time) :: "memory");

        j = A[j];
        s_index[it] = j;
        sum += j;

        uint32_t stop_time;
        asm volatile ("mov.u32 %0, %%clock;" :"=r"(stop_time) :: "memory");
        s_tvalue[it] = stop_time - start_time;
    }

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