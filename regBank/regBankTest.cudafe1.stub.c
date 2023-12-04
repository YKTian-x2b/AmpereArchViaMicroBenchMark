#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wcast-qual"
#define __NV_CUBIN_HANDLE_STORAGE__ static
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#include "regBankTest.fatbin.c"
extern void __device_stub__Z19regbank_test_kernel4int2i6float4Pf(const struct int2&, const int, const struct float4&, float *);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll(void) __attribute__((__constructor__));
void __device_stub__Z19regbank_test_kernel4int2i6float4Pf(const struct int2&__par0, const int __par1, const struct float4&__par2, float *__par3){__cudaLaunchPrologue(4);__cudaSetupArg(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaSetupArg(__par2, 16UL);__cudaSetupArgSimple(__par3, 32UL);__cudaLaunch(((char *)((void ( *)(const struct int2, const int, const struct float4, float *))regbank_test_kernel)));}
# 20 "regBankTest.cu"
void regbank_test_kernel( const struct int2 __cuda_0,const int __cuda_1,const struct float4 __cuda_2,float *__cuda_3)
# 21 "regBankTest.cu"
{__device_stub__Z19regbank_test_kernel4int2i6float4Pf( __cuda_0,__cuda_1,__cuda_2,__cuda_3);
# 54 "regBankTest.cu"
}
# 1 "regBankTest.cudafe1.stub.c"
static void __nv_cudaEntityRegisterCallback( void **__T11) {  __nv_dummy_param_ref(__T11); __nv_save_fatbinhandle_for_managed_rt(__T11); __cudaRegisterEntry(__T11, ((void ( *)(const struct int2, const int, const struct float4, float *))regbank_test_kernel), _Z19regbank_test_kernel4int2i6float4Pf, (-1)); }
static void __sti____cudaRegisterAll(void) {  __cudaRegisterBinary(__nv_cudaEntityRegisterCallback);  }

#pragma GCC diagnostic pop
