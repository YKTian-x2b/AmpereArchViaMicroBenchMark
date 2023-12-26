#ifndef __SKIP_INTERNAL_FATBINARY_HEADERS
#include "fatbinary_section.h"
#endif
#define __CUDAFATBINSECTION  ".nvFatBinSegment"
#define __CUDAFATBINDATASECTION  ".nv_fatbin"
asm(
".section .nv_fatbin, \"a\"\n"
".align 8\n"
"fatbinData:\n"
".quad 0x00100001ba55ed50,0x0000000000001880,0x0000004001010002,0x0000000000000fa8\n"
".quad 0x0000000000000000,0x0000005600010007,0x0000000000000000,0x0000000000000011\n"
".quad 0x0000000000000000,0x0000000000000000,0x33010102464c457f,0x0000000000000007\n"
".quad 0x0000007900be0002,0x0000000000000000,0x0000000000000f00,0x0000000000000c80\n"
".quad 0x0038004000560556,0x0001000a00400003,0x7472747368732e00,0x747274732e006261\n"
".quad 0x746d79732e006261,0x746d79732e006261,0x78646e68735f6261,0x7466752e766e2e00\n"
".quad 0x2e007972746e652e,0x006f666e692e766e,0x5a5f2e747865742e,0x61746144314c3532\n"
".quad 0x5f57426568636163,0x72656b5f74736574,0x505f536a506c656e,0x766e2e005f305366\n"
".quad 0x5a5f2e6f666e692e,0x61746144314c3532,0x5f57426568636163,0x72656b5f74736574\n"
".quad 0x505f536a506c656e,0x766e2e005f305366,0x2e6465726168732e,0x6144314c35325a5f\n"
".quad 0x4265686361636174,0x6b5f747365745f57,0x536a506c656e7265,0x2e005f305366505f\n"
".quad 0x74736e6f632e766e,0x325a5f2e30746e61,0x6361746144314c35,0x745f574265686361\n"
".quad 0x6e72656b5f747365,0x66505f536a506c65,0x6265642e005f3053,0x656d6172665f6775\n"
".quad 0x65642e6c65722e00,0x6d6172665f677562,0x2e616c65722e0065,0x72665f6775626564\n"
".quad 0x68732e0000656d61,0x2e00626174727473,0x2e00626174727473,0x2e006261746d7973\n"
".quad 0x735f6261746d7973,0x766e2e0078646e68,0x746e652e7466752e,0x692e766e2e007972\n"
".quad 0x35325a5f006f666e,0x616361746144314c,0x65745f5742656863,0x656e72656b5f7473\n"
".quad 0x5366505f536a506c,0x747865742e005f30,0x44314c35325a5f2e,0x6568636163617461\n"
".quad 0x5f747365745f5742,0x6a506c656e72656b,0x005f305366505f53,0x6f666e692e766e2e\n"
".quad 0x44314c35325a5f2e,0x6568636163617461,0x5f747365745f5742,0x6a506c656e72656b\n"
".quad 0x005f305366505f53,0x726168732e766e2e,0x4c35325a5f2e6465,0x6361636174614431\n"
".quad 0x7365745f57426568,0x6c656e72656b5f74,0x305366505f536a50,0x6f632e766e2e005f\n"
".quad 0x2e30746e6174736e,0x6144314c35325a5f,0x4265686361636174,0x6b5f747365745f57\n"
".quad 0x536a506c656e7265,0x5f005f305366505f,0x642e006d61726170,0x6172665f67756265\n"
".quad 0x2e6c65722e00656d,0x72665f6775626564,0x6c65722e00656d61,0x5f67756265642e61\n"
".quad 0x000000656d617266,0x0000000000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0009000300000067,0x0000000000000000,0x0000000000000000,0x00080003000000f6\n"
".quad 0x0000000000000000,0x0000000000000000,0x0004000300000132,0x0000000000000000\n"
".quad 0x0000000000000000,0x0009101200000040,0x0000000000000000,0x0000000000000680\n"
".quad 0x00000024ffffffff,0xffffffff00000000,0x7c040003ffffffff,0x80810c0fffffffff\n"
".quad 0x288081ff08002880,0x0000002880808108,0x00000034ffffffff,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000068000000000,0x0000040400000000,0x810c000000180400\n"
".quad 0x0001500400288080,0x0000000000000000,0x0000000400082f04,0x0008230400000026\n"
".quad 0x0000000000000004,0x0000000400081204,0x0008110400000000,0x0000000000000004\n"
".quad 0x0000007900043704,0x00080a0400003501,0x0020016000000002,0x000c170400201903\n"
".quad 0x0018000300000000,0x000c17040021f000,0x0010000200000000,0x000c17040021f000\n"
".quad 0x0008000100000000,0x000c17040021f000,0x0000000000000000,0x00ff1b030021f000\n"
".quad 0x000005b000041c04,0x0000000000000044,0x0000000400000002,0x0000000000000000\n"
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
".quad 0x0000000000000000,0x0000000000000000,0x00000a0000017a02,0x000fc40000000f00\n"
".quad 0x0000000000047919,0x000e220000002100,0x0000000400037802,0x000fe20000000f00\n"
".quad 0x0000460000047ab9,0x000fe40000000a00,0x0000000000007b1d,0x000fec0000000000\n"
".quad 0x00005e0004027625,0x001fe200078e0203,0x0000001fff077819,0x000fc60000011404\n"
".quad 0x0000000000007805,0x000fc80000005000,0x000000ff001b7202,0x000fe40000000f00\n"
".quad 0x000000ff00217202,0x000fc40000000f00,0x00000004021e7981,0x000ea8000c1eb900\n"
".quad 0x00008004021f7981,0x000ee8000c1eb900,0x0001000402207981,0x000f28000c1eb900\n"
".quad 0x00018004021d7981,0x000f68000c1eb900,0x00020004021c7981,0x000f68000c1eb900\n"
".quad 0x0002800402067981,0x000f68000c1eb900,0x0003000402057981,0x000f68000c1eb900\n"
".quad 0x00038004021a7981,0x000f68000c1eb900,0x0004000402197981,0x000168000c1eb900\n"
".quad 0x0004800402187981,0x000168000c1eb900,0x0005000402177981,0x000168000c1eb900\n"
".quad 0x0005800402167981,0x000168000c1eb900,0x0006000402157981,0x000168000c1eb900\n"
".quad 0x0006800402147981,0x000168000c1eb900,0x0007000402137981,0x000168000c1eb900\n"
".quad 0x0007800402127981,0x000168000c1eb900,0x0008000402117981,0x000168000c1eb900\n"
".quad 0x0008800402107981,0x000168000c1eb900,0x00090004020f7981,0x000168000c1eb900\n"
".quad 0x00098004020e7981,0x000168000c1eb900,0x000a0004020d7981,0x000168000c1eb900\n"
".quad 0x000a8004020c7981,0x000168000c1eb900,0x000b0004020b7981,0x000168000c1eb900\n"
".quad 0x000b8004020a7981,0x000168000c1eb900,0x000c000402097981,0x000168000c1eb900\n"
".quad 0x000c800402087981,0x000162000c1eb900,0x0000001b1e1e7221,0x004fc60000000000\n"
".quad 0x000d0004021b7981,0x0000a2000c1eb900,0x0000001f1e1f7221,0x008fc60000000000\n"
".quad 0x000d8004021e7981,0x0000e2000c1eb900,0x000000201f207221,0x010fc60000000000\n"
".quad 0x000e0004021f7981,0x000122000c1eb900,0x0000001d20237221,0x020fc60000000000\n"
".quad 0x000e8004021d7981,0x000162000c1eb900,0x0000001c23237221,0x000fc60000000000\n"
".quad 0x000f0004021c7981,0x000168000c1eb900,0x000f800402207981,0x000162000c1eb900\n"
".quad 0x0000000623067221,0x000fe20000000000,0x0000040021217810,0x000fc60007ffe0ff\n"
".quad 0x0000000506057221,0x000fe20000000000,0x000060002100780c,0x000fc60003f06070\n"
".quad 0x0000001a051a7221,0x000fe20000000000,0x0000100002027810,0x001fc60007f3e0ff\n"
".quad 0x000000191a197221,0x000fe20000000000,0x00000003ff037210,0x000fc60000ffe4ff\n"
".quad 0x0000001819187221,0x000fc80000000000,0x0000001718177221,0x000fc80000000000\n"
".quad 0x0000001617167221,0x000fc80000000000,0x0000001516157221,0x000fc80000000000\n"
".quad 0x0000001415147221,0x000fc80000000000,0x0000001314137221,0x000fc80000000000\n"
".quad 0x0000001213127221,0x000fc80000000000,0x0000001112117221,0x000fc80000000000\n"
".quad 0x0000001011107221,0x000fc80000000000,0x0000000f100f7221,0x000fc80000000000\n"
".quad 0x0000000e0f0e7221,0x000fc80000000000,0x0000000d0e0d7221,0x000fc80000000000\n"
".quad 0x0000000c0d0c7221,0x000fc80000000000,0x0000000b0c0b7221,0x000fc80000000000\n"
".quad 0x0000000a0b0a7221,0x000fc80000000000,0x000000090a097221,0x000fc80000000000\n"
".quad 0x0000000809087221,0x000fc80000000000,0x0000001b081b7221,0x004fc80000000000\n"
".quad 0x0000001e1b1e7221,0x008fc80000000000,0x0000001f1e1e7221,0x010fc80000000000\n"
".quad 0x0000001d1e1d7221,0x020fc80000000000,0x0000001c1d1d7221,0x000fc80000000000\n"
".quad 0x000000201d1b7221,0x000fe20000000000,0xfffffbb000008947,0x000fea000383ffff\n"
".quad 0x0000000000097805,0x000fc40000005000,0x0000000204067819,0x040fe400000006ff\n"
".quad 0x0000000204077819,0x000fe40000010207,0x0000580006027a10,0x040fe40007f1e0ff\n"
".quad 0x00005a0006047a10,0x040fe40007f3e0ff,0x00005c0006067a10,0x000fe40007f5e0ff\n"
".quad 0x0000590007037a10,0x000fc400007fe4ff,0x00005b0007057a10,0x040fe40000ffe4ff\n"
".quad 0x00005d0007077a10,0x000fe200017fe4ff,0x0000000002007986,0x000fe8000c101904\n"
".quad 0x0000000904007986,0x000fe8000c101904,0x0000001b06007986,0x000fe2000c101904\n"
".quad 0x000000000000794d,0x000fea0003800000,0xfffffff000007947,0x000fc0000383ffff\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000007918,0x000fc00000000000\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000007918,0x000fc00000000000\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000007918,0x000fc00000000000\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000007918,0x000fc00000000000\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000007918,0x000fc00000000000\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000300000001,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000040,0x0000000000000134,0x0000000000000000\n"
".quad 0x0000000000000001,0x0000000000000000,0x000000030000000b,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000174,0x0000000000000162,0x0000000000000000\n"
".quad 0x0000000000000001,0x0000000000000000,0x0000000200000013,0x0000000000000000\n"
".quad 0x0000000000000000,0x00000000000002d8,0x0000000000000078,0x0000000400000002\n"
".quad 0x0000000000000008,0x0000000000000018,0x0000000100000104,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000350,0x0000000000000070,0x0000000000000000\n"
".quad 0x0000000000000001,0x0000000000000000,0x7000000000000037,0x0000000000000000\n"
".quad 0x0000000000000000,0x00000000000003c0,0x0000000000000030,0x0000000000000005\n"
".quad 0x0000000000000004,0x0000000000000000,0x700000000000006d,0x0000000000000000\n"
".quad 0x0000000000000000,0x00000000000003f0,0x0000000000000068,0x0000000900000005\n"
".quad 0x0000000000000004,0x0000000000000000,0x0000000900000111,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000458,0x0000000000000010,0x0000000400000005\n"
".quad 0x0000000000000008,0x0000000000000010,0x00000001000000cf,0x0000000000000002\n"
".quad 0x0000000000000000,0x0000000000000468,0x0000000000000180,0x0000000900000000\n"
".quad 0x0000000000000004,0x0000000000000000,0x0000000100000040,0x0000000000100006\n"
".quad 0x0000000000000000,0x0000000000000600,0x0000000000000680,0x2600000400000005\n"
".quad 0x0000000000000080,0x0000000000000000,0x0000000500000006,0x0000000000000f00\n"
".quad 0x0000000000000000,0x0000000000000000,0x00000000000000a8,0x00000000000000a8\n"
".quad 0x0000000000000008,0x0000000500000001,0x0000000000000468,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000818,0x0000000000000818,0x0000000000000008\n"
".quad 0x0000000500000001,0x0000000000000f00,0x0000000000000000,0x0000000000000000\n"
".quad 0x00000000000000a8,0x00000000000000a8,0x0000000000000008,0x0000004801010001\n"
".quad 0x0000000000000850,0x000000400000084e,0x0000005600080001,0x0000000000000000\n"
".quad 0x0000000000002011,0x0000000000000000,0x00000000000018c9,0x0000000000000000\n"
".quad 0x762e1cf200010a13,0x38206e6f69737265,0x677261742e0a312e,0x36385f6d73207465\n"
".quad 0x7365726464612e0a,0x3620657a69735f73,0x69736932ff002f34,0x746e652e20656c62\n"
".quad 0x4c35325a5f207972,0x6361636174614431,0x7365745f57426568,0x6c656e72656b5f74\n"
".quad 0x305366505f536a50,0x617261702e0a285f,0x00343436752e206d,0x305f3f00325f1114\n"
".quad 0x003c311f27003c2c,0x08f328003c321f28,0x722e0a7b0a290a33,0x646572702e206765\n"
".quad 0x123b3e333c702520,0x662520323366a500,0x621000133030313c,0x0025313c72360013\n"
".quad 0x72252034366202f2,0x0a0a3b3e35383c64,0x752e22008d646c0a,0x5b202c30315f0018\n"
".quad 0x463b5d303e1a0094,0x311f1d0046321f00,0x1d0046311f010046,0x46331f010046321f\n"
".quad 0x0a3b5d3303f51d00,0x2e6f742e61747663,0x004c6c61626f6c67,0x0a3b328100062c11\n"
".quad 0x91015d752e766f6d,0x2e64697425202c37,0x3436732e61003578,0x2e3264200019732e\n"
".quad 0x6c756d0a3b37b400,0x320018656469772e,0x3b348200382c3431,0x005d732e6464610a\n"
".quad 0x250100b02c343834,0x13010b0000650800,0x2702002e03001130,0x0a0a3b343805f400\n"
".quad 0x5f3042425f5f4c24,0xb5646c090a0a3a31,0x0200021361632300,0x0a3b5d5700330101\n"
".quad 0x2c3631340073090a,0x3e3b3832314f004c,0x312d003e34120300,0x3f003e3715003e36\n"
".quad 0x351304003e363532,0x3815003e371d003e,0x003e3438333f003e,0x3e381d003e361304\n"
".quad 0x31353f003e391500,0x003e371304003e32,0x3e303225003e391c,0x04003e3034363f00\n"
".quad 0x3e30322d003e3812,0x36372f003e311500,0x1d003e3913050136,0x2f003e3215003e31\n"
".quad 0x3031230501363938,0x3315003f321d003f,0x01383230313f003f,0xf30d004031312305\n"
".quad 0x312f004034322601,0x4032312305013a35,0x3335180040341d00,0x33312305013c0f02\n"
".quad 0x73070040351d0040,0x2305013e30342f02,0x1602750d00403431,0x403335313f027532\n"
".quad 0x77321d0277030601,0x36313f0277321602,0x1d02790306014036,0x3f02793216027932\n"
".quad 0x7b03060140393731,0x7b3316027b321d02,0x0601403239313f02,0x16027d331d027d03\n"
".quad 0x403430323f027d33,0x7f331d027f030601,0x31323f027f331602,0x4030322305014037\n"
".quad 0x0280331602800d00,0x230501403033323f,0x1602800d00403132,0x403334323f028033\n"
".quad 0x0d00403232230501,0x0f04753533280280,0x0040333223050140,0x3f0280331602800d\n"
".quad 0x3223050140383632,0x331702800d004034,0x06014031382f04f5,0x160280331d028003\n"
".quad 0x403439323f028033,0x80331d0280030601,0x30333f0280331602,0x1d02800306014037\n"
".quad 0x3f02803416028033,0x8003060140303233,0x8034160280341d02,0x2306063433332f02\n"
".quad 0x1602800d00403932,0x063634332f028034,0x800d004030332306,0x35332f0280341602\n"
".quad 0x0040313323060638,0x2f0280341602800d,0x32332306063a3733,0x35342802800d0040\n"
".quad 0x33230501400f06b7,0x341602800d004033,0x06063e39332f0280,0x02800d0040343323\n"
".quad 0x3034430040333825,0x0208250508423639,0x657372061a020006,0x150843746c2e7074\n"
".quad 0xf835343230001d70,0x6220317025409503,0x0a3b2f083e206172,0x312f00b3020408f7\n"
".quad 0x1103130205091731,0x2e72616291010d31,0x26000e20636e7973,0x7202f90008c4090a\n"
".quad 0x170a3b6b636f6c63,0x2c39397300eb0200,0xf509000130663020,0x08df0508f5321108\n"
".quad 0x032d030508df331f,0x3300190201ad3816,0x00250000612c3836,0x742c383434096d09\n"
".quad 0x3733230708fa0f09,0x39250059381c0186,0x005937332a005f2c,0x0709150f00593915\n"
".quad 0x59391b0059383323,0x29005f2c30373500,0x5930352500593833,0x3933220709300f00\n"
".quad 0x25005930352c0059,0x5939332a005f2c31,0x094b0f0059311500,0x311c005930342307\n"
".quad 0x2a005f2c32250059,0x0059321500593034,0x593134230709660f,0x2c33250059321c00\n"
".quad 0x15005931342a005f,0x230709810f005933,0x0059331c00593234,0x32342a005f2c3425\n"
".quad 0x9c0f005934150059,0x0c00593334230709,0x005f2c353735026f,0x593515005933342a\n"
".quad 0x3434230809b60f00,0x3625005a351c005a,0x005a34342a00602c,0x0709d00f005a3616\n"
".quad 0x5a361c005a353423,0x342a00602c372500,0x0f005a3716005a35,0x005a3634230709ea\n"
".quad 0x602c3825005a371c,0x383526037d341a00,0x3413070a040f005a,0x3735037e351c037e\n"
".quad 0x037e341a00602c39,0x0a1e0f005a393526,0x7f0c005a38342307,0x2900602c30383503\n"
".quad 0x5a303626005a3834,0x393422070a380f00,0x38350380361c005a,0x0380341a00602c31\n"
".quad 0x0a520f005a313626,0x810c005a30352307,0x1a00602c32383503,0x005a323626038135\n"
".quad 0x5a313523070a6c0f,0x03066b0103820c00,0x36250382351a0060,0x23080a860f005a33\n"
".quad 0x0003830c005a3235,0x32352a0060040038,0xa00f005a3416005a,0x0c005a333523070a\n"
".quad 0x00602c3538350384,0x5a3536260384351a,0x343523070aba0f00,0x36383503840c005a\n"
".quad 0x260384351a00602c,0x070ad40f005a3636,0x03840c005a353523,0x351a00602c373835\n"
".quad 0x0f005a3736260384,0x005a363523070aee,0x602c38383503840c,0x3816005a36352a00\n"
".quad 0x3523070b080f005a,0x383503840c005a37,0x0384351a00602c39,0x0b220f005a393626\n"
".quad 0x840c005a38352307,0x1a00602c30393503,0x005a303726038435,0x5a393522070b3c0f\n"
".quad 0x3139350384371c00,0x250384351a00602c,0x080b560f005a3137,0x03840c005a303623\n"
".quad 0x362a00602c323935,0x0f005a3216005a30,0x005a313623070b70,0x602c33393503840c\n"
".quad 0x3337260384361a00,0x3623070b8a0f005a,0x393503840c005a32,0x0384361a00602c34\n"
".quad 0x0ba40f005a343726,0x840c005a33362307,0x1a00602c35393503,0x005a353726038436\n"
".quad 0x5a343623070bbe0f,0x2c36393503840c00,0x16005a34362a0060,0x23070bd80f005a36\n"
".quad 0x3503840c005a3536,0x84361a00602c3739,0xf20f005a37372603,0x0c005a363623070b\n"
".quad 0x00602c3839350384,0x5a3837260384361a,0x373623070c0c0f00,0x0ad90203840c005a\n"
".quad 0x250384361a006002,0x230c260d005a3438,0x010c260f00062c32,0x32190c2606001d05\n"
".quad 0xd607163633100c26,0x73340bd73031280b,0x0107460116626c68,0x070401025d0a1505\n"
".quad 0x010387371a0c3404,0x001c0015670406c6,0x006e00010f747324,0x001e5d10003f5b11\n"
".quad 0x1c311102001c381f,0xd401005530312a00,0x1400005536642f00,0x014b5d3221003966\n"
".quad 0x3b7465720a3b39d0, 0x0000000a0a7d0a0a\n"
".text\n");
#ifdef __cplusplus
extern "C" {
#endif
extern const unsigned long long fatbinData[786];
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
