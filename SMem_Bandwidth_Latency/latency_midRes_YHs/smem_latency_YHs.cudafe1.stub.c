#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wcast-qual"
#define __NV_CUBIN_HANDLE_STORAGE__ static
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#include "smem_latency_YHs.fatbin.c"
extern void __device_stub__Z19smem_latency_kernelPKjPjS1_(const uint32_t *, uint32_t *, uint32_t *);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll(void) __attribute__((__constructor__));
void __device_stub__Z19smem_latency_kernelPKjPjS1_(const uint32_t *__par0, uint32_t *__par1, uint32_t *__par2){__cudaLaunchPrologue(3);__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaSetupArgSimple(__par2, 16UL);__cudaLaunch(((char *)((void ( *)(const uint32_t *, uint32_t *, uint32_t *))smem_latency_kernel)));}
# 9 "smem_latency_YHs.cu"
void smem_latency_kernel( const uint32_t *__cuda_0,uint32_t *__cuda_1,uint32_t *__cuda_2)
# 9 "smem_latency_YHs.cu"
{__device_stub__Z19smem_latency_kernelPKjPjS1_( __cuda_0,__cuda_1,__cuda_2);
# 56 "smem_latency_YHs.cu"
}
# 1 "latency_midRes_YHs/smem_latency_YHs.cudafe1.stub.c"
static void __nv_cudaEntityRegisterCallback( void **__T4) {  __nv_dummy_param_ref(__T4); __nv_save_fatbinhandle_for_managed_rt(__T4); __cudaRegisterEntry(__T4, ((void ( *)(const uint32_t *, uint32_t *, uint32_t *))smem_latency_kernel), _Z19smem_latency_kernelPKjPjS1_, 16); }
static void __sti____cudaRegisterAll(void) {  __cudaRegisterBinary(__nv_cudaEntityRegisterCallback);  }

#pragma GCC diagnostic pop
