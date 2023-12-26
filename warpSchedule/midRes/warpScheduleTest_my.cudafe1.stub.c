#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wcast-qual"
#define __NV_CUBIN_HANDLE_STORAGE__ static
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#include "warpScheduleTest_my.fatbin.c"
extern void __device_stub__Z24warpSchedule_test_kernel6float4PjS0_Pf(const struct float4&, unsigned *, unsigned *, float *);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll(void) __attribute__((__constructor__));
void __device_stub__Z24warpSchedule_test_kernel6float4PjS0_Pf(const struct float4&__par0, unsigned *__par1, unsigned *__par2, float *__par3){__cudaLaunchPrologue(4);__cudaSetupArg(__par0, 0UL);__cudaSetupArgSimple(__par1, 16UL);__cudaSetupArgSimple(__par2, 24UL);__cudaSetupArgSimple(__par3, 32UL);__cudaLaunch(((char *)((void ( *)(const struct float4, unsigned *, unsigned *, float *))warpSchedule_test_kernel)));}
# 13 "warpScheduleTest_my.cu"
void warpSchedule_test_kernel( const struct float4 __cuda_0,unsigned *__cuda_1,unsigned *__cuda_2,float *__cuda_3)
# 14 "warpScheduleTest_my.cu"
{__device_stub__Z24warpSchedule_test_kernel6float4PjS0_Pf( __cuda_0,__cuda_1,__cuda_2,__cuda_3);
# 44 "warpScheduleTest_my.cu"
}
# 1 "midRes/warpScheduleTest_my.cudafe1.stub.c"
static void __nv_cudaEntityRegisterCallback( void **__T15) {  __nv_dummy_param_ref(__T15); __nv_save_fatbinhandle_for_managed_rt(__T15); __cudaRegisterEntry(__T15, ((void ( *)(const struct float4, unsigned *, unsigned *, float *))warpSchedule_test_kernel), _Z24warpSchedule_test_kernel6float4PjS0_Pf, (-1)); }
static void __sti____cudaRegisterAll(void) {  __cudaRegisterBinary(__nv_cudaEntityRegisterCallback);  }

#pragma GCC diagnostic pop
