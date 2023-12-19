#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wcast-qual"
#define __NV_CUBIN_HANDLE_STORAGE__ static
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#include "l1Cache_latency_YHs.fatbin.c"
static void __device_stub__Z17l1_latency_kernelILi50EEvPPvS1_Pj(void **, void **, uint32_t *);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll(void) __attribute__((__constructor__));
static void __device_stub__Z17l1_latency_kernelILi50EEvPPvS1_Pj(void **__par0, void **__par1, uint32_t *__par2){__cudaLaunchPrologue(3);__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaSetupArgSimple(__par2, 16UL);__cudaLaunch(((char *)((void ( *)(void **, void **, uint32_t *))l1_latency_kernel<(int)50> )));}
template<> __specialization_static void __wrapper__device_stub_l1_latency_kernel<50>( void **&__cuda_0,void **&__cuda_1,::uint32_t *&__cuda_2){__device_stub__Z17l1_latency_kernelILi50EEvPPvS1_Pj( (void **&)__cuda_0,(void **&)__cuda_1,(::uint32_t *&)__cuda_2);}
static void __nv_cudaEntityRegisterCallback(void **__T6){__nv_dummy_param_ref(__T6);__nv_save_fatbinhandle_for_managed_rt(__T6);__cudaRegisterEntry(__T6, ((void ( *)(void **, void **, uint32_t *))l1_latency_kernel<(int)50> ), _Z17l1_latency_kernelILi50EEvPPvS1_Pj, 4);}
static void __sti____cudaRegisterAll(void){__cudaRegisterBinary(__nv_cudaEntityRegisterCallback);}

#pragma GCC diagnostic pop
