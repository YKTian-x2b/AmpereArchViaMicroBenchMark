#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wcast-qual"
#define __NV_CUBIN_HANDLE_STORAGE__ static
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#include "L2cacheBW_float2.fatbin.c"
extern void __device_stub__Z23L2cacheBW_float2_kernelPK6float2Pf(const struct float2 *, float *);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll(void) __attribute__((__constructor__));
void __device_stub__Z23L2cacheBW_float2_kernelPK6float2Pf(const struct float2 *__par0, float *__par1){__cudaLaunchPrologue(2);__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaLaunch(((char *)((void ( *)(const struct float2 *, float *))L2cacheBW_float2_kernel)));}
# 32 "L2cacheBW_float2.cu"
void L2cacheBW_float2_kernel( const struct float2 *__cuda_0,float *__cuda_1)
# 32 "L2cacheBW_float2.cu"
{__device_stub__Z23L2cacheBW_float2_kernelPK6float2Pf( __cuda_0,__cuda_1);
# 46 "L2cacheBW_float2.cu"
}
# 1 "midRes/L2cacheBW_float2.cudafe1.stub.c"
static void __nv_cudaEntityRegisterCallback( void **__T9) {  __nv_dummy_param_ref(__T9); __nv_save_fatbinhandle_for_managed_rt(__T9); __cudaRegisterEntry(__T9, ((void ( *)(const struct float2 *, float *))L2cacheBW_float2_kernel), _Z23L2cacheBW_float2_kernelPK6float2Pf, (-1)); }
static void __sti____cudaRegisterAll(void) {  __cudaRegisterBinary(__nv_cudaEntityRegisterCallback);  }

#pragma GCC diagnostic pop
