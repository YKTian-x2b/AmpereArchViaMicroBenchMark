#ifndef __SKIP_INTERNAL_FATBINARY_HEADERS
#include "fatbinary_section.h"
#endif
#define __CUDAFATBINSECTION  ".nvFatBinSegment"
#define __CUDAFATBINDATASECTION  ".nv_fatbin"
asm(
".section .nv_fatbin, \"a\"\n"
".align 8\n"
"fatbinData:\n"
".quad 0x00100001ba55ed50,0x0000000000001800,0x0000004001010002,0x0000000000001420\n"
".quad 0x0000000000000000,0x0000005600010007,0x0000000000000000,0x0000000000000011\n"
".quad 0x0000000000000000,0x0000000000000000,0x33010102464c457f,0x0000000000000007\n"
".quad 0x0000007900be0002,0x0000000000000000,0x0000000000001340,0x0000000000001080\n"
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
".quad 0x325f5f7272413345,0x6f632e766e2e0037,0x2e30746e6174736e,0x6d654d5334325a5f\n"
".quad 0x574265746972775f,0x656b5f747365745f,0x5f536a506c656e72,0x617261705f006650\n"
".quad 0x67756265642e006d,0x2e00656d6172665f,0x756265642e6c6572,0x00656d6172665f67\n"
".quad 0x65642e616c65722e,0x6d6172665f677562,0x0000000000000065,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0009000300000063,0x0000000000000000\n"
".quad 0x0000000000000000,0x000a0003000000b8,0x0000000000000000,0x0000000000000000\n"
".quad 0x0008000300000116,0x0000000000000000,0x0000000000000000,0x000400030000014e\n"
".quad 0x0000000000000000,0x0000000000000000,0x0009101200000040,0x0000000000000000\n"
".quad 0x0000000000000a80,0x00000024ffffffff,0xffffffff00000000,0x7c040003ffffffff\n"
".quad 0x80810c0fffffffff,0x288081ff08002880,0x0000002880808108,0x00000034ffffffff\n"
".quad 0x0000000000000000,0x0000000000000000,0x00000a8000000000,0x0000040400000000\n"
".quad 0x810c000000040400,0x00025c0400288080,0x0000000000000000,0x0000000500082f04\n"
".quad 0x000823040000000e,0x0000000000000005,0x0000000500081204,0x0008110400000000\n"
".quad 0x0000000000000005,0x0000007900043704,0x00080a0400003501,0x0018016000000003\n"
".quad 0x000c170400181903,0x0010000200000000,0x000c17040021f000,0x0008000100000000\n"
".quad 0x000c17040021f000,0x0000000000000000,0x00ff1b030021f000,0x0000095000081c04\n"
".quad 0x0000000000000990,0x0000000000000044,0x0000000500000002,0x0000000000000000\n"
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
".quad 0x0000460000047ab9,0x000fca0000000a00,0x0000000000097805,0x000fc40000005000\n"
".quad 0x0000000000067919,0x000e220000002100,0x000000ffff027224,0x000fe400078e00ff\n"
".quad 0x0000000406007824,0x001fca00078e00ff,0x0000080000007810,0x000fc40007ffe0ff\n"
".quad 0x0000100002027810,0x000fe40007ffe0ff,0x3f80000000037802,0x000fe40000000f00\n"
".quad 0x000020000200780c,0x000fc60003f06070,0xfff8000300007388,0x000fe80000000800\n"
".quad 0xfff8800300007388,0x000fe80000000800,0xfff9000300007388,0x000fe80000000800\n"
".quad 0xfff9800300007388,0x000fe80000000800,0xfffa000300007388,0x000fe80000000800\n"
".quad 0xfffa800300007388,0x000fe80000000800,0xfffb000300007388,0x000fe80000000800\n"
".quad 0xfffb800300007388,0x000fe80000000800,0xfffc000300007388,0x000fe80000000800\n"
".quad 0xfffc800300007388,0x000fe80000000800,0xfffd000300007388,0x000fe80000000800\n"
".quad 0xfffd800300007388,0x000fe80000000800,0xfffe000300007388,0x000fe80000000800\n"
".quad 0xfffe800300007388,0x000fe80000000800,0xffff000300007388,0x000fe80000000800\n"
".quad 0xffff800300007388,0x000fe80000000800,0x0000000300007388,0x000fe80000000800\n"
".quad 0x0000800300007388,0x000fe80000000800,0x0001000300007388,0x000fe80000000800\n"
".quad 0x0001800300007388,0x000fe80000000800,0x0002000300007388,0x000fe80000000800\n"
".quad 0x0002800300007388,0x000fe80000000800,0x0003000300007388,0x000fe80000000800\n"
".quad 0x0003800300007388,0x000fe80000000800,0x0004000300007388,0x000fe80000000800\n"
".quad 0x0004800300007388,0x000fe80000000800,0x0005000300007388,0x000fe80000000800\n"
".quad 0x0005800300007388,0x000fe80000000800,0x0006000300007388,0x000fe80000000800\n"
".quad 0x0006800300007388,0x000fe80000000800,0x0007000300007388,0x000fe80000000800\n"
".quad 0x0007800300007388,0x000fe80000000800,0x0008000300007388,0x000fe80000000800\n"
".quad 0x0008800300007388,0x000fe80000000800,0x0009000300007388,0x000fe80000000800\n"
".quad 0x0009800300007388,0x000fe80000000800,0x000a000300007388,0x000fe80000000800\n"
".quad 0x000a800300007388,0x000fe80000000800,0x000b000300007388,0x000fe80000000800\n"
".quad 0x000b800300007388,0x000fe80000000800,0x000c000300007388,0x000fe80000000800\n"
".quad 0x000c800300007388,0x000fe80000000800,0x000d000300007388,0x000fe80000000800\n"
".quad 0x000d800300007388,0x000fe80000000800,0x000e000300007388,0x000fe80000000800\n"
".quad 0x000e800300007388,0x000fe80000000800,0x000f000300007388,0x000fe80000000800\n"
".quad 0x000f800300007388,0x000fe80000000800,0x0010000300007388,0x000fe80000000800\n"
".quad 0x0010800300007388,0x000fe80000000800,0x0011000300007388,0x000fe80000000800\n"
".quad 0x0011800300007388,0x000fe80000000800,0x0012000300007388,0x000fe80000000800\n"
".quad 0x0012800300007388,0x000fe80000000800,0x0013000300007388,0x000fe80000000800\n"
".quad 0x0013800300007388,0x000fe80000000800,0x0014000300007388,0x000fe80000000800\n"
".quad 0x0014800300007388,0x000fe80000000800,0x0015000300007388,0x000fe80000000800\n"
".quad 0x0015800300007388,0x000fe80000000800,0x0016000300007388,0x000fe80000000800\n"
".quad 0x0016800300007388,0x000fe80000000800,0x0017000300007388,0x000fe80000000800\n"
".quad 0x0017800300007388,0x000fe80000000800,0x0018000300007388,0x000fe80000000800\n"
".quad 0x0018800300007388,0x000fe80000000800,0x0019000300007388,0x000fe80000000800\n"
".quad 0x0019800300007388,0x000fe80000000800,0x001a000300007388,0x000fe80000000800\n"
".quad 0x001a800300007388,0x000fe80000000800,0x001b000300007388,0x000fe80000000800\n"
".quad 0x001b800300007388,0x000fe80000000800,0x001c000300007388,0x000fe80000000800\n"
".quad 0x001c800300007388,0x000fe80000000800,0x001d000300007388,0x000fe80000000800\n"
".quad 0x001d800300007388,0x000fe80000000800,0x001e000300007388,0x000fe80000000800\n"
".quad 0x001e800300007388,0x000fe80000000800,0x001f000300007388,0x000fe80000000800\n"
".quad 0x001f800300007388,0x000fe80000000800,0x0020000300007388,0x000fe80000000800\n"
".quad 0x0020800300007388,0x000fe80000000800,0x0021000300007388,0x000fe80000000800\n"
".quad 0x0021800300007388,0x000fe80000000800,0x0022000300007388,0x000fe80000000800\n"
".quad 0x0022800300007388,0x000fe80000000800,0x0023000300007388,0x000fe80000000800\n"
".quad 0x0023800300007388,0x000fe80000000800,0x0024000300007388,0x000fe80000000800\n"
".quad 0x0024800300007388,0x000fe80000000800,0x0025000300007388,0x000fe80000000800\n"
".quad 0x0025800300007388,0x000fe80000000800,0x0026000300007388,0x000fe80000000800\n"
".quad 0x0026800300007388,0x000fe80000000800,0x0027000300007388,0x000fe80000000800\n"
".quad 0x0027800300007388,0x000fe80000000800,0x0028000300007388,0x000fe80000000800\n"
".quad 0x0028800300007388,0x000fe80000000800,0x0029000300007388,0x000fe80000000800\n"
".quad 0x0029800300007388,0x000fe80000000800,0x002a000300007388,0x000fe80000000800\n"
".quad 0x002a800300007388,0x000fe80000000800,0x002b000300007388,0x000fe80000000800\n"
".quad 0x002b800300007388,0x000fe80000000800,0x002c000300007388,0x000fe80000000800\n"
".quad 0x002c800300007388,0x000fe80000000800,0x002d000300007388,0x000fe80000000800\n"
".quad 0x002d800300007388,0x000fe80000000800,0x002e000300007388,0x000fe80000000800\n"
".quad 0x002e800300007388,0x000fe80000000800,0x002f000300007388,0x000fe80000000800\n"
".quad 0x002f800300007388,0x000fe80000000800,0x0030000300007388,0x000fe80000000800\n"
".quad 0x0030800300007388,0x000fe80000000800,0x0031000300007388,0x000fe80000000800\n"
".quad 0x0031800300007388,0x000fe80000000800,0x0032000300007388,0x000fe80000000800\n"
".quad 0x0032800300007388,0x000fe80000000800,0x0033000300007388,0x000fe80000000800\n"
".quad 0x0033800300007388,0x000fe80000000800,0x0034000300007388,0x000fe80000000800\n"
".quad 0x0034800300007388,0x000fe80000000800,0x0035000300007388,0x000fe80000000800\n"
".quad 0x0035800300007388,0x000fe80000000800,0x0036000300007388,0x000fe80000000800\n"
".quad 0x0036800300007388,0x000fe80000000800,0x0037000300007388,0x000fe80000000800\n"
".quad 0x0037800300007388,0x0001e40000000800,0x0000400000007810,0x001fe20007ffe0ff\n"
".quad 0xfffff7b000008947,0x000fea000383ffff,0x00000000000b7805,0x000fc40000005000\n"
".quad 0x0000000000007b1d,0x000fec0000000000,0x0000000006077984,0x000e220000004800\n"
".quad 0x00000004ff057424,0x000fc800078e00ff,0x0000580006027625,0x000fc800078e0205\n"
".quad 0x00005a0006047625,0x000fe200078e0205,0x0000000902007986,0x0003e8000c101904\n"
".quad 0x0000000b04007986,0x0003e2000c101904,0x000000ff0700720b,0x001fda0003f0d000\n"
".quad 0x000000000000094d,0x000fea0003800000,0x00005c00ff027624,0x002fe200078e00ff\n"
".quad 0x00005d0000037a02,0x000fca0000000f00,0x0000000702007986,0x000fe2000c101904\n"
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
".quad 0x0000000000000000,0x0000000000000600,0x0000000000000a80,0x0e00000500000005\n"
".quad 0x0000000000000080,0x0000000000000000,0x0000000800000095,0x0000000000000003\n"
".quad 0x0000000000000000,0x0000000000001080,0x0000000000009000,0x0000000900000000\n"
".quad 0x0000000000000004,0x0000000000000000,0x0000000500000006,0x0000000000001340\n"
".quad 0x0000000000000000,0x0000000000000000,0x00000000000000e0,0x00000000000000e0\n"
".quad 0x0000000000000008,0x0000000500000001,0x0000000000000488,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000bf8,0x0000000000000bf8,0x0000000000000008\n"
".quad 0x0000000600000001,0x0000000000001080,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000009000,0x0000000000000008,0x0000000500000001\n"
".quad 0x0000000000001340,0x0000000000000000,0x0000000000000000,0x00000000000000e0\n"
".quad 0x00000000000000e0,0x0000000000000008,0x0000004801010001,0x0000000000000358\n"
".quad 0x0000004000000354,0x0000005600080001,0x0000000000000000,0x0000000000002011\n"
".quad 0x0000000000000000,0x0000000000000966,0x0000000000000000,0x762e1cf300010a13\n"
".quad 0x38206e6f69737265,0x677261742e0a312e,0x36385f6d73207465,0x7365726464612e0a\n"
".quad 0x3620657a69735f73,0x6973692eff003034,0x746e652e20656c62,0x5334325a5f207972\n"
".quad 0x746972775f6d654d,0x747365745f574265,0x506c656e72656b5f,0x2e0a2866505f536a\n"
".quad 0x752e206d61726170,0x2e5f111000303436,0x2300382c305f3f00,0x3208f3240038311f\n"
".quad 0x65722e0a7b0a290a,0x20646572702e2067,0x00123b3e333c7025,0x3c66252032336685\n"
".quad 0x4600116210001132,0x3680001230323c72,0x13313c6472252034,0x6168732e090a6000\n"
".quad 0x696c612e00ff0047,0x38622e2034206e67,0x02f20e008f5a5f20,0x36335b7272413345\n"
".quad 0x6c0a0a3b5d343638,0x005f752e2200ce64,0x1600d45b202c324f,0x341f00413b5d303d\n"
".quad 0x000041311f190041,0x3203f4190041331f,0x2e617476630a3b5d,0x61626f6c672e6f74\n"
".quad 0x00062c312000476c,0x766f6d51012b3410,0x202c389a0150752e,0x00176b636f6c6325\n"
".quad 0x64697425202c32e3,0x7c6c68730a3b782e,0x36001b2c30313201,0x31313f002b0a3b32\n"
".quad 0x610a3b721601662c,0x32230038732e6464,0x1a09005a00003e2c,0x324900202c382300\n"
".quad 0x3902f8006c383430,0x4c240a0a3b30202c,0x3a315f3042425f5f,0x31202c3302f3001d\n"
".quad 0x3132333533353630,0x01021274730a3b36,0x2b2000585b100020,0x1f005f5d1100522d\n"
".quad 0x3239314f04002233,0x3239373f0c002230,0x223436363f0c0022,0x00223633353f0c00\n"
".quad 0x2f0d00aa30342f0c,0x35312f0d00aa3832,0x00aa32302f0d00aa,0x2f0c00a939382f0c\n"
".quad 0x34362f0c00a83637,0x00a631352f0c00a7,0x3f0c00a538332f0c,0x210f0e012c363532\n"
".quad 0x3c0f0a003d0f0900,0x0f0d007d2b1f0c00,0x0f0d00ff0f0d00be,0x0f0d01810f0d0140\n"
".quad 0x0f0e02040f0d01c2,0x0f0e028a0f0e0247,0x0f0e03100f0e02cd,0x090e03960f0e0353\n"
".quad 0x2c3879046e0d03d9,0x23001a3639303420,0x9101220000062c39,0x6c2e707465730a3b\n"
".quad 0x1d31702534005374,0x3b3239313800f500,0x726220317025400a,0x890a3b2f049c2061\n"
".quad 0x0a06582c35210405,0xa1058a3431280572,0x79732e726162090a,0x756d099304f0636e\n"
".quad 0x009a656469772e6c,0xb03413058a366423,0x5f2c372600590200,0x0200790405010200\n"
".quad 0x1901003764210105,0x061d2c3826003538,0x1101b9030200350f,0x9e02015603069934\n"
".quad 0x313300212c312007,0x75656e32011c5d32,0x001f2c327032001a,0x2201000130663033\n"
".quad 0x22341f0122321901,0x3364280179010601,0x3921008e6613008e,0x34d0060507005b5d\n"
".quad 0x0a0a3b7465720a3a, 0x00000000000a0a7d\n"
".text\n");
#ifdef __cplusplus
extern "C" {
#endif
extern const unsigned long long fatbinData[770];
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
