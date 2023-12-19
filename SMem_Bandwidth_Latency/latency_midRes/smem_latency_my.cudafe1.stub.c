#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wcast-qual"
#define __NV_CUBIN_HANDLE_STORAGE__ static
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#include "smem_latency_my.fatbin.c"
extern void __device_stub__Z27smem_ld_latency_test_kernelPjS_S_(uint32_t *, uint32_t *, uint32_t *);
extern void __device_stub__Z27smem_st_latency_test_kernelPjS_S_(uint32_t *, uint32_t *, uint32_t *);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll(void) __attribute__((__constructor__));
void __device_stub__Z27smem_ld_latency_test_kernelPjS_S_(uint32_t *__par0, uint32_t *__par1, uint32_t *__par2){__cudaLaunchPrologue(3);__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaSetupArgSimple(__par2, 16UL);__cudaLaunch(((char *)((void ( *)(uint32_t *, uint32_t *, uint32_t *))smem_ld_latency_test_kernel)));}
# 20 "smem_latency_my.cu"
void smem_ld_latency_test_kernel( uint32_t *__cuda_0,uint32_t *__cuda_1,uint32_t *__cuda_2)
# 20 "smem_latency_my.cu"
{__device_stub__Z27smem_ld_latency_test_kernelPjS_S_( __cuda_0,__cuda_1,__cuda_2);
# 58 "smem_latency_my.cu"
}
# 1 "latency_midRes/smem_latency_my.cudafe1.stub.c"
void __device_stub__Z27smem_st_latency_test_kernelPjS_S_( uint32_t *__par0,  uint32_t *__par1,  uint32_t *__par2) {  __cudaLaunchPrologue(3); __cudaSetupArgSimple(__par0, 0UL); __cudaSetupArgSimple(__par1, 8UL); __cudaSetupArgSimple(__par2, 16UL); __cudaLaunch(((char *)((void ( *)(uint32_t *, uint32_t *, uint32_t *))smem_st_latency_test_kernel))); }
# 61 "smem_latency_my.cu"
void smem_st_latency_test_kernel( uint32_t *__cuda_0,uint32_t *__cuda_1,uint32_t *__cuda_2)
# 61 "smem_latency_my.cu"
{__device_stub__Z27smem_st_latency_test_kernelPjS_S_( __cuda_0,__cuda_1,__cuda_2);
# 105 "smem_latency_my.cu"
}
# 1 "latency_midRes/smem_latency_my.cudafe1.stub.c"
static void __nv_cudaEntityRegisterCallback( void **__T4) {  __nv_dummy_param_ref(__T4); __nv_save_fatbinhandle_for_managed_rt(__T4); __cudaRegisterEntry(__T4, ((void ( *)(uint32_t *, uint32_t *, uint32_t *))smem_st_latency_test_kernel), _Z27smem_st_latency_test_kernelPjS_S_, 32); __cudaRegisterEntry(__T4, ((void ( *)(uint32_t *, uint32_t *, uint32_t *))smem_ld_latency_test_kernel), _Z27smem_ld_latency_test_kernelPjS_S_, 32); }
static void __sti____cudaRegisterAll(void) {  __cudaRegisterBinary(__nv_cudaEntityRegisterCallback);  }

#pragma GCC diagnostic pop
