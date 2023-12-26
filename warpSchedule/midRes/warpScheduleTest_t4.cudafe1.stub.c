#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wcast-qual"
#define __NV_CUBIN_HANDLE_STORAGE__ static
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#include "warpScheduleTest_t4.fatbin.c"
extern void __device_stub__Z23L0CacheSize_test_kernel6float4PjS0_Pfii(const struct float4&, unsigned *, unsigned *, float *, int, int);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll(void) __attribute__((__constructor__));
void __device_stub__Z23L0CacheSize_test_kernel6float4PjS0_Pfii(const struct float4&__par0, unsigned *__par1, unsigned *__par2, float *__par3, int __par4, int __par5){__cudaLaunchPrologue(6);__cudaSetupArg(__par0, 0UL);__cudaSetupArgSimple(__par1, 16UL);__cudaSetupArgSimple(__par2, 24UL);__cudaSetupArgSimple(__par3, 32UL);__cudaSetupArgSimple(__par4, 40UL);__cudaSetupArgSimple(__par5, 44UL);__cudaLaunch(((char *)((void ( *)(const struct float4, unsigned *, unsigned *, float *, int, int))L0CacheSize_test_kernel)));}
# 14 "warpScheduleTest_t4.cu"
void L0CacheSize_test_kernel( const struct float4 __cuda_0,unsigned *__cuda_1,unsigned *__cuda_2,float *__cuda_3,int __cuda_4,int __cuda_5)
# 15 "warpScheduleTest_t4.cu"
{__device_stub__Z23L0CacheSize_test_kernel6float4PjS0_Pfii( __cuda_0,__cuda_1,__cuda_2,__cuda_3,__cuda_4,__cuda_5);
# 57 "warpScheduleTest_t4.cu"
}
# 1 "midRes/warpScheduleTest_t4.cudafe1.stub.c"
static void __nv_cudaEntityRegisterCallback( void **__T15) {  __nv_dummy_param_ref(__T15); __nv_save_fatbinhandle_for_managed_rt(__T15); __cudaRegisterEntry(__T15, ((void ( *)(const struct float4, unsigned *, unsigned *, float *, int, int))L0CacheSize_test_kernel), _Z23L0CacheSize_test_kernel6float4PjS0_Pfii, (-1)); }
static void __sti____cudaRegisterAll(void) {  __cudaRegisterBinary(__nv_cudaEntityRegisterCallback);  }

#pragma GCC diagnostic pop
