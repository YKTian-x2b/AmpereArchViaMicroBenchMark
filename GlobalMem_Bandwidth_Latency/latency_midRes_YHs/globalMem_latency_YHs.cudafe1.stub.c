#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wcast-qual"
#define __NV_CUBIN_HANDLE_STORAGE__ static
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#include "globalMem_latency_YHs.fatbin.c"
static void __device_stub__Z15flush_l2_kernelILi128EEvPKiPi(const int *, int *);
static void __device_stub__Z19dram_latency_kernelILi10EEvPKjPjS2_(const uint32_t *, uint32_t *, uint32_t *);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll(void) __attribute__((__constructor__));
static void __device_stub__Z15flush_l2_kernelILi128EEvPKiPi(const int *__par0, int *__par1){__cudaLaunchPrologue(2);__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaLaunch(((char *)((void ( *)(const int *, int *))flush_l2_kernel<(int)128> )));}
template<> __specialization_static void __wrapper__device_stub_flush_l2_kernel<128>( const int *&__cuda_0,int *&__cuda_1){__device_stub__Z15flush_l2_kernelILi128EEvPKiPi( (const int *&)__cuda_0,(int *&)__cuda_1);}
static void __device_stub__Z19dram_latency_kernelILi10EEvPKjPjS2_(const uint32_t *__par0, uint32_t *__par1, uint32_t *__par2){__cudaLaunchPrologue(3);__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaSetupArgSimple(__par2, 16UL);__cudaLaunch(((char *)((void ( *)(const uint32_t *, uint32_t *, uint32_t *))dram_latency_kernel<(int)10> )));}
template<> __specialization_static void __wrapper__device_stub_dram_latency_kernel<10>( const ::uint32_t *&__cuda_0,::uint32_t *&__cuda_1,::uint32_t *&__cuda_2){__device_stub__Z19dram_latency_kernelILi10EEvPKjPjS2_( (const ::uint32_t *&)__cuda_0,(::uint32_t *&)__cuda_1,(::uint32_t *&)__cuda_2);}
static void __nv_cudaEntityRegisterCallback(void **__T9){__nv_dummy_param_ref(__T9);__nv_save_fatbinhandle_for_managed_rt(__T9);__cudaRegisterEntry(__T9, ((void ( *)(const uint32_t *, uint32_t *, uint32_t *))dram_latency_kernel<(int)10> ), _Z19dram_latency_kernelILi10EEvPKjPjS2_, 32);__cudaRegisterEntry(__T9, ((void ( *)(const int *, int *))flush_l2_kernel<(int)128> ), _Z15flush_l2_kernelILi128EEvPKiPi, (-1));}
static void __sti____cudaRegisterAll(void){__cudaRegisterBinary(__nv_cudaEntityRegisterCallback);}

#pragma GCC diagnostic pop
