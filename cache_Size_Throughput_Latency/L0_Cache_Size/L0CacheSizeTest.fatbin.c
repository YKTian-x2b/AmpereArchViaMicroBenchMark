#ifndef __SKIP_INTERNAL_FATBINARY_HEADERS
#include "fatbinary_section.h"
#endif
#define __CUDAFATBINSECTION  ".nvFatBinSegment"
#define __CUDAFATBINDATASECTION  ".nv_fatbin"
asm(
".section .nv_fatbin, \"a\"\n"
".align 8\n"
"fatbinData:\n"
".quad 0x00100001ba55ed50,0x0000000000001388,0x0000004001010002,0x0000000000000ea8\n"
".quad 0x0000000000000000,0x0000005600010007,0x0000000000000000,0x0000000000000011\n"
".quad 0x0000000000000000,0x0000000000000000,0x33010102464c457f,0x0000000000000007\n"
".quad 0x0000007900be0002,0x0000000000000000,0x0000000000000e00,0x0000000000000b80\n"
".quad 0x0038004000560556,0x0001000a00400003,0x7472747368732e00,0x747274732e006261\n"
".quad 0x746d79732e006261,0x746d79732e006261,0x78646e68735f6261,0x7466752e766e2e00\n"
".quad 0x2e007972746e652e,0x006f666e692e766e,0x5a5f2e747865742e,0x68636143304c3332\n"
".quad 0x65745f657a695365,0x656e72656b5f7473,0x3474616f6c66366c,0x66505f30536a5069\n"
".quad 0x666e692e766e2e00,0x304c33325a5f2e6f,0x7a69536568636143,0x6b5f747365745f65\n"
".quad 0x6c66366c656e7265,0x536a50693474616f,0x766e2e0066505f30,0x2e6465726168732e\n"
".quad 0x6143304c33325a5f,0x5f657a6953656863,0x72656b5f74736574,0x616f6c66366c656e\n"
".quad 0x5f30536a50693474,0x632e766e2e006650,0x30746e6174736e6f,0x43304c33325a5f2e\n"
".quad 0x657a695365686361,0x656b5f747365745f,0x6f6c66366c656e72,0x30536a5069347461\n"
".quad 0x6265642e0066505f,0x656d6172665f6775,0x65642e6c65722e00,0x6d6172665f677562\n"
".quad 0x2e616c65722e0065,0x72665f6775626564,0x68732e0000656d61,0x2e00626174727473\n"
".quad 0x2e00626174727473,0x2e006261746d7973,0x735f6261746d7973,0x766e2e0078646e68\n"
".quad 0x746e652e7466752e,0x692e766e2e007972,0x33325a5f006f666e,0x536568636143304c\n"
".quad 0x747365745f657a69,0x366c656e72656b5f,0x50693474616f6c66,0x2e0066505f30536a\n"
".quad 0x325a5f2e74786574,0x6568636143304c33,0x7365745f657a6953,0x6c656e72656b5f74\n"
".quad 0x693474616f6c6636,0x0066505f30536a50,0x6f666e692e766e2e,0x43304c33325a5f2e\n"
".quad 0x657a695365686361,0x656b5f747365745f,0x6f6c66366c656e72,0x30536a5069347461\n"
".quad 0x2e766e2e0066505f,0x5f2e646572616873,0x636143304c33325a,0x745f657a69536568\n"
".quad 0x6e72656b5f747365,0x74616f6c66366c65,0x505f30536a506934,0x6f632e766e2e0066\n"
".quad 0x2e30746e6174736e,0x6143304c33325a5f,0x5f657a6953656863,0x72656b5f74736574\n"
".quad 0x616f6c66366c656e,0x5f30536a50693474,0x617261705f006650,0x67756265642e006d\n"
".quad 0x2e00656d6172665f,0x756265642e6c6572,0x00656d6172665f67,0x65642e616c65722e\n"
".quad 0x6d6172665f677562,0x0000000000000065,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x000900030000006b,0x0000000000000000,0x0000000000000000\n"
".quad 0x0008000300000106,0x0000000000000000,0x0000000000000000,0x0004000300000146\n"
".quad 0x0000000000000000,0x0000000000000000,0x0009101200000040,0x0000000000000000\n"
".quad 0x0000000000000500,0x00000024ffffffff,0xffffffff00000000,0x7c040003ffffffff\n"
".quad 0x80810c0fffffffff,0x288081ff08002880,0x0000002880808108,0x00000034ffffffff\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000050000000000,0x0000040400000000\n"
".quad 0x810c000000140400,0x0000ec0400288080,0x0000000000000000,0x0000000400082f04\n"
".quad 0x0008230400000010,0x0000000000000004,0x0000000400081204,0x0008110400000000\n"
".quad 0x0000000000000004,0x0000007900043704,0x00080a0400003501,0x0030016000000002\n"
".quad 0x000c170400301903,0x0028000400000000,0x000c17040021f000,0x0020000300000000\n"
".quad 0x000c17040021f000,0x0018000200000000,0x000c17040021f000,0x0010000100000000\n"
".quad 0x000c17040011f000,0x0000000000000000,0x00ff1b030041f000,0x0000032000081c04\n"
".quad 0x0000000000000410,0x0000000000000044,0x0000000400000002,0x0000000000000000\n"
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
".quad 0x00005c00ff007624,0x000fe400078e00ff,0x00005800ff097624,0x000fc600078e00ff\n"
".quad 0x000000010000780c,0x040fe40003f06270,0xffffffff00037810,0x000fd60007ffe0ff\n"
".quad 0x0000013000008947,0x000fea0003800000,0x000000030300780c,0x000fe40003f46070\n"
".quad 0x0000000300047812,0x000fc800078ec0ff,0x000000ff0400720c,0x000fce0003f25270\n"
".quad 0x000000900000a947,0x000fec0003800000,0x00005c0004057a10,0x000fe20007ffe1ff\n"
".quad 0x00005a00ff027624,0x000fc600078e00ff,0xfffffffc05057810,0x000fe20007ffe0ff\n"
".quad 0x0000590009097623,0x000fc60000000002,0x000000ff0500720c,0x000fe20003f45270\n"
".quad 0x0000590009097623,0x000fc80000000002,0x0000590009097623,0x000fc80000000002\n"
".quad 0x0000590009097623,0x000fc80000000002,0xffffff9000002947,0x000fea000383ffff\n"
".quad 0x0000005000009947,0x000fea0003800000,0x00005a00ff027624,0x000fc600078e00ff\n"
".quad 0xffffffff04047810,0x000fe20007ffe0ff,0x0000590009097623,0x000fc60000000002\n"
".quad 0x000000ff0400720c,0x000fda0003f25270,0xffffffc000001947,0x000fea000383ffff\n"
".quad 0x0000000000007b1d,0x000fec0000000000,0x00000000000b7805,0x000fc40000005000\n"
".quad 0x0000000000057919,0x000e220000002100,0x0000013000008947,0x000fea0003800000\n"
".quad 0x000000030300780c,0x000fe40003f06070,0x0000000300007812,0x000fc800078ec0ff\n"
".quad 0x000000ff0000720c,0x000fce0003f25270,0x0000009000008947,0x000fec0003800000\n"
".quad 0x00005c0000037a10,0x000fe20007ffe1ff,0x00005a00ff027624,0x000fc600078e00ff\n"
".quad 0xfffffffc03037810,0x000fe20007ffe0ff,0x0000590009097623,0x000fc60000000002\n"
".quad 0x000000ff0300720c,0x000fe20003f05270,0x0000590009097623,0x000fc80000000002\n"
".quad 0x0000590009097623,0x000fc80000000002,0x0000590009097623,0x000fc80000000002\n"
".quad 0xffffff9000000947,0x000fea000383ffff,0x0000005000009947,0x000fea0003800000\n"
".quad 0x00005a00ff027624,0x000fc600078e00ff,0xffffffff00007810,0x000fe20007ffe0ff\n"
".quad 0x0000590009097623,0x000fc60000000002,0x000000ff0000720c,0x000fda0003f05270\n"
".quad 0xffffffc000000947,0x000fea000383ffff,0x00000000000d7805,0x000fc40000005000\n"
".quad 0x0000001f05ff7812,0x001fda000780c0ff,0x000000000000094d,0x000fea0003800000\n"
".quad 0x0000000000037919,0x000e220000002500,0x0000001fff007819,0x000fe20000011405\n"
".quad 0x00000004ff077424,0x000fe200078e00ff,0x0000460000047ab9,0x000fe40000000a00\n"
".quad 0x0000000500027211,0x000fe200078f28ff,0x0000000003007a24,0x001fc600078e02ff\n"
".quad 0x00000005ff037819,0x000fc80000011402,0x0000000300007211,0x000fca00078fdaff\n"
".quad 0x0000620000027625,0x000fc800078e0207,0x00005e0000047625,0x0c0fe200078e0207\n"
".quad 0x0000000902007986,0x000fe6000c101904,0x0000600000067625,0x000fe200078e0207\n"
".quad 0x0000000b04007986,0x000fe8000c101904,0x0000000d06007986,0x000fe2000c101904\n"
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
".quad 0x0000000000000000,0x0000000000000040,0x0000000000000144,0x0000000000000000\n"
".quad 0x0000000000000001,0x0000000000000000,0x000000030000000b,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000184,0x0000000000000176,0x0000000000000000\n"
".quad 0x0000000000000001,0x0000000000000000,0x0000000200000013,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000300,0x0000000000000078,0x0000000400000002\n"
".quad 0x0000000000000008,0x0000000000000018,0x0000000100000114,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000378,0x0000000000000070,0x0000000000000000\n"
".quad 0x0000000000000001,0x0000000000000000,0x7000000000000037,0x0000000000000000\n"
".quad 0x0000000000000000,0x00000000000003e8,0x0000000000000030,0x0000000000000005\n"
".quad 0x0000000000000004,0x0000000000000000,0x7000000000000071,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000418,0x000000000000007c,0x0000000900000005\n"
".quad 0x0000000000000004,0x0000000000000000,0x0000000900000121,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000498,0x0000000000000010,0x0000000400000005\n"
".quad 0x0000000000000008,0x0000000000000010,0x00000001000000db,0x0000000000000002\n"
".quad 0x0000000000000000,0x00000000000004a8,0x0000000000000190,0x0000000900000000\n"
".quad 0x0000000000000004,0x0000000000000000,0x0000000100000040,0x0000000000100006\n"
".quad 0x0000000000000000,0x0000000000000680,0x0000000000000500,0x1000000400000005\n"
".quad 0x0000000000000080,0x0000000000000000,0x0000000500000006,0x0000000000000e00\n"
".quad 0x0000000000000000,0x0000000000000000,0x00000000000000a8,0x00000000000000a8\n"
".quad 0x0000000000000008,0x0000000500000001,0x00000000000004a8,0x0000000000000000\n"
".quad 0x0000000000000000,0x00000000000006d8,0x00000000000006d8,0x0000000000000008\n"
".quad 0x0000000500000001,0x0000000000000e00,0x0000000000000000,0x0000000000000000\n"
".quad 0x00000000000000a8,0x00000000000000a8,0x0000000000000008,0x0000004801010001\n"
".quad 0x0000000000000458,0x0000004000000457,0x0000005600080001,0x0000000000000000\n"
".quad 0x0000000000002011,0x0000000000000000,0x0000000000000b6f,0x0000000000000000\n"
".quad 0x762e1cf200010a13,0x38206e6f69737265,0x677261742e0a312e,0x36385f6d73207465\n"
".quad 0x7365726464612e0a,0x3620657a69735f73,0x6973693fff002f34,0x746e652e20656c62\n"
".quad 0x4c33325a5f207972,0x6953656863614330,0x5f747365745f657a,0x66366c656e72656b\n"
".quad 0x6a50693474616f6c,0x2e0a2866505f3053,0x612e206d61726170,0x203631206e67696c\n"
".quad 0x5f1118004138622e,0x36315b305f75003f,0x3233753f004d2c5d,0x2f004031171f0044\n"
".quad 0x40321f1f00403436,0xf32c0040331f2c00,0x2e0a7b0a290a3409,0x6572702e20676572\n"
".quad 0x3e32313c70252064,0x203233669500133b,0x10001236333c6625,0x35333c7246001262\n"
".quad 0x2520343601f20012,0x0a3b3e31313c6472,0x50010091646c0a0a,0x202c363172257f01\n"
".quad 0x3b5d31371e00975b,0x49311f0061020049,0x1f000049321f2100,0x0049331f21004932\n"
".quad 0x3418210049331f00,0x35332f0160020049,0x0f0049301e210049,0x00932b302f2200da\n"
".quad 0x5d387423004a0f01,0xf001fc766f6d0a3b,0x2e64697425202c04,0x2e707465730a3b78\n"
".quad 0x70330019732e746c,0x3b310cf2021a2c31,0x726220317025400a,0x42425f5f4c242061\n"
".quad 0x64610a0a3b375f30,0x2c37317234002b64,0x6e610a3b312d7300,0x0018323324028264\n"
".quad 0x33007701005e3316,0x5e331100382c3270,0x3b3473005e321900,0x15005e6275730a0a\n"
".quad 0x3b34005200008a33,0x3a330ef300270a0a,0x616d676172702e0a,0x6f726e756f6e2220\n"
".quad 0x616d660a3b226c6c,0x39313301246e722e,0x253b01300101bd2c,0x2c30323600213266\n"
".quad 0x31250200210f0027,0x020200210f00272c,0x060021313228005d,0x00060000be02011c\n"
".quad 0x656e220105342d23,0x11001b337024001c,0x1701053319010530,0x003a3a342200ea33\n"
".quad 0x2c3423003a716523,0x9d341d003a02015f,0x0124361f000c0401,0x00c1351f011e0310\n"
".quad 0x312d2c006c321404,0x35190087351a00c1,0x37d0008736170087,0x2e726162090a0a3a\n"
".quad 0x0a47002e636e7973,0x2c38900285090a09,0x1a6b636f6c632520,0x6f34312a026e0d00\n"
".quad 0x01026f0f01ad0002,0x02a10206026f341f,0x005f371a026f3914,0x004733140270311a\n"
".quad 0x312f00c507005300,0x4d33322e10014d30,0x272c342600210a01,0x2c35250200210f00\n"
".quad 0x5d020200210f0027,0x230401b035322f00,0x1402710e00062c33,0x381a01b002001b38\n"
".quad 0x311c00ec30180107,0x0201632c39230273,0x0d0501a2391e003c,0x0122031103990f00\n"
".quad 0x006e34140500c50f,0x008a30312a02750e,0x033908008b30312a,0x2802690a3a343148\n"
".quad 0x01023b0602693032,0x6f331e050c0003be,0x6f0300212c312300,0x0702e700029c0b00\n"
".quad 0x516e13032e000061,0x3300e30000170705,0x6c75520018617463,0xe9721100606f6c2e\n"
".quad 0x3232728400210201,0x23001a7268730a3b,0x0017351900202c35,0x6372682400ac3618\n"
".quad 0x3228001d2c372300,0x002f383223014b37,0x3923004809002300,0x26017b3519001f2c\n"
".quad 0x3b3902f4007c2c30,0x6f742e617476630a,0x576c61626f6c672e,0xcc33642200b50107\n"
".quad 0x43012e6469773300,0x341300442c356472,0x2c36260030020055,0x50741400ce000036\n"
".quad 0x00215b10020e0000,0x0071351f020a5d11,0x5531642900de0105,0x5509001a2c382600\n"
".quad 0x5d38210055751300,0x01050055381f00fc,0x0200553264290102,0x07005639642f025f\n"
".quad 0x3032190057303121, 0x7465720a3a36d003, 0x00000a0a7d0a0a3b\n"
".text\n");
#ifdef __cplusplus
extern "C" {
#endif
extern const unsigned long long fatbinData[627];
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
