#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wcast-qual"
#define __NV_CUBIN_HANDLE_STORAGE__ static
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#include "smem_bandwidth_float.fatbin.c"
extern void __device_stub__Z24SMem_writeBW_test_kernelPjS_Pf(uint32_t *, uint32_t *, float *);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll(void) __attribute__((__constructor__));
void __device_stub__Z24SMem_writeBW_test_kernelPjS_Pf(uint32_t *__par0, uint32_t *__par1, float *__par2){__cudaLaunchPrologue(3);__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaSetupArgSimple(__par2, 16UL);__cudaLaunch(((char *)((void ( *)(uint32_t *, uint32_t *, float *))SMem_writeBW_test_kernel)));}
# 19 "smem_bandwidth_float.cu"
void SMem_writeBW_test_kernel( uint32_t *__cuda_0,uint32_t *__cuda_1,float *__cuda_2)
# 19 "smem_bandwidth_float.cu"
{__device_stub__Z24SMem_writeBW_test_kernelPjS_Pf( __cuda_0,__cuda_1,__cuda_2);
# 42 "smem_bandwidth_float.cu"
}
# 1 "bw_midRes_float/smem_bandwidth_float.cudafe1.stub.c"
static void __nv_cudaEntityRegisterCallback( void **__T6) {  __nv_dummy_param_ref(__T6); __nv_save_fatbinhandle_for_managed_rt(__T6); __cudaRegisterEntry(__T6, ((void ( *)(uint32_t *, uint32_t *, float *))SMem_writeBW_test_kernel), _Z24SMem_writeBW_test_kernelPjS_Pf, (-1)); }
static void __sti____cudaRegisterAll(void) {  __cudaRegisterBinary(__nv_cudaEntityRegisterCallback);  }

#pragma GCC diagnostic pop
