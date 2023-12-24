#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wcast-qual"
#define __NV_CUBIN_HANDLE_STORAGE__ static
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#include "regBankTest_2Bank.fatbin.c"
extern void __device_stub__Z19regbank_test_kernel6float4Pf(const struct float4&, float *);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll(void) __attribute__((__constructor__));
void __device_stub__Z19regbank_test_kernel6float4Pf(const struct float4&__par0, float *__par1){__cudaLaunchPrologue(2);__cudaSetupArg(__par0, 0UL);__cudaSetupArgSimple(__par1, 16UL);__cudaLaunch(((char *)((void ( *)(const struct float4, float *))regbank_test_kernel)));}
# 18 "regBankTest_2Bank.cu"
void regbank_test_kernel( const struct float4 __cuda_0,float *__cuda_1)
# 19 "regBankTest_2Bank.cu"
{__device_stub__Z19regbank_test_kernel6float4Pf( __cuda_0,__cuda_1);
# 33 "regBankTest_2Bank.cu"
}
# 1 "midRes/regBankTest_2Bank.cudafe1.stub.c"
static void __nv_cudaEntityRegisterCallback( void **__T10) {  __nv_dummy_param_ref(__T10); __nv_save_fatbinhandle_for_managed_rt(__T10); __cudaRegisterEntry(__T10, ((void ( *)(const struct float4, float *))regbank_test_kernel), _Z19regbank_test_kernel6float4Pf, (-1)); }
static void __sti____cudaRegisterAll(void) {  __cudaRegisterBinary(__nv_cudaEntityRegisterCallback);  }

#pragma GCC diagnostic pop
