#ifndef __SKIP_INTERNAL_FATBINARY_HEADERS
#include "fatbinary_section.h"
#endif
#define __CUDAFATBINSECTION  ".nvFatBinSegment"
#define __CUDAFATBINDATASECTION  ".nv_fatbin"
asm(
".section .nv_fatbin, \"a\"\n"
".align 8\n"
"fatbinData:\n"
".quad 0x00100001ba55ed50,0x00000000000010f0,0x0000004001010002,0x0000000000000d28\n"
".quad 0x0000000000000000,0x0000005600010007,0x0000000000000000,0x0000000000000011\n"
".quad 0x0000000000000000,0x0000000000000000,0x33010102464c457f,0x0000000000000007\n"
".quad 0x0000007900be0002,0x0000000000000000,0x0000000000000c80,0x0000000000000a00\n"
".quad 0x0038004000560556,0x0001000a00400003,0x7472747368732e00,0x747274732e006261\n"
".quad 0x746d79732e006261,0x746d79732e006261,0x78646e68735f6261,0x7466752e766e2e00\n"
".quad 0x2e007972746e652e,0x006f666e692e766e,0x5a5f2e747865742e,0x74616c5f326c3731\n"
".quad 0x72656b5f79636e65,0x3031694c496c656e,0x6a506a4b50764545,0x2e766e2e005f3253\n"
".quad 0x315a5f2e6f666e69,0x6574616c5f326c37,0x6e72656b5f79636e,0x453031694c496c65\n"
".quad 0x536a506a4b507645,0x732e766e2e005f32,0x5a5f2e6465726168,0x74616c5f326c3731\n"
".quad 0x72656b5f79636e65,0x3031694c496c656e,0x6a506a4b50764545,0x2e766e2e005f3253\n"
".quad 0x746e6174736e6f63,0x326c37315a5f2e30,0x79636e6574616c5f,0x496c656e72656b5f\n"
".quad 0x507645453031694c,0x005f32536a506a4b,0x665f67756265642e,0x65722e00656d6172\n"
".quad 0x5f67756265642e6c,0x722e00656d617266,0x756265642e616c65,0x00656d6172665f67\n"
".quad 0x7472747368732e00,0x747274732e006261,0x746d79732e006261,0x746d79732e006261\n"
".quad 0x78646e68735f6261,0x7466752e766e2e00,0x2e007972746e652e,0x006f666e692e766e\n"
".quad 0x6c5f326c37315a5f,0x6b5f79636e657461,0x694c496c656e7265,0x6a4b507645453031\n"
".quad 0x742e005f32536a50,0x37315a5f2e747865,0x6e6574616c5f326c,0x656e72656b5f7963\n"
".quad 0x45453031694c496c,0x32536a506a4b5076,0x6e692e766e2e005f,0x6c37315a5f2e6f66\n"
".quad 0x636e6574616c5f32,0x6c656e72656b5f79,0x7645453031694c49,0x5f32536a506a4b50\n"
".quad 0x6168732e766e2e00,0x37315a5f2e646572,0x6e6574616c5f326c,0x656e72656b5f7963\n"
".quad 0x45453031694c496c,0x32536a506a4b5076,0x6f632e766e2e005f,0x2e30746e6174736e\n"
".quad 0x6c5f326c37315a5f,0x6b5f79636e657461,0x694c496c656e7265,0x6a4b507645453031\n"
".quad 0x705f005f32536a50,0x65642e006d617261,0x6d6172665f677562,0x642e6c65722e0065\n"
".quad 0x6172665f67756265,0x616c65722e00656d,0x665f67756265642e,0x00000000656d6172\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0009000300000066\n"
".quad 0x0000000000000000,0x0000000000000000,0x00080003000000f2,0x0000000000000000\n"
".quad 0x0000000000000000,0x000400030000012d,0x0000000000000000,0x0000000000000000\n"
".quad 0x0009101200000040,0x0000000000000000,0x0000000000000400,0x00000024ffffffff\n"
".quad 0xffffffff00000000,0x7c040003ffffffff,0x80810c0fffffffff,0x288081ff08002880\n"
".quad 0x0000002880808108,0x00000034ffffffff,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000040000000000,0x0000040400000000,0x810c000000200400,0x0000a00400288080\n"
".quad 0x0000000000000000,0x0000000400082f04,0x0008230400000010,0x0000000000000004\n"
".quad 0x0000000400081204,0x0008110400000000,0x0000000000000004,0x0000007900043704\n"
".quad 0x00080a0400003501,0x0018016000000002,0x000c170400181903,0x0010000200000000\n"
".quad 0x000c17040021f000,0x0008000100000000,0x000c17040021f000,0x0000000000000000\n"
".quad 0x00ff1b030021f000,0x000002d000081c04,0x000c050400000310,0x0000000100000020\n"
".quad 0x0000000000000001,0x0000000000000044,0x0000000400000002,0x0000000000000000\n"
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
".quad 0x0000000000007919,0x000e220000002100,0x00000004ff0d7424,0x000fe200078e00ff\n"
".quad 0x0000460000047ab9,0x000fc60000000a00,0x0000580000027625,0x001fca00078e000d\n"
".quad 0x0000000402057981,0x000ea8000c1ef900,0x0000000000007b1d,0x000fec0000000000\n"
".quad 0x0000000502047210,0x004fca0007f1e0ff,0x000000ffff057224,0x000fc400000e0603\n"
".quad 0x00000000000679c3,0x000e220000005000,0x000080000000791a,0x000fce0000000000\n"
".quad 0x0000000404037981,0x000ea4000c1ef900,0x0000000403027210,0x004fca0007f1e0ff\n"
".quad 0x000000ffff037224,0x000fca00000e0605,0x0000000402077981,0x000ea4000c1ef900\n"
".quad 0x0000000207067210,0x004fc80007f1e0ff,0x00000003ff077210,0x000fca00007fe4ff\n"
".quad 0x0000000406097981,0x000ea4000c1ef900,0x0000000609087210,0x004fca0007f1e0ff\n"
".quad 0x000000ffff097224,0x000fca00000e0607,0x00000004080b7981,0x000ea4000c1ef900\n"
".quad 0x000000080b0a7210,0x004fca0007f1e0ff,0x000000ffff0b7224,0x000fca00000e0609\n"
".quad 0x000000040a057981,0x000ea4000c1ef900,0x0000000a05047210,0x004fca0007f1e0ff\n"
".quad 0x000000ffff057224,0x000fca00000e060b,0x0000000404037981,0x000ea4000c1ef900\n"
".quad 0x0000000403027210,0x004fc80007f1e0ff,0x00000005ff037210,0x000fca00007fe4ff\n"
".quad 0x0000000402077981,0x000ea4000c1ef900,0x0000000207067210,0x004fca0007f1e0ff\n"
".quad 0x000000ffff077224,0x000fca00000e0603,0x0000000406097981,0x000ea4000c1ef900\n"
".quad 0x0000000609087210,0x004fca0007f1e0ff,0x000000ffff097224,0x000fca00000e0607\n"
".quad 0x00000004080b7981,0x000ea4000c1ef900,0x000000080b0a7210,0x004fca0007f1e0ff\n"
".quad 0x000000ffff0b7224,0x000fca00000e0609,0x000000040a0a7981,0x000168000c1ef900\n"
".quad 0x0000000000007b1d,0x000fec0000000000,0x0000000000057805,0x000fc40000005000\n"
".quad 0x000000ff0a00720c,0x020fe20003f05270,0x00005c0000027625,0x000fe200078e000d\n"
".quad 0x8000000605057c10,0x000fca000fffe0ff,0x0000000502007986,0x0003ec000c101904\n"
".quad 0x000000000000094d,0x000fea0003800000,0x00005a0000027a02,0x002fe20000000f00\n"
".quad 0x00005b00ff037624,0x000fca00078e00ff,0x000000ff02007986,0x000fe2000c101904\n"
".quad 0x000000000000794d,0x000fea0003800000,0xfffffff000007947,0x000fc0000383ffff\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000007918,0x000fc00000000000\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000007918,0x000fc00000000000\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000007918,0x000fc00000000000\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000007918,0x000fc00000000000\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000007918,0x000fc00000000000\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000007918,0x000fc00000000000\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000300000001,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000040,0x0000000000000130,0x0000000000000000\n"
".quad 0x0000000000000001,0x0000000000000000,0x000000030000000b,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000170,0x000000000000015d,0x0000000000000000\n"
".quad 0x0000000000000001,0x0000000000000000,0x0000000200000013,0x0000000000000000\n"
".quad 0x0000000000000000,0x00000000000002d0,0x0000000000000078,0x0000000400000002\n"
".quad 0x0000000000000008,0x0000000000000018,0x0000000100000100,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000348,0x0000000000000070,0x0000000000000000\n"
".quad 0x0000000000000001,0x0000000000000000,0x7000000000000037,0x0000000000000000\n"
".quad 0x0000000000000000,0x00000000000003b8,0x0000000000000030,0x0000000000000005\n"
".quad 0x0000000000000004,0x0000000000000000,0x700000000000006c,0x0000000000000000\n"
".quad 0x0000000000000000,0x00000000000003e8,0x000000000000006c,0x0000000900000005\n"
".quad 0x0000000000000004,0x0000000000000000,0x000000090000010d,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000458,0x0000000000000010,0x0000000400000005\n"
".quad 0x0000000000000008,0x0000000000000010,0x00000001000000cc,0x0000000000000002\n"
".quad 0x0000000000000000,0x0000000000000468,0x0000000000000178,0x0000000900000000\n"
".quad 0x0000000000000004,0x0000000000000000,0x0000000100000040,0x0000000000100006\n"
".quad 0x0000000000000000,0x0000000000000600,0x0000000000000400,0x1000000400000005\n"
".quad 0x0000000000000080,0x0000000000000000,0x0000000500000006,0x0000000000000c80\n"
".quad 0x0000000000000000,0x0000000000000000,0x00000000000000a8,0x00000000000000a8\n"
".quad 0x0000000000000008,0x0000000500000001,0x0000000000000468,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000598,0x0000000000000598,0x0000000000000008\n"
".quad 0x0000000500000001,0x0000000000000c80,0x0000000000000000,0x0000000000000000\n"
".quad 0x00000000000000a8,0x00000000000000a8,0x0000000000000008,0x0000004801010001\n"
".quad 0x0000000000000340,0x000000400000033b,0x0000005600080001,0x0000000000000000\n"
".quad 0x0000000000002011,0x0000000000000000,0x000000000000077a,0x0000000000000000\n"
".quad 0x762e1cf200010a13,0x38206e6f69737265,0x677261742e0a312e,0x36385f6d73207465\n"
".quad 0x7365726464612e0a,0x3620657a69735f73,0x69736931ff002f34,0x746e652e20656c62\n"
".quad 0x6c37315a5f207972,0x636e6574616c5f32,0x6c656e72656b5f79,0x7645453031694c49\n"
".quad 0x5f32536a506a4b50,0x6d617261702e0a28,0x1300333436752e20,0x2c305f3f00315f11\n"
".quad 0x27003b311f26003b,0x6d2e0a290a322af3,0x33206469746e7861,0x0a31202c31202c32\n"
".quad 0x6174636e6e696d2e,0x0a31206d73726570,0x2e206765722e0a7b,0x3c70252064657270\n"
".quad 0x33629600123b3e32,0x1237313c72252032,0x722520343601f200,0x0a0a3b3e39323c64\n"
".quad 0x752e22009b646c0a,0x5b202c33315f0018,0x453b5d303e1900a2,0x44311f1c00440f00\n"
".quad 0x911c0045341f0100,0x2e766f6d0a3b5d32,0x01f3003f0000f375,0x0a3b782e64697425\n"
".quad 0x656469772e6c756d,0x222c35316443001b,0x6464610a3b348200,0x022c32240073732e\n"
".quad 0x0a3b01f300250101,0x6f6c672e646c090a,0x014d67632e6c6162,0x5d10002d0000dd00\n"
".quad 0xb27476630940013f,0x003d3610005b0500,0x5d2c332700573119,0x6162a80056361000\n"
".quad 0x3020636e79732e72,0x6c635100220000b3,0x007c0f00596b636f,0x7c331f007c331202\n"
".quad 0x3319006337100300,0x008204010600007c,0x34120400d237312f,0x10030056341f0056\n"
".quad 0x352601290a003d38,0x005638312f005c2c,0x56351f0056351204,0x3519003d39100300\n"
".quad 0x2f005c2c36260056,0x5636120400563931,0x3220020056361f00,0x2600563619003d30\n"
".quad 0x5630322f005c2c37,0x371f005637120400,0x19003d3110030056,0x005c2c3826005637\n"
".quad 0x381204005631322f,0x01030056381f0056,0x3926005638190211,0x005632322f005c2c\n"
".quad 0x56391f0056391204,0x56391901eb010300,0x2f005d2c30313600,0x3031220400573332\n"
".quad 0x03005930312f0058,0x005a30312a01ee01,0x322f006104011a01,0x2f03330305005b34\n"
".quad 0x01f30103005b3131,0x011f31110335311a,0x06038d321f006204,0x0f038f03005b3213\n"
".quad 0x035d33312905035c,0x0019732e62757352,0x3272b4001f2c3524,0x742e617476630a3b\n"
".quad 0x3222048c0300686f,0x3728042f0b008d36,0x730a3b3555001d2c,0x0098323321003974\n"
".quad 0x9200662c5d373241,0x6e2e707465730a3b,0xbe2c317033007865,0x25400a3b3005f000\n"
".quad 0x2420617262203170,0xfb5f3042425f5f4c,0x021d0204008a0f01,0x0046361100dc3119\n"
".quad 0x007d381200007d0f,0x3ac0005b05047400,0x7d0a0a3b7465720a,0x0000000000000a0a\n"
".text\n");
#ifdef __cplusplus
extern "C" {
#endif
extern const unsigned long long fatbinData[544];
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
