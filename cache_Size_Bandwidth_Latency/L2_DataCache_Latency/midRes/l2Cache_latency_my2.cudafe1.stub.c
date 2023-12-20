#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wcast-qual"
#define __NV_CUBIN_HANDLE_STORAGE__ static
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#include "l2Cache_latency_my2.fatbin.c"
extern void __device_stub__Z27l2Cache_latency_test_kernelPjS_PPvS1_(uint32_t *, uint32_t *, void **, void **);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll(void) __attribute__((__constructor__));
void __device_stub__Z27l2Cache_latency_test_kernelPjS_PPvS1_(uint32_t *__par0, uint32_t *__par1, void **__par2, void **__par3){__cudaLaunchPrologue(4);__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaSetupArgSimple(__par2, 16UL);__cudaSetupArgSimple(__par3, 24UL);__cudaLaunch(((char *)((void ( *)(uint32_t *, uint32_t *, void **, void **))l2Cache_latency_test_kernel)));}
# 15 "l2Cache_latency_my2.cu"
void l2Cache_latency_test_kernel( uint32_t *__cuda_0,uint32_t *__cuda_1,void **__cuda_2,void **__cuda_3)
# 15 "l2Cache_latency_my2.cu"
{__device_stub__Z27l2Cache_latency_test_kernelPjS_PPvS1_( __cuda_0,__cuda_1,__cuda_2,__cuda_3);
# 48 "l2Cache_latency_my2.cu"
}
# 1 "midRes/l2Cache_latency_my2.cudafe1.stub.c"
static void __nv_cudaEntityRegisterCallback( void **__T6) {  __nv_dummy_param_ref(__T6); __nv_save_fatbinhandle_for_managed_rt(__T6); __cudaRegisterEntry(__T6, ((void ( *)(uint32_t *, uint32_t *, void **, void **))l2Cache_latency_test_kernel), _Z27l2Cache_latency_test_kernelPjS_PPvS1_, (-1)); }
static void __sti____cudaRegisterAll(void) {  __cudaRegisterBinary(__nv_cudaEntityRegisterCallback);  }

#pragma GCC diagnostic pop
