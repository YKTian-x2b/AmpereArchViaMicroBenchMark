#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wcast-qual"
#define __NV_CUBIN_HANDLE_STORAGE__ static
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#include "float4Loadtest.fatbin.c"
extern void __device_stub__Z14float4LoadtestPfS_(float *, float *);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll(void) __attribute__((__constructor__));
void __device_stub__Z14float4LoadtestPfS_(float *__par0, float *__par1){__cudaLaunchPrologue(2);__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaLaunch(((char *)((void ( *)(float *, float *))float4Loadtest)));}
# 26 "float4Loadtest.cu"
void float4Loadtest( float *__cuda_0,float *__cuda_1)
# 26 "float4Loadtest.cu"
{__device_stub__Z14float4LoadtestPfS_( __cuda_0,__cuda_1);
# 35 "float4Loadtest.cu"
}
# 1 "midRes/float4Loadtest.cudafe1.stub.c"
static void __nv_cudaEntityRegisterCallback( void **__T4) {  __nv_dummy_param_ref(__T4); __nv_save_fatbinhandle_for_managed_rt(__T4); __cudaRegisterEntry(__T4, ((void ( *)(float *, float *))float4Loadtest), _Z14float4LoadtestPfS_, (-1)); }
static void __sti____cudaRegisterAll(void) {  __cudaRegisterBinary(__nv_cudaEntityRegisterCallback);  }

#pragma GCC diagnostic pop
