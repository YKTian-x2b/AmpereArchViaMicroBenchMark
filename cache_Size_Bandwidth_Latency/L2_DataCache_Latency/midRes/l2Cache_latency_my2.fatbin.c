#ifndef __SKIP_INTERNAL_FATBINARY_HEADERS
#include "fatbinary_section.h"
#endif
#define __CUDAFATBINSECTION  ".nvFatBinSegment"
#define __CUDAFATBINDATASECTION  ".nv_fatbin"
asm(
".section .nv_fatbin, \"a\"\n"
".align 8\n"
"fatbinData:\n"
".quad 0x00100001ba55ed50,0x0000000000001178,0x0000004001010002,0x0000000000000ea8\n"
".quad 0x0000000000000000,0x0000005600010007,0x0000000000000000,0x0000000000000011\n"
".quad 0x0000000000000000,0x0000000000000000,0x33010102464c457f,0x0000000000000007\n"
".quad 0x0000007900be0002,0x0000000000000000,0x0000000000000e00,0x0000000000000b80\n"
".quad 0x0038004000560556,0x0001000a00400003,0x7472747368732e00,0x747274732e006261\n"
".quad 0x746d79732e006261,0x746d79732e006261,0x78646e68735f6261,0x7466752e766e2e00\n"
".quad 0x2e007972746e652e,0x006f666e692e766e,0x5a5f2e747865742e,0x68636143326c3732\n"
".quad 0x636e6574616c5f65,0x6b5f747365745f79,0x536a506c656e7265,0x005f31537650505f\n"
".quad 0x6f666e692e766e2e,0x43326c37325a5f2e,0x74616c5f65686361,0x7365745f79636e65\n"
".quad 0x6c656e72656b5f74,0x537650505f536a50,0x732e766e2e005f31,0x5a5f2e6465726168\n"
".quad 0x68636143326c3732,0x636e6574616c5f65,0x6b5f747365745f79,0x536a506c656e7265\n"
".quad 0x005f31537650505f,0x736e6f632e766e2e,0x5a5f2e30746e6174,0x68636143326c3732\n"
".quad 0x636e6574616c5f65,0x6b5f747365745f79,0x536a506c656e7265,0x005f31537650505f\n"
".quad 0x665f67756265642e,0x65722e00656d6172,0x5f67756265642e6c,0x722e00656d617266\n"
".quad 0x756265642e616c65,0x00656d6172665f67,0x7472747368732e00,0x747274732e006261\n"
".quad 0x746d79732e006261,0x746d79732e006261,0x78646e68735f6261,0x7466752e766e2e00\n"
".quad 0x2e007972746e652e,0x006f666e692e766e,0x6143326c37325a5f,0x6574616c5f656863\n"
".quad 0x747365745f79636e,0x506c656e72656b5f,0x31537650505f536a,0x2e747865742e005f\n"
".quad 0x6143326c37325a5f,0x6574616c5f656863,0x747365745f79636e,0x506c656e72656b5f\n"
".quad 0x31537650505f536a,0x6e692e766e2e005f,0x6c37325a5f2e6f66,0x6c5f656863614332\n"
".quad 0x745f79636e657461,0x6e72656b5f747365,0x50505f536a506c65,0x766e2e005f315376\n"
".quad 0x2e6465726168732e,0x6143326c37325a5f,0x6574616c5f656863,0x747365745f79636e\n"
".quad 0x506c656e72656b5f,0x31537650505f536a,0x6f632e766e2e005f,0x2e30746e6174736e\n"
".quad 0x6143326c37325a5f,0x6574616c5f656863,0x747365745f79636e,0x506c656e72656b5f\n"
".quad 0x31537650505f536a,0x6d617261705f005f,0x5f67756265642e00,0x722e00656d617266\n"
".quad 0x67756265642e6c65,0x2e00656d6172665f,0x6265642e616c6572,0x656d6172665f6775\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x000900030000006a,0x0000000000000000,0x0000000000000000,0x0008000300000102\n"
".quad 0x0000000000000000,0x0000000000000000,0x0004000300000141,0x0000000000000000\n"
".quad 0x0000000000000000,0x0009101200000040,0x0000000000000000,0x0000000000000500\n"
".quad 0x00000024ffffffff,0xffffffff00000000,0x7c040003ffffffff,0x80810c0fffffffff\n"
".quad 0x288081ff08002880,0x0000002880808108,0x00000034ffffffff,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000050000000000,0x0000040400000000,0x810c000000180400\n"
".quad 0x0000fc0400288080,0x0000000000000000,0x0000000400082f04,0x0008230400000014\n"
".quad 0x0000000000000004,0x0000000400081204,0x0008110400000000,0x0000000000000004\n"
".quad 0x0000007900043704,0x00080a0400003501,0x0020016000000002,0x000c170400201903\n"
".quad 0x0018000300000000,0x000c17040021f000,0x0010000200000000,0x000c17040021f000\n"
".quad 0x0008000100000000,0x000c17040021f000,0x0000000000000000,0x00ff1b030021f000\n"
".quad 0x0000042000081c04,0x0000000000000460,0x0000000000000044,0x0000000400000002\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x00000a00ff017624,0x000fc400078e00ff\n"
".quad 0x0000000000007919,0x000e220000002100,0x0000000800037802,0x000fe20000000f00\n"
".quad 0x0000460000047ab9,0x000fc80000000a00,0x00005e0000027625,0x001fca00078e0203\n"
".quad 0x0000000402047981,0x000168000c1efb00,0x0000000000007b1d,0x000fec0000000000\n"
".quad 0x0000000000027805,0x001fc40000005000,0x0000000404047981,0x020ea8000c1efb00\n"
".quad 0x0000000404067981,0x004ea8000c1efb00,0x0000000406067981,0x004ea8000c1efb00\n"
".quad 0x0000000406087981,0x004ea8000c1efb00,0x0000000408087981,0x004ea8000c1efb00\n"
".quad 0x00000004080a7981,0x004ea8000c1efb00,0x000000040a0a7981,0x004ea8000c1efb00\n"
".quad 0x000000040a0c7981,0x004ea8000c1efb00,0x000000040c0c7981,0x004ea8000c1efb00\n"
".quad 0x000000040c0e7981,0x004ea8000c1efb00,0x000000040e0e7981,0x004ea8000c1efb00\n"
".quad 0x000000040e107981,0x004ea8000c1efb00,0x0000000410107981,0x004ea8000c1efb00\n"
".quad 0x0000000410047981,0x004ea8000c1efb00,0x0000000404047981,0x004ea8000c1efb00\n"
".quad 0x0000000404067981,0x004ea8000c1efb00,0x0000000406067981,0x004ea8000c1efb00\n"
".quad 0x0000000406087981,0x004ea8000c1efb00,0x0000000408087981,0x004ea8000c1efb00\n"
".quad 0x00000004080a7981,0x004ea8000c1efb00,0x000000040a0a7981,0x004ea8000c1efb00\n"
".quad 0x000000040a0c7981,0x004ea8000c1efb00,0x000000040c0c7981,0x004ea8000c1efb00\n"
".quad 0x000000040c0e7981,0x004ea8000c1efb00,0x000000040e0e7981,0x004ea8000c1efb00\n"
".quad 0x000000040e107981,0x004ea8000c1efb00,0x0000000410107981,0x004ea8000c1efb00\n"
".quad 0x0000000410047981,0x004ea8000c1efb00,0x0000000404047981,0x004ea8000c1efb00\n"
".quad 0x0000000404067981,0x004ea8000c1efb00,0x0000000406067981,0x004ea8000c1efb00\n"
".quad 0x0000000406087981,0x004ea8000c1efb00,0x0000000408087981,0x004ea8000c1efb00\n"
".quad 0x00000004080a7981,0x004ea8000c1efb00,0x000000040a0a7981,0x004ea8000c1efb00\n"
".quad 0x000000040a0c7981,0x004ea8000c1efb00,0x000000040c0c7981,0x004ea8000c1efb00\n"
".quad 0x000000040c0e7981,0x004ea8000c1efb00,0x000000040e0e7981,0x004ea8000c1efb00\n"
".quad 0x000000040e107981,0x004ea8000c1efb00,0x0000000410107981,0x004ea8000c1efb00\n"
".quad 0x0000000410047981,0x004ea8000c1efb00,0x0000000404047981,0x004ea8000c1efb00\n"
".quad 0x0000000404067981,0x004ea8000c1efb00,0x0000000406067981,0x004ea8000c1efb00\n"
".quad 0x0000000406087981,0x004ea8000c1efb00,0x0000000408087981,0x004ea8000c1efb00\n"
".quad 0x00000004080a7981,0x004ea8000c1efb00,0x000000040a0a7981,0x004ea8000c1efb00\n"
".quad 0x000000040a0c7981,0x004164000c1efb00,0x0000000000037805,0x000fc40000005000\n"
".quad 0x000000ff0c00720c,0x020fe20003f05070,0x00000004ff077424,0x000fc600078e00ff\n"
".quad 0x000000ff0d00720c,0x000fe20003f05300,0x0000580000047625,0x000fc800078e0207\n"
".quad 0x00005a0000067625,0x000fe200078e0207,0x0000000204007986,0x0003e8000c101904\n"
".quad 0x0000000306007986,0x0003e6000c101904,0x000000000000094d,0x000fea0003800000\n"
".quad 0x00005c0000027a02,0x002fe20000000f00,0x00005d00ff037624,0x000fca00078e00ff\n"
".quad 0x000000ff02007986,0x000fe2000c101b04,0x000000000000794d,0x000fea0003800000\n"
".quad 0xfffffff000007947,0x000fc0000383ffff,0x0000000000007918,0x000fc00000000000\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000007918,0x000fc00000000000\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000007918,0x000fc00000000000\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000007918,0x000fc00000000000\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000300000001,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000040,0x0000000000000140,0x0000000000000000\n"
".quad 0x0000000000000001,0x0000000000000000,0x000000030000000b,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000180,0x0000000000000171,0x0000000000000000\n"
".quad 0x0000000000000001,0x0000000000000000,0x0000000200000013,0x0000000000000000\n"
".quad 0x0000000000000000,0x00000000000002f8,0x0000000000000078,0x0000000400000002\n"
".quad 0x0000000000000008,0x0000000000000018,0x0000000100000110,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000370,0x0000000000000070,0x0000000000000000\n"
".quad 0x0000000000000001,0x0000000000000000,0x7000000000000037,0x0000000000000000\n"
".quad 0x0000000000000000,0x00000000000003e0,0x0000000000000030,0x0000000000000005\n"
".quad 0x0000000000000004,0x0000000000000000,0x7000000000000070,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000410,0x000000000000006c,0x0000000900000005\n"
".quad 0x0000000000000004,0x0000000000000000,0x000000090000011d,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000480,0x0000000000000010,0x0000000400000005\n"
".quad 0x0000000000000008,0x0000000000000010,0x00000001000000d8,0x0000000000000002\n"
".quad 0x0000000000000000,0x0000000000000490,0x0000000000000180,0x0000000900000000\n"
".quad 0x0000000000000004,0x0000000000000000,0x0000000100000040,0x0000000000100006\n"
".quad 0x0000000000000000,0x0000000000000680,0x0000000000000500,0x1400000400000005\n"
".quad 0x0000000000000080,0x0000000000000000,0x0000000500000006,0x0000000000000e00\n"
".quad 0x0000000000000000,0x0000000000000000,0x00000000000000a8,0x00000000000000a8\n"
".quad 0x0000000000000008,0x0000000500000001,0x0000000000000490,0x0000000000000000\n"
".quad 0x0000000000000000,0x00000000000006f0,0x00000000000006f0,0x0000000000000008\n"
".quad 0x0000000500000001,0x0000000000000e00,0x0000000000000000,0x0000000000000000\n"
".quad 0x00000000000000a8,0x00000000000000a8,0x0000000000000008,0x0000004801010001\n"
".quad 0x0000000000000248,0x0000004000000241,0x0000005600080001,0x0000000000000000\n"
".quad 0x0000000000002011,0x0000000000000000,0x0000000000000c04,0x0000000000000000\n"
".quad 0x762e1cf200010a13,0x38206e6f69737265,0x677261742e0a312e,0x36385f6d73207465\n"
".quad 0x7365726464612e0a,0x3620657a69735f73,0x69736935ff002f34,0x746e652e20656c62\n"
".quad 0x6c37325a5f207972,0x6c5f656863614332,0x745f79636e657461,0x6e72656b5f747365\n"
".quad 0x50505f536a506c65,0x702e0a285f315376,0x36752e206d617261,0x00355f1117003734\n"
".quad 0x1f2a003f2c305f3f,0x003f321f2b003f31,0x7b0a290a3308f32b,0x702e206765722e0a\n"
".quad 0x323c702520646572,0x3233628600123b3e,0xf20011343c722520,0x3c64722520343602\n"
".quad 0x0a0a0a3b3e353131,0x19752e22007d646c,0x5b202c3430316f00,0x4a3b5d303f1d0085\n"
".quad 0x1f20004a351f0000,0x2000480f01004a31,0x4a361f020092321f,0x6d0a3b5d33912000\n"
".quad 0x08f2014b752e766f,0x2e64697425202c33,0x772e6c756d0a3b78,0x5f3233732e656469\n"
".quad 0x388200222c372200,0x77732e6464610a3b,0x2602007d2c342500,0x6c090a0a3b03f500\n"
".quad 0x6c61626f6c672e64,0x100029622e67632e,0xe101995d1000075b,0x732e726162090a09\n"
".quad 0x00103b3020636e79,0x25202c3192008606,0x0f00196b636f6c63,0xffff00240f0c004d\n"
".quad 0x072106dcffffffff,0x7476637407213218,0x0e0500406f742e61,0xcc341f0791381308\n"
".quad 0x341907cc39130107,0x3d2c3031314a07cc,0x0400600a3b393f00,0x43351b0023313123\n"
".quad 0x395500202c322a00,0x3321003e74730a3b,0x5d3031314000d532,0x1103001d311f0020\n"
".quad 0x730a3b32a2001d32,0x005e656e2e707465,0x08ff01182c317033,0x20317025400a3b30\n"
".quad 0x5f5f4c2420617262,0xac0a3b325f304242,0x0300082c33210600,0x00490200160408eb\n"
".quad 0x008002002f747328,0x3b3500232c5d3333,0x720a3ac000610a0a,0x0a0a7d0a0a3b7465\n"
".quad 0x0000000000000000\n"
".text\n");
#ifdef __cplusplus
extern "C" {
#endif
extern const unsigned long long fatbinData[561];
#ifdef __cplusplus
}
#endif
#ifdef __cplusplus
extern "C" {
#endif
static const __fatBinC_Wrapper_t __fatDeviceText __attribute__ ((aligned (8))) __attribute__ ((section (__CUDAFATBINSECTION)))= 
	{ 0x466243b1, 1, fatbinData, 0 };
#ifdef __cplusplus
}
#endif
