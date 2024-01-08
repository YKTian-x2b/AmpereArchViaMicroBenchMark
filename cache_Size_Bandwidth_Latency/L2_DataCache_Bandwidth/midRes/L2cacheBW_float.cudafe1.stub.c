#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wcast-qual"
#define __NV_CUBIN_HANDLE_STORAGE__ static
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#include "L2cacheBW_float.fatbin.c"
extern void __device_stub__Z22L2cacheBW_float_kernelPKfPf(const float *, float *);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll(void) __attribute__((__constructor__));
void __device_stub__Z22L2cacheBW_float_kernelPKfPf(const float *__par0, float *__par1){__cudaLaunchPrologue(2);__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaLaunch(((char *)((void ( *)(const float *, float *))L2cacheBW_float_kernel)));}
# 32 "L2cacheBW_float.cu"
void L2cacheBW_float_kernel( const float *__cuda_0,float *__cuda_1)
# 32 "L2cacheBW_float.cu"
{__device_stub__Z22L2cacheBW_float_kernelPKfPf( __cuda_0,__cuda_1);
# 45 "L2cacheBW_float.cu"
}
# 1 "midRes/L2cacheBW_float.cudafe1.stub.c"
static void __nv_cudaEntityRegisterCallback( void **__T6) {  __nv_dummy_param_ref(__T6); __nv_save_fatbinhandle_for_managed_rt(__T6); __cudaRegisterEntry(__T6, ((void ( *)(const float *, float *))L2cacheBW_float_kernel), _Z22L2cacheBW_float_kernelPKfPf, (-1)); }
static void __sti____cudaRegisterAll(void) {  __cudaRegisterBinary(__nv_cudaEntityRegisterCallback);  }

#pragma GCC diagnostic pop
