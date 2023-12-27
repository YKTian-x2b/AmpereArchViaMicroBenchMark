#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wcast-qual"
#define __NV_CUBIN_HANDLE_STORAGE__ static
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#include "smem_latency_ld.fatbin.c"
extern void __device_stub__Z27smem_ld_latency_test_kernelPjS_S_(uint32_t *, uint32_t *, uint32_t *);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll(void) __attribute__((__constructor__));
void __device_stub__Z27smem_ld_latency_test_kernelPjS_S_(uint32_t *__par0, uint32_t *__par1, uint32_t *__par2){__cudaLaunchPrologue(3);__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaSetupArgSimple(__par2, 16UL);__cudaLaunch(((char *)((void ( *)(uint32_t *, uint32_t *, uint32_t *))smem_ld_latency_test_kernel)));}
# 19 "smem_latency_ld.cu"
void smem_ld_latency_test_kernel( uint32_t *__cuda_0,uint32_t *__cuda_1,uint32_t *__cuda_2)
# 19 "smem_latency_ld.cu"
{__device_stub__Z27smem_ld_latency_test_kernelPjS_S_( __cuda_0,__cuda_1,__cuda_2);
# 52 "smem_latency_ld.cu"
}
# 1 "latency_midRes/smem_latency_ld.cudafe1.stub.c"
static void __nv_cudaEntityRegisterCallback( void **__T4) {  __nv_dummy_param_ref(__T4); __nv_save_fatbinhandle_for_managed_rt(__T4); __cudaRegisterEntry(__T4, ((void ( *)(uint32_t *, uint32_t *, uint32_t *))smem_ld_latency_test_kernel), _Z27smem_ld_latency_test_kernelPjS_S_, (-1)); }
static void __sti____cudaRegisterAll(void) {  __cudaRegisterBinary(__nv_cudaEntityRegisterCallback);  }

#pragma GCC diagnostic pop
