#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wcast-qual"
#define __NV_CUBIN_HANDLE_STORAGE__ static
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#include "L1cacheBW_float.fatbin.c"
extern void __device_stub__Z25L1DatacacheBW_test_kernelPjS_PfS0_(uint32_t *, uint32_t *, float *, float *);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll(void) __attribute__((__constructor__));
void __device_stub__Z25L1DatacacheBW_test_kernelPjS_PfS0_(uint32_t *__par0, uint32_t *__par1, float *__par2, float *__par3){__cudaLaunchPrologue(4);__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaSetupArgSimple(__par2, 16UL);__cudaSetupArgSimple(__par3, 24UL);__cudaLaunch(((char *)((void ( *)(uint32_t *, uint32_t *, float *, float *))L1DatacacheBW_test_kernel)));}
# 35 "L1cacheBW_float.cu"
void L1DatacacheBW_test_kernel( uint32_t *__cuda_0,uint32_t *__cuda_1,float *__cuda_2,float *__cuda_3)
# 35 "L1cacheBW_float.cu"
{__device_stub__Z25L1DatacacheBW_test_kernelPjS_PfS0_( __cuda_0,__cuda_1,__cuda_2,__cuda_3);
# 60 "L1cacheBW_float.cu"
}
# 1 "midRes/L1cacheBW_float.cudafe1.stub.c"
static void __nv_cudaEntityRegisterCallback( void **__T6) {  __nv_dummy_param_ref(__T6); __nv_save_fatbinhandle_for_managed_rt(__T6); __cudaRegisterEntry(__T6, ((void ( *)(uint32_t *, uint32_t *, float *, float *))L1DatacacheBW_test_kernel), _Z25L1DatacacheBW_test_kernelPjS_PfS0_, (-1)); }
static void __sti____cudaRegisterAll(void) {  __cudaRegisterBinary(__nv_cudaEntityRegisterCallback);  }

#pragma GCC diagnostic pop
