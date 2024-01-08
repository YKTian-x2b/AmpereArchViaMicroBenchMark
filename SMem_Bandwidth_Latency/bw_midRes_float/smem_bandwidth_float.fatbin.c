#ifndef __SKIP_INTERNAL_FATBINARY_HEADERS
#include "fatbinary_section.h"
#endif
#define __CUDAFATBINSECTION  ".nvFatBinSegment"
#define __CUDAFATBINDATASECTION  ".nv_fatbin"
asm(
".section .nv_fatbin, \"a\"\n"
".align 8\n"
"fatbinData:\n"
".quad 0x00100001ba55ed50,0x0000000000001440,0x0000004001010002,0x0000000000000fa0\n"
".quad 0x0000000000000000,0x0000005600010007,0x0000000000000000,0x0000000000000011\n"
".quad 0x0000000000000000,0x0000000000000000,0x33010102464c457f,0x0000000000000007\n"
".quad 0x0000007900be0002,0x0000000000000000,0x0000000000000ec0,0x0000000000000c00\n"
".quad 0x0038004000560556,0x0001000b00400004,0x7472747368732e00,0x747274732e006261\n"
".quad 0x746d79732e006261,0x746d79732e006261,0x78646e68735f6261,0x7466752e766e2e00\n"
".quad 0x2e007972746e652e,0x006f666e692e766e,0x5a5f2e747865742e,0x775f6d654d533432\n"
".quad 0x745f574265746972,0x6e72656b5f747365,0x66505f536a506c65,0x666e692e766e2e00\n"
".quad 0x4d5334325a5f2e6f,0x65746972775f6d65,0x5f747365745f5742,0x6a506c656e72656b\n"
".quad 0x766e2e0066505f53,0x2e6465726168732e,0x6d654d5334325a5f,0x574265746972775f\n"
".quad 0x656b5f747365745f,0x5f536a506c656e72,0x632e766e2e006650,0x30746e6174736e6f\n"
".quad 0x654d5334325a5f2e,0x4265746972775f6d,0x6b5f747365745f57,0x536a506c656e7265\n"
".quad 0x6265642e0066505f,0x656d6172665f6775,0x65642e6c65722e00,0x6d6172665f677562\n"
".quad 0x2e616c65722e0065,0x72665f6775626564,0x68732e0000656d61,0x2e00626174727473\n"
".quad 0x2e00626174727473,0x2e006261746d7973,0x735f6261746d7973,0x766e2e0078646e68\n"
".quad 0x746e652e7466752e,0x692e766e2e007972,0x34325a5f006f666e,0x6972775f6d654d53\n"
".quad 0x7365745f57426574,0x6c656e72656b5f74,0x2e0066505f536a50,0x325a5f2e74786574\n"
".quad 0x72775f6d654d5334,0x65745f5742657469,0x656e72656b5f7473,0x0066505f536a506c\n"
".quad 0x6f666e692e766e2e,0x654d5334325a5f2e,0x4265746972775f6d,0x6b5f747365745f57\n"
".quad 0x536a506c656e7265,0x2e766e2e0066505f,0x5f2e646572616873,0x5f6d654d5334325a\n"
".quad 0x5f57426574697277,0x72656b5f74736574,0x505f536a506c656e,0x5a5a5f5f5f240066\n"
".quad 0x775f6d654d533432,0x745f574265746972,0x6e72656b5f747365,0x66505f536a506c65\n"
".quad 0x325f5f7272413345,0x6f632e766e2e0038,0x2e30746e6174736e,0x6d654d5334325a5f\n"
".quad 0x574265746972775f,0x656b5f747365745f,0x5f536a506c656e72,0x617261705f006650\n"
".quad 0x67756265642e006d,0x2e00656d6172665f,0x756265642e6c6572,0x00656d6172665f67\n"
".quad 0x65642e616c65722e,0x6d6172665f677562,0x0000000000000065,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0009000300000063,0x0000000000000000\n"
".quad 0x0000000000000000,0x000a0003000000b8,0x0000000000000000,0x0000000000000000\n"
".quad 0x0008000300000116,0x0000000000000000,0x0000000000000000,0x000400030000014e\n"
".quad 0x0000000000000000,0x0000000000000000,0x0009101200000040,0x0000000000000000\n"
".quad 0x0000000000000600,0x00000024ffffffff,0xffffffff00000000,0x7c040003ffffffff\n"
".quad 0x80810c0fffffffff,0x288081ff08002880,0x0000002880808108,0x00000034ffffffff\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000060000000000,0x0000040400000000\n"
".quad 0x810c000000180400,0x0001380400288080,0x0000000000000000,0x0000000500082f04\n"
".quad 0x0008230400000010,0x0000000000000005,0x0000000500081204,0x0008110400000000\n"
".quad 0x0000000000000005,0x0000007900043704,0x00080a0400003501,0x0018016000000003\n"
".quad 0x000c170400181903,0x0010000200000000,0x000c17040021f000,0x0008000100000000\n"
".quad 0x000c17040021f000,0x0000000000000000,0x00ff1b030021f000,0x0000051000081c04\n"
".quad 0x0000000000000550,0x0000000000000044,0x0000000500000002,0x0000000000000000\n"
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
".quad 0x0000000000097919,0x000e220000002100,0x0000460000047ab9,0x000fc60000000a00\n"
".quad 0x0000000000007b1d,0x000fec0000000000,0x0000000900027312,0x001e240000201c00\n"
".quad 0x3ff0000002027429,0x001e140000000000,0x0000000200027310,0x0010640000301000\n"
".quad 0x00000000000b7805,0x000fc40000005000,0x0000000209007388,0x002fe80000004800\n"
".quad 0x0000800209007388,0x000fe80000004800,0x0001000209007388,0x000fe80000004800\n"
".quad 0x0001800209007388,0x000fe80000004800,0x0002000209007388,0x000fe80000004800\n"
".quad 0x0002800209007388,0x000fe80000004800,0x0003000209007388,0x000fe80000004800\n"
".quad 0x0003800209007388,0x000fe80000004800,0x0004000209007388,0x000fe80000004800\n"
".quad 0x0004800209007388,0x000fe80000004800,0x0005000209007388,0x000fe80000004800\n"
".quad 0x0005800209007388,0x000fe80000004800,0x0006000209007388,0x000fe80000004800\n"
".quad 0x0006800209007388,0x000fe80000004800,0x0007000209007388,0x000fe80000004800\n"
".quad 0x0007800209007388,0x000fe80000004800,0x0008000209007388,0x000fe80000004800\n"
".quad 0x0008800209007388,0x000fe80000004800,0x0009000209007388,0x000fe80000004800\n"
".quad 0x0009800209007388,0x000fe80000004800,0x000a000209007388,0x000fe80000004800\n"
".quad 0x000a800209007388,0x000fe80000004800,0x000b000209007388,0x000fe80000004800\n"
".quad 0x000b800209007388,0x000fe80000004800,0x000c000209007388,0x000fe80000004800\n"
".quad 0x000c800209007388,0x000fe80000004800,0x000d000209007388,0x000fe80000004800\n"
".quad 0x000d800209007388,0x000fe80000004800,0x000e000209007388,0x000fe80000004800\n"
".quad 0x000e800209007388,0x000fe80000004800,0x000f000209007388,0x000fe80000004800\n"
".quad 0x000f800209007388,0x000fe80000004800,0x0010000209007388,0x000fe80000004800\n"
".quad 0x0010800209007388,0x000fe80000004800,0x0011000209007388,0x000fe80000004800\n"
".quad 0x0011800209007388,0x000fe80000004800,0x0012000209007388,0x000fe80000004800\n"
".quad 0x0012800209007388,0x000fe80000004800,0x0013000209007388,0x000fe80000004800\n"
".quad 0x0013800209007388,0x000fe80000004800,0x0014000209007388,0x000fe80000004800\n"
".quad 0x0014800209007388,0x000fe80000004800,0x0015000209007388,0x000fe80000004800\n"
".quad 0x0015800209007388,0x000fe80000004800,0x0016000209007388,0x000fe80000004800\n"
".quad 0x0016800209007388,0x000fe80000004800,0x0017000209007388,0x000fe80000004800\n"
".quad 0x0017800209007388,0x000fe80000004800,0x0018000209007388,0x000fe80000004800\n"
".quad 0x0018800209007388,0x000fe80000004800,0x0019000209007388,0x000fe80000004800\n"
".quad 0x0019800209007388,0x000fe80000004800,0x001a000209007388,0x000fe80000004800\n"
".quad 0x001a800209007388,0x000fe80000004800,0x001b000209007388,0x000fe80000004800\n"
".quad 0x001b800209007388,0x000fe80000004800,0x001c000209007388,0x000fe80000004800\n"
".quad 0x001c800209007388,0x000fe80000004800,0x001d000209007388,0x000fe80000004800\n"
".quad 0x001d800209007388,0x000fe80000004800,0x001e000209007388,0x000fe80000004800\n"
".quad 0x001e800209007388,0x000fe80000004800,0x001f000209007388,0x000fe80000004800\n"
".quad 0x001f800209007388,0x000fe80000004800,0x0000000000007b1d,0x000fec0000000000\n"
".quad 0x00000000000d7805,0x000fc40000005000,0x0000000009077984,0x000e620000004800\n"
".quad 0x00000004ff047424,0x000fc800078e00ff,0x0000580009027625,0x001fc800078e0204\n"
".quad 0x00005a0009047625,0x000fe200078e0204,0x0000000b02007986,0x0001e8000c101904\n"
".quad 0x0000000d04007986,0x0001e2000c101904,0x000000ff0700720b,0x002fda0003f0d000\n"
".quad 0x000000000000094d,0x000fea0003800000,0x00005c0000027a02,0x001fe40000000f00\n"
".quad 0x00005d0000037a02,0x000fca0000000f00,0x0000000702007986,0x000fe2000c101904\n"
".quad 0x000000000000794d,0x000fea0003800000,0xfffffff000007947,0x000fc0000383ffff\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000007918,0x000fc00000000000\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000007918,0x000fc00000000000\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000007918,0x000fc00000000000\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000007918,0x000fc00000000000\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000300000001,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000040,0x0000000000000124,0x0000000000000000\n"
".quad 0x0000000000000001,0x0000000000000000,0x000000030000000b,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000164,0x000000000000017e,0x0000000000000000\n"
".quad 0x0000000000000001,0x0000000000000000,0x0000000200000013,0x0000000000000000\n"
".quad 0x0000000000000000,0x00000000000002e8,0x0000000000000090,0x0000000500000002\n"
".quad 0x0000000000000008,0x0000000000000018,0x00000001000000f4,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000378,0x0000000000000070,0x0000000000000000\n"
".quad 0x0000000000000001,0x0000000000000000,0x7000000000000037,0x0000000000000000\n"
".quad 0x0000000000000000,0x00000000000003e8,0x0000000000000030,0x0000000000000005\n"
".quad 0x0000000000000004,0x0000000000000000,0x7000000000000069,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000418,0x000000000000005c,0x0000000900000005\n"
".quad 0x0000000000000004,0x0000000000000000,0x0000000900000101,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000478,0x0000000000000010,0x0000000400000005\n"
".quad 0x0000000000000008,0x0000000000000010,0x00000001000000c3,0x0000000000000002\n"
".quad 0x0000000000000000,0x0000000000000488,0x0000000000000178,0x0000000900000000\n"
".quad 0x0000000000000004,0x0000000000000000,0x0000000100000040,0x0000000000100006\n"
".quad 0x0000000000000000,0x0000000000000600,0x0000000000000600,0x1000000500000005\n"
".quad 0x0000000000000080,0x0000000000000000,0x0000000800000095,0x0000000000000003\n"
".quad 0x0000000000000000,0x0000000000000c00,0x0000000000003000,0x0000000900000000\n"
".quad 0x0000000000000004,0x0000000000000000,0x0000000500000006,0x0000000000000ec0\n"
".quad 0x0000000000000000,0x0000000000000000,0x00000000000000e0,0x00000000000000e0\n"
".quad 0x0000000000000008,0x0000000500000001,0x0000000000000488,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000778,0x0000000000000778,0x0000000000000008\n"
".quad 0x0000000600000001,0x0000000000000c00,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000003000,0x0000000000000008,0x0000000500000001\n"
".quad 0x0000000000000ec0,0x0000000000000000,0x0000000000000000,0x00000000000000e0\n"
".quad 0x00000000000000e0,0x0000000000000008,0x0000004801010001,0x0000000000000418\n"
".quad 0x0000004000000413,0x0000005600080001,0x0000000000000000,0x0000000000002011\n"
".quad 0x0000000000000000,0x0000000000000cbb,0x0000000000000000,0x762e1cf300010a13\n"
".quad 0x38206e6f69737265,0x677261742e0a312e,0x36385f6d73207465,0x7365726464612e0a\n"
".quad 0x3620657a69735f73,0x6973692eff003034,0x746e652e20656c62,0x5334325a5f207972\n"
".quad 0x746972775f6d654d,0x747365745f574265,0x506c656e72656b5f,0x2e0a2866505f536a\n"
".quad 0x752e206d61726170,0x2e5f111000303436,0x2300382c305f3f00,0x3208f3240038311f\n"
".quad 0x65722e0a7b0a290a,0x20646572702e2067,0x00123b3e323c7025,0x3c66252032336685\n"
".quad 0x3600116210001133,0x3436680022373c72,0x1200002364662520,0x3e30313c6472e000\n"
".quad 0x6168732e090a0a3b,0x696c612e00ff0058,0x38622e2034206e67,0x02f20e00a05a5f20\n"
".quad 0x32315b7272413345,0x6c0a0a3b5d383832,0x005f752e2200df64,0x1600e55b202c324f\n"
".quad 0x331f00413b5d303d,0x000041311f190041,0x5d3291190041311f,0x40752e766f6d0a3b\n"
".quad 0x7425202c3302f001,0x76630a3b782e6469,0x2e2001476e722e74,0x8400586610001c73\n"
".quad 0x6464610a3b337225,0x6800192c3223015e,0x0001304646336430,0x002f323323004206\n"
".quad 0xa0017d3210002e02,0x636e79732e726162,0x83090a26000e3020,0x6f6c635000660000\n"
".quad 0x6c68733300196b63,0x18009f2c342201da,0x01b12c352f00af32,0x3200ca0100b70216\n"
".quad 0x722573003c2c3672,0x01020974730a3b34,0x5d3672255b500254,0x4f01001a321f00a7\n"
".quad 0x2f08001e3832312b,0x38333f09003c3532,0x3231353f08001e34,0x1e3034363f08001e\n"
".quad 0x09009636372f0800,0x302f0a00d239382f,0x3531314f09009732,0x0900990f0b011032\n"
".quad 0x3f09009a3034313f,0x362f0a009b333531,0x9b39372f0a009b36,0x09009b32392f0a00\n"
".quad 0x3f09009b3430323f,0x323f09009b373132,0x34324f09009b3033,0x009b0f0b02283233\n"
".quad 0x2f0a009b38362f0a,0x34392f0a009b3138,0x9b3730333f09009b,0x009b3032333f0900\n"
".quad 0x2f0a030133332f09,0x03351f0b03023433,0x40323137334f0a03,0x391f0a009b0f0b03\n"
".quad 0x030730342f0a0306,0x2f0a030732342f0a,0x34342f0a03073334,0x030736342f0a0307\n"
".quad 0x2f0a030737342f0a,0x39344f0a03073834,0x009b0f0b04583239,0x2f0a030732352f09\n"
".quad 0x35352f0a03073335,0x030736352f0a0307,0x2f0a030737352f0a,0x30362f0a03073835\n"
".quad 0x030731362f0a0307,0x0c05703732363f0a,0x0735362f09009b0f,0x0a030736362f0a03\n"
".quad 0x362f0a030737362f,0x0c30372f0a030739,0x2f0a0307311f0b06,0x34372f0a03073237\n"
".quad 0x323535374f0a0307,0x1f0a009b0f0b0688,0x0739372f0a030738,0x0f03073038260a03\n"
".quad 0xe408403218090840,0x2e6f742e61747663,0x09216c61626f6c67,0x6d83088800084c01\n"
".quad 0x18656469772e6c75,0x3413086535642308,0x2c3626002f02082e,0x00540a3b353f0035\n"
".quad 0x393319001f371103,0x3511001a2c382600,0x00d50200340400d5,0x1b31722f00f06411\n"
".quad 0x327221012a010100,0x662520010b0709de,0x0a3ba208a50009de,0x75656e2e70746573\n"
".quad 0x001e2c3170320019,0x02f0098330663035,0x6172622031702540,0x3042425f5f4c2420\n"
".quad 0x210300c10f013d5f,0x13008c080a3c2c39,0x005b5d3921008c66,0x3ac000470a0a3b35\n"
".quad 0x7d0a0a3b7465720a, 0x0000000000000a0a\n"
".text\n");
#ifdef __cplusplus
extern "C" {
#endif
extern const unsigned long long fatbinData[650];
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
