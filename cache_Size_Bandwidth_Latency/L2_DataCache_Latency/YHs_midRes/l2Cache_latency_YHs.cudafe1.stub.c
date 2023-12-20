#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wcast-qual"
#define __NV_CUBIN_HANDLE_STORAGE__ static
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#include "l2Cache_latency_YHs.fatbin.c"
static void __device_stub__Z17l2_latency_kernelILi10EEvPKjPjS2_(const uint32_t *, uint32_t *, uint32_t *);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll(void) __attribute__((__constructor__));
static void __device_stub__Z17l2_latency_kernelILi10EEvPKjPjS2_(const uint32_t *__par0, uint32_t *__par1, uint32_t *__par2){__cudaLaunchPrologue(3);__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaSetupArgSimple(__par2, 16UL);__cudaLaunch(((char *)((void ( *)(const uint32_t *, uint32_t *, uint32_t *))l2_latency_kernel<(int)10> )));}
template<> __specialization_static void __wrapper__device_stub_l2_latency_kernel<10>( const ::uint32_t *&__cuda_0,::uint32_t *&__cuda_1,::uint32_t *&__cuda_2){__device_stub__Z17l2_latency_kernelILi10EEvPKjPjS2_( (const ::uint32_t *&)__cuda_0,(::uint32_t *&)__cuda_1,(::uint32_t *&)__cuda_2);}
static void __nv_cudaEntityRegisterCallback(void **__T4){__nv_dummy_param_ref(__T4);__nv_save_fatbinhandle_for_managed_rt(__T4);__cudaRegisterEntry(__T4, ((void ( *)(const uint32_t *, uint32_t *, uint32_t *))l2_latency_kernel<(int)10> ), _Z17l2_latency_kernelILi10EEvPKjPjS2_, 32);}
static void __sti____cudaRegisterAll(void){__cudaRegisterBinary(__nv_cudaEntityRegisterCallback);}

#pragma GCC diagnostic pop
