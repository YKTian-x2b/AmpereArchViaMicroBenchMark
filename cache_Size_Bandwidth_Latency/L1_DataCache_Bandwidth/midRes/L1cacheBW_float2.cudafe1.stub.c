#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wcast-qual"
#define __NV_CUBIN_HANDLE_STORAGE__ static
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#include "L1cacheBW_float2.fatbin.c"
extern void __device_stub__Z25L1DatacacheBW_test_kernelPjS_P6float2S1_(uint32_t *, uint32_t *, struct float2 *, struct float2 *);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll(void) __attribute__((__constructor__));
void __device_stub__Z25L1DatacacheBW_test_kernelPjS_P6float2S1_(uint32_t *__par0, uint32_t *__par1, struct float2 *__par2, struct float2 *__par3){__cudaLaunchPrologue(4);__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaSetupArgSimple(__par2, 16UL);__cudaSetupArgSimple(__par3, 24UL);__cudaLaunch(((char *)((void ( *)(uint32_t *, uint32_t *, struct float2 *, struct float2 *))L1DatacacheBW_test_kernel)));}
# 35 "L1cacheBW_float2.cu"
void L1DatacacheBW_test_kernel( uint32_t *__cuda_0,uint32_t *__cuda_1,struct float2 *__cuda_2,struct float2 *__cuda_3)
# 35 "L1cacheBW_float2.cu"
{__device_stub__Z25L1DatacacheBW_test_kernelPjS_P6float2S1_( __cuda_0,__cuda_1,__cuda_2,__cuda_3);
# 62 "L1cacheBW_float2.cu"
}
# 1 "midRes/L1cacheBW_float2.cudafe1.stub.c"
static void __nv_cudaEntityRegisterCallback( void **__T8) {  __nv_dummy_param_ref(__T8); __nv_save_fatbinhandle_for_managed_rt(__T8); __cudaRegisterEntry(__T8, ((void ( *)(uint32_t *, uint32_t *, struct float2 *, struct float2 *))L1DatacacheBW_test_kernel), _Z25L1DatacacheBW_test_kernelPjS_P6float2S1_, (-1)); }
static void __sti____cudaRegisterAll(void) {  __cudaRegisterBinary(__nv_cudaEntityRegisterCallback);  }

#pragma GCC diagnostic pop
