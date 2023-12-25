#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wcast-qual"
#define __NV_CUBIN_HANDLE_STORAGE__ static
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#include "L0CacheSizeTest.fatbin.c"
extern void __device_stub__Z23L0CacheSize_test_kernel6float4iPjS0_Pf(const struct float4&, int, unsigned *, unsigned *, float *);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll(void) __attribute__((__constructor__));
void __device_stub__Z23L0CacheSize_test_kernel6float4iPjS0_Pf(const struct float4&__par0, int __par1, unsigned *__par2, unsigned *__par3, float *__par4){__cudaLaunchPrologue(5);__cudaSetupArg(__par0, 0UL);__cudaSetupArgSimple(__par1, 16UL);__cudaSetupArgSimple(__par2, 24UL);__cudaSetupArgSimple(__par3, 32UL);__cudaSetupArgSimple(__par4, 40UL);__cudaLaunch(((char *)((void ( *)(const struct float4, int, unsigned *, unsigned *, float *))L0CacheSize_test_kernel)));}
# 14 "save/L0CacheSizeTest.cu"
void L0CacheSize_test_kernel( const struct float4 __cuda_0,int __cuda_1,unsigned *__cuda_2,unsigned *__cuda_3,float *__cuda_4)
# 15 "save/L0CacheSizeTest.cu"
{__device_stub__Z23L0CacheSize_test_kernel6float4iPjS0_Pf( __cuda_0,__cuda_1,__cuda_2,__cuda_3,__cuda_4);
# 53 "save/L0CacheSizeTest.cu"
}
# 1 "L0CacheSizeTest.cudafe1.stub.c"
static void __nv_cudaEntityRegisterCallback( void **__T13) {  __nv_dummy_param_ref(__T13); __nv_save_fatbinhandle_for_managed_rt(__T13); __cudaRegisterEntry(__T13, ((void ( *)(const struct float4, int, unsigned *, unsigned *, float *))L0CacheSize_test_kernel), _Z23L0CacheSize_test_kernel6float4iPjS0_Pf, (-1)); }
static void __sti____cudaRegisterAll(void) {  __cudaRegisterBinary(__nv_cudaEntityRegisterCallback);  }

#pragma GCC diagnostic pop
