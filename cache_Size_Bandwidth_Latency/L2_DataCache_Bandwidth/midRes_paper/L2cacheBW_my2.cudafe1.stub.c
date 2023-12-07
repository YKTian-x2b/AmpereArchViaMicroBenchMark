#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wcast-qual"
#define __NV_CUBIN_HANDLE_STORAGE__ static
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#include "L2cacheBW_my2.fatbin.c"
extern void __device_stub__Z5l2_bwPfS_(float *, float *);
extern void __device_stub__Z6l2_bw2PfS_(float *, float *);
extern void __device_stub__Z6l2_bw3PfS_(float *, float *);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll(void) __attribute__((__constructor__));
void __device_stub__Z5l2_bwPfS_(float *__par0, float *__par1){__cudaLaunchPrologue(2);__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaLaunch(((char *)((void ( *)(float *, float *))l2_bw)));}
# 25 "L2cacheBW_my2.cu"
void l2_bw( float *__cuda_0,float *__cuda_1)
# 25 "L2cacheBW_my2.cu"
{__device_stub__Z5l2_bwPfS_( __cuda_0,__cuda_1);
# 47 "L2cacheBW_my2.cu"
}
# 1 "midRes_paper/L2cacheBW_my2.cudafe1.stub.c"
void __device_stub__Z6l2_bw2PfS_( float *__par0,  float *__par1) {  __cudaLaunchPrologue(2); __cudaSetupArgSimple(__par0, 0UL); __cudaSetupArgSimple(__par1, 8UL); __cudaLaunch(((char *)((void ( *)(float *, float *))l2_bw2))); }
# 49 "L2cacheBW_my2.cu"
void l2_bw2( float *__cuda_0,float *__cuda_1)
# 49 "L2cacheBW_my2.cu"
{__device_stub__Z6l2_bw2PfS_( __cuda_0,__cuda_1);
# 84 "L2cacheBW_my2.cu"
}
# 1 "midRes_paper/L2cacheBW_my2.cudafe1.stub.c"
void __device_stub__Z6l2_bw3PfS_( float *__par0,  float *__par1) {  __cudaLaunchPrologue(2); __cudaSetupArgSimple(__par0, 0UL); __cudaSetupArgSimple(__par1, 8UL); __cudaLaunch(((char *)((void ( *)(float *, float *))l2_bw3))); }
# 87 "L2cacheBW_my2.cu"
void l2_bw3( float *__cuda_0,float *__cuda_1)
# 87 "L2cacheBW_my2.cu"
{__device_stub__Z6l2_bw3PfS_( __cuda_0,__cuda_1);
# 109 "L2cacheBW_my2.cu"
}
# 1 "midRes_paper/L2cacheBW_my2.cudafe1.stub.c"
static void __nv_cudaEntityRegisterCallback( void **__T6) {  __nv_dummy_param_ref(__T6); __nv_save_fatbinhandle_for_managed_rt(__T6); __cudaRegisterEntry(__T6, ((void ( *)(float *, float *))l2_bw3), _Z6l2_bw3PfS_, (-1)); __cudaRegisterEntry(__T6, ((void ( *)(float *, float *))l2_bw2), _Z6l2_bw2PfS_, (-1)); __cudaRegisterEntry(__T6, ((void ( *)(float *, float *))l2_bw), _Z5l2_bwPfS_, (-1)); }
static void __sti____cudaRegisterAll(void) {  __cudaRegisterBinary(__nv_cudaEntityRegisterCallback);  }

#pragma GCC diagnostic pop
