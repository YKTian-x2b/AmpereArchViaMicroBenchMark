#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wcast-qual"
#define __NV_CUBIN_HANDLE_STORAGE__ static
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#include "globalMem_latency.fatbin.c"
static void __device_stub__Z15flush_l2_kernelILi128EEvPKiPi(const int *, int *);
extern void __device_stub__Z26gloMem_latency_test_kernelPjS_PPvS1_(uint32_t *, uint32_t *, void **, void **);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll(void) __attribute__((__constructor__));
static void __device_stub__Z15flush_l2_kernelILi128EEvPKiPi(const int *__par0, int *__par1){__cudaLaunchPrologue(2);__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaLaunch(((char *)((void ( *)(const int *, int *))flush_l2_kernel<(int)128> )));}
template<> __specialization_static void __wrapper__device_stub_flush_l2_kernel<128>( const int *&__cuda_0,int *&__cuda_1){__device_stub__Z15flush_l2_kernelILi128EEvPKiPi( (const int *&)__cuda_0,(int *&)__cuda_1);}
void __device_stub__Z26gloMem_latency_test_kernelPjS_PPvS1_(uint32_t *__par0, uint32_t *__par1, void **__par2, void **__par3){__cudaLaunchPrologue(4);__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaSetupArgSimple(__par2, 16UL);__cudaSetupArgSimple(__par3, 24UL);__cudaLaunch(((char *)((void ( *)(uint32_t *, uint32_t *, void **, void **))gloMem_latency_test_kernel)));}
# 38 "globalMem_latency.cu"
void gloMem_latency_test_kernel( uint32_t *__cuda_0,uint32_t *__cuda_1,void **__cuda_2,void **__cuda_3)
# 38 "globalMem_latency.cu"
{__device_stub__Z26gloMem_latency_test_kernelPjS_PPvS1_( __cuda_0,__cuda_1,__cuda_2,__cuda_3);
# 61 "globalMem_latency.cu"
}
# 1 "latency_midRes/globalMem_latency.cudafe1.stub.c"
static void __nv_cudaEntityRegisterCallback( void **__T11) {  __nv_dummy_param_ref(__T11); __nv_save_fatbinhandle_for_managed_rt(__T11); __cudaRegisterEntry(__T11, ((void ( *)(uint32_t *, uint32_t *, void **, void **))gloMem_latency_test_kernel), _Z26gloMem_latency_test_kernelPjS_PPvS1_, (-1)); __cudaRegisterEntry(__T11, ((void ( *)(const int *, int *))flush_l2_kernel<(int)128> ), _Z15flush_l2_kernelILi128EEvPKiPi, (-1)); }
static void __sti____cudaRegisterAll(void) {  __cudaRegisterBinary(__nv_cudaEntityRegisterCallback);  }

#pragma GCC diagnostic pop
