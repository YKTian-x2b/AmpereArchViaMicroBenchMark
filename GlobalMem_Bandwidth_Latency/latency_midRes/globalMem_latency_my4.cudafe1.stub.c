#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wcast-qual"
#define __NV_CUBIN_HANDLE_STORAGE__ static
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#include "globalMem_latency_my4.fatbin.c"
static void __device_stub__Z15flush_l2_kernelILi128EEvPKiPi(const int *, int *);
extern void __device_stub__Z26gloMem_latency_test_kernelPjS_S_(uint32_t *, uint32_t *, uint32_t *);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll(void) __attribute__((__constructor__));
static void __device_stub__Z15flush_l2_kernelILi128EEvPKiPi(const int *__par0, int *__par1){__cudaLaunchPrologue(2);__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaLaunch(((char *)((void ( *)(const int *, int *))flush_l2_kernel<(int)128> )));}
template<> __specialization_static void __wrapper__device_stub_flush_l2_kernel<128>( const int *&__cuda_0,int *&__cuda_1){__device_stub__Z15flush_l2_kernelILi128EEvPKiPi( (const int *&)__cuda_0,(int *&)__cuda_1);}
void __device_stub__Z26gloMem_latency_test_kernelPjS_S_(uint32_t *__par0, uint32_t *__par1, uint32_t *__par2){__cudaLaunchPrologue(3);__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaSetupArgSimple(__par2, 16UL);__cudaLaunch(((char *)((void ( *)(uint32_t *, uint32_t *, uint32_t *))gloMem_latency_test_kernel)));}
# 101 "globalMem_latency_my4.cu"
void gloMem_latency_test_kernel( uint32_t *__cuda_0,uint32_t *__cuda_1,uint32_t *__cuda_2)
# 101 "globalMem_latency_my4.cu"
{__device_stub__Z26gloMem_latency_test_kernelPjS_S_( __cuda_0,__cuda_1,__cuda_2);
# 127 "globalMem_latency_my4.cu"
}
# 1 "latency_midRes/globalMem_latency_my4.cudafe1.stub.c"
static void __nv_cudaEntityRegisterCallback( void **__T9) {  __nv_dummy_param_ref(__T9); __nv_save_fatbinhandle_for_managed_rt(__T9); __cudaRegisterEntry(__T9, ((void ( *)(uint32_t *, uint32_t *, uint32_t *))gloMem_latency_test_kernel), _Z26gloMem_latency_test_kernelPjS_S_, (-1)); __cudaRegisterEntry(__T9, ((void ( *)(const int *, int *))flush_l2_kernel<(int)128> ), _Z15flush_l2_kernelILi128EEvPKiPi, (-1)); }
static void __sti____cudaRegisterAll(void) {  __cudaRegisterBinary(__nv_cudaEntityRegisterCallback);  }

#pragma GCC diagnostic pop
