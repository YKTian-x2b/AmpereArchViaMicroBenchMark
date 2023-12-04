#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wcast-qual"
#define __NV_CUBIN_HANDLE_STORAGE__ static
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#include "warpScheduleTest.fatbin.c"
extern void __device_stub__Z23L0CacheSize_test_kernel6float4iPjS0_Pfii(const struct float4&, int, unsigned *, unsigned *, float *, int, int);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll(void) __attribute__((__constructor__));
void __device_stub__Z23L0CacheSize_test_kernel6float4iPjS0_Pfii(const struct float4&__par0, int __par1, unsigned *__par2, unsigned *__par3, float *__par4, int __par5, int __par6){__cudaLaunchPrologue(7);__cudaSetupArg(__par0, 0UL);__cudaSetupArgSimple(__par1, 16UL);__cudaSetupArgSimple(__par2, 24UL);__cudaSetupArgSimple(__par3, 32UL);__cudaSetupArgSimple(__par4, 40UL);__cudaSetupArgSimple(__par5, 48UL);__cudaSetupArgSimple(__par6, 52UL);__cudaLaunch(((char *)((void ( *)(const struct float4, int, unsigned *, unsigned *, float *, int, int))L0CacheSize_test_kernel)));}
# 14 "save/warpScheduleTest.cu"
void L0CacheSize_test_kernel( const struct float4 __cuda_0,int __cuda_1,unsigned *__cuda_2,unsigned *__cuda_3,float *__cuda_4,int __cuda_5,int __cuda_6)
# 15 "save/warpScheduleTest.cu"
{__device_stub__Z23L0CacheSize_test_kernel6float4iPjS0_Pfii( __cuda_0,__cuda_1,__cuda_2,__cuda_3,__cuda_4,__cuda_5,__cuda_6);
# 57 "save/warpScheduleTest.cu"
}
# 1 "warpScheduleTest.cudafe1.stub.c"
static void __nv_cudaEntityRegisterCallback( void **__T15) {  __nv_dummy_param_ref(__T15); __nv_save_fatbinhandle_for_managed_rt(__T15); __cudaRegisterEntry(__T15, ((void ( *)(const struct float4, int, unsigned *, unsigned *, float *, int, int))L0CacheSize_test_kernel), _Z23L0CacheSize_test_kernel6float4iPjS0_Pfii, (-1)); }
static void __sti____cudaRegisterAll(void) {  __cudaRegisterBinary(__nv_cudaEntityRegisterCallback);  }

#pragma GCC diagnostic pop
