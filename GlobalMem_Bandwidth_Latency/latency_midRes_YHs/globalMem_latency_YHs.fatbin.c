#ifndef __SKIP_INTERNAL_FATBINARY_HEADERS
#include "fatbinary_section.h"
#endif
#define __CUDAFATBINSECTION  ".nvFatBinSegment"
#define __CUDAFATBINDATASECTION  ".nv_fatbin"
asm(
".section .nv_fatbin, \"a\"\n"
".align 8\n"
"fatbinData:\n"
".quad 0x00100001ba55ed50,0x0000000000002788,0x0000004001010002,0x0000000000001ce8\n"
".quad 0x0000000000000000,0x0000005600010007,0x0000000000000000,0x0000000000000011\n"
".quad 0x0000000000000000,0x0000000000000000,0x33010102464c457f,0x0000000000000007\n"
".quad 0x0000007900be0002,0x0000000000000000,0x0000000000001c40,0x0000000000001900\n"
".quad 0x0038004000560556,0x0001000d00400003,0x7472747368732e00,0x747274732e006261\n"
".quad 0x746d79732e006261,0x746d79732e006261,0x78646e68735f6261,0x7466752e766e2e00\n"
".quad 0x2e007972746e652e,0x006f666e692e766e,0x5a5f2e747865742e,0x6c5f6d6172643931\n"
".quad 0x6b5f79636e657461,0x694c496c656e7265,0x6a4b507645453031,0x6e2e005f32536a50\n"
".quad 0x5f2e6f666e692e76,0x5f6d61726439315a,0x5f79636e6574616c,0x4c496c656e72656b\n"
".quad 0x4b50764545303169,0x2e005f32536a506a,0x65726168732e766e,0x726439315a5f2e64\n"
".quad 0x6e6574616c5f6d61,0x656e72656b5f7963,0x45453031694c496c,0x32536a506a4b5076\n"
".quad 0x6f632e766e2e005f,0x2e30746e6174736e,0x6d61726439315a5f,0x79636e6574616c5f\n"
".quad 0x496c656e72656b5f,0x507645453031694c,0x005f32536a506a4b,0x5a5f2e747865742e\n"
".quad 0x5f6873756c663531,0x656e72656b5f326c,0x45383231694c496c,0x006950694b507645\n"
".quad 0x6f666e692e766e2e,0x756c6635315a5f2e,0x656b5f326c5f6873,0x31694c496c656e72\n"
".quad 0x694b507645453832,0x732e766e2e006950,0x5a5f2e6465726168,0x5f6873756c663531\n"
".quad 0x656e72656b5f326c,0x45383231694c496c,0x006950694b507645,0x736e6f632e766e2e\n"
".quad 0x5a5f2e30746e6174,0x5f6873756c663531,0x656e72656b5f326c,0x45383231694c496c\n"
".quad 0x006950694b507645,0x665f67756265642e,0x65722e00656d6172,0x5f67756265642e6c\n"
".quad 0x722e00656d617266,0x756265642e616c65,0x00656d6172665f67,0x7472747368732e00\n"
".quad 0x747274732e006261,0x746d79732e006261,0x746d79732e006261,0x78646e68735f6261\n"
".quad 0x7466752e766e2e00,0x2e007972746e652e,0x006f666e692e766e,0x6d61726439315a5f\n"
".quad 0x79636e6574616c5f,0x496c656e72656b5f,0x507645453031694c,0x005f32536a506a4b\n"
".quad 0x5a5f2e747865742e,0x6c5f6d6172643931,0x6b5f79636e657461,0x694c496c656e7265\n"
".quad 0x6a4b507645453031,0x6e2e005f32536a50,0x5f2e6f666e692e76,0x5f6d61726439315a\n"
".quad 0x5f79636e6574616c,0x4c496c656e72656b,0x4b50764545303169,0x2e005f32536a506a\n"
".quad 0x65726168732e766e,0x726439315a5f2e64,0x6e6574616c5f6d61,0x656e72656b5f7963\n"
".quad 0x45453031694c496c,0x32536a506a4b5076,0x6f632e766e2e005f,0x2e30746e6174736e\n"
".quad 0x6d61726439315a5f,0x79636e6574616c5f,0x496c656e72656b5f,0x507645453031694c\n"
".quad 0x005f32536a506a4b,0x5f006d617261705f,0x6873756c6635315a,0x6e72656b5f326c5f\n"
".quad 0x383231694c496c65,0x6950694b50764545,0x5f2e747865742e00,0x6873756c6635315a\n"
".quad 0x6e72656b5f326c5f,0x383231694c496c65,0x6950694b50764545,0x666e692e766e2e00\n"
".quad 0x6c6635315a5f2e6f,0x6b5f326c5f687375,0x694c496c656e7265,0x4b50764545383231\n"
".quad 0x2e766e2e00695069,0x5f2e646572616873,0x6873756c6635315a,0x6e72656b5f326c5f\n"
".quad 0x383231694c496c65,0x6950694b50764545,0x6e6f632e766e2e00,0x5f2e30746e617473\n"
".quad 0x6873756c6635315a,0x6e72656b5f326c5f,0x383231694c496c65,0x6950694b50764545\n"
".quad 0x5f67756265642e00,0x722e00656d617266,0x67756265642e6c65,0x2e00656d6172665f\n"
".quad 0x6265642e616c6572,0x656d6172665f6775,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x000b000300000068,0x0000000000000000\n"
".quad 0x0000000000000000,0x00090003000000fa,0x0000000000000000,0x0000000000000000\n"
".quad 0x000c000300000159,0x0000000000000000,0x0000000000000000,0x000a0003000001d9\n"
".quad 0x0000000000000000,0x0000000000000000,0x0004000300000209,0x0000000000000000\n"
".quad 0x0000000000000000,0x000b101200000040,0x0000000000000000,0x0000000000000400\n"
".quad 0x000c101200000137,0x0000000000000000,0x0000000000000a80,0x00000024ffffffff\n"
".quad 0xffffffff00000000,0x7c040003ffffffff,0x80810c0fffffffff,0x288081ff08002880\n"
".quad 0x0000002880808108,0x00000034ffffffff,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000040000000000,0x0000040400000000,0x810c000000200400,0x0000a00400288080\n"
".quad 0x0000000000000000,0x00000024ffffffff,0xffffffff00000000,0x7c040003ffffffff\n"
".quad 0x80810c0fffffffff,0x288081ff08002880,0x0000002880808108,0x00000034ffffffff\n"
".quad 0x0000007000000000,0x0000000000000000,0x00000a8000000000,0x0000040400000000\n"
".quad 0x810c000002640400,0x00000c0400288080,0x0000000000000000,0x0000000700082f04\n"
".quad 0x0008230400000028,0x0000000000000007,0x0000000700081204,0x0008110400000000\n"
".quad 0x0000000000000007,0x0000000600082f04,0x0008230400000010,0x0000000000000006\n"
".quad 0x0000000600081204,0x0008110400000000,0x0000000000000006,0x0000007900043704\n"
".quad 0x00080a0400003501,0x0018016000000002,0x000c170400181903,0x0010000200000000\n"
".quad 0x000c17040021f000,0x0008000100000000,0x000c17040021f000,0x0000000000000000\n"
".quad 0x00ff1b030021f000,0x000002d000081c04,0x000c050400000310,0x0000000100000020\n"
".quad 0x0004370400000001,0x0000350100000079,0x0000000400080a04,0x0010190300100160\n"
".quad 0x00000000000c1704,0x0021f00000080001,0x00000000000c1704,0x0021f00000000000\n"
".quad 0x00081c0400ff1b03,0x000009d000000990,0x00000000000000b4,0x0000000700000002\n"
".quad 0x0000000000000044,0x0000000600000002,0x0000000000000000,0x0000000000000000\n"
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
".quad 0x0000000000007918,0x000fc00000000000,0x00000a00ff017624,0x000fc400078e00ff\n"
".quad 0x0000000000257919,0x000e220000002100,0x0000460000047ab9,0x000fc60000000a00\n"
".quad 0x0000000000147919,0x000e620000002500,0xffffffe025197812,0x041fe400078ec0ff\n"
".quad 0x0000001f25157812,0x000fe400078ec0ff,0x0000001914147211,0x002fc800078038ff\n"
".quad 0x0000001f14067812,0x040fe400078ef825,0x000000ff19197211,0x000fe400000f0eff\n"
".quad 0x0000000114007812,0x100fe400078ef615,0x0000580006027a11,0x000fe400078210ff\n"
".quad 0x00000002140a7812,0x000fe400078ef615,0x0000580000047a11,0x000fc400078010ff\n"
".quad 0x0000590006037a11,0x000fe400008f1419,0x0000000314087812,0x100fe400078ef615\n"
".quad 0x000058000a067a11,0x000fe400078210ff,0x0000000414107812,0x000fe400078ef615\n"
".quad 0x0000590000057a11,0x100fe400000f1419,0x00005800080c7a11,0x000fe200078010ff\n"
".quad 0x0000000402007981,0x0000a2000c1ef900,0x000059000a077a11,0x000fc400008f1419\n"
".quad 0x00000005140a7812,0x100fe200078ef615,0x0000000404247981,0x0002a2000c1ef900\n"
".quad 0x00005800100e7a11,0x000fe400078210ff,0x0000000614127812,0x000fe200078ef615\n"
".quad 0x0000000406237981,0x0006a2000c1ef900,0x00005900080d7a11,0x100fe400000f1419\n"
".quad 0x000058000a087a11,0x000fe400078010ff,0x00005900100f7a11,0x000fe200008f1419\n"
".quad 0x000000040c227981,0x000962000c1ef900,0x0000000714167812,0x000fc400078ef615\n"
".quad 0x0000580012027a11,0x001fe200078210ff,0x000000040e217981,0x000162000c1ef900\n"
".quad 0x0000000814107812,0x000fe400078ef615,0x000059000a097a11,0x100fe400000f1419\n"
".quad 0x00005800160a7a11,0x000fe400078010ff,0x0000590012037a11,0x000fe200008f1419\n"
".quad 0x0000000408207981,0x000162000c1ef900,0x0000000914127812,0x000fc400078ef615\n"
".quad 0x0000580010047a11,0x002fe200078210ff,0x00000004021f7981,0x000362000c1ef900\n"
".quad 0x00005900160b7a11,0x000fe400000f1419,0x0000000a14167812,0x000fe400078ef615\n"
".quad 0x0000580012067a11,0x008fe200078010ff,0x000000040a1e7981,0x000762000c1ef900\n"
".quad 0x0000590010057a11,0x000fe400008f1419,0x0000000b14107812,0x000fc400078ef615\n"
".quad 0x00005800160c7a11,0x010fe200078210ff,0x00000004041d7981,0x000962000c1ef900\n"
".quad 0x0000590012077a11,0x000fe400000f1419,0x0000000c14127812,0x100fe400078ef615\n"
".quad 0x0000580010087a11,0x001fe200078010ff,0x00000004061c7981,0x000162000c1ef900\n"
".quad 0x0000000d140e7812,0x000fe400078ef615,0x00005900160d7a11,0x000fc400008f1419\n"
".quad 0x0000580012027a11,0x002fe400078210ff,0x0000590010097a11,0x000fe200000f1419\n"
".quad 0x000000040c1b7981,0x000362000c1ef900,0x0000000e14107812,0x100fe400078ef615\n"
".quad 0x000058000e0a7a11,0x008fe200078010ff,0x00000004081a7981,0x000762000c1ef900\n"
".quad 0x0000000f14187812,0x000fe400078ef615,0x0000590012037a11,0x000fc400008f1419\n"
".quad 0x0000580010047a11,0x010fe400078210ff,0x000059000e0b7a11,0x000fe200000f1419\n"
".quad 0x0000000402117981,0x000962000c1ef900,0x00000010140e7812,0x100fe400078ef615\n"
".quad 0x0000580018067a11,0x001fe400078010ff,0x0000001114127812,0x000fe400078ef615\n"
".quad 0x0000590010057a11,0x000fc400008f1419,0x000058000e167a11,0x000fe200078210ff\n"
".quad 0x000000040a107981,0x000162000c1ef900,0x0000590018077a11,0x000fe400000f1419\n"
".quad 0x00000012140c7812,0x102fe200078ef615,0x00000004040f7981,0x000362000c1ef900\n"
".quad 0x0000580012087a11,0x008fe400078010ff,0x0000001314187812,0x000fe400078ef615\n"
".quad 0x000059000e177a11,0x000fc400008f1419,0x000058000c027a11,0x010fe200078210ff\n"
".quad 0x00000004060e7981,0x000722000c1ef900,0x0000590012097a11,0x000fe400000f1419\n"
".quad 0x00000014140a7812,0x001fe200078ef615,0x00000004160d7981,0x000122000c1ef900\n"
".quad 0x0000580018127a11,0x000fe400078010ff,0x000059000c037a11,0x000fe400008f1419\n"
".quad 0x00000004080c7981,0x000122000c1ef900,0x000058000a047a11,0x002fc400078210ff\n"
".quad 0x0000590018137a11,0x000fe200000f1419,0x00000004020b7981,0x000322000c1ef900\n"
".quad 0x0000001614187812,0x140fe400078ef615,0x0000001514087812,0x001fe400078ef615\n"
".quad 0x000059000a057a11,0x000fe400008f1419,0x0000580008067a11,0x008fe200078010ff\n"
".quad 0x00000004120a7981,0x0000e2000c1ef900,0x0000580018167a11,0x000fc400078210ff\n"
".quad 0x0000590008077a11,0x100fe200000f1419,0x0000000404097981,0x0002e2000c1ef900\n"
".quad 0x0000590018177a11,0x000fc600008f1419,0x0000000406087981,0x0002e2000c1ef900\n"
".quad 0x0000001714127812,0x001fc800078ef615,0x0000580012027a11,0x002fe200078010ff\n"
".quad 0x0000000416077981,0x0000e2000c1ef900,0x0000001914187812,0x000fe400078ef615\n"
".quad 0x0000590012037a11,0x000fe400000f1419,0x0000001814167812,0x001fc600078ef615\n"
".quad 0x0000000402067981,0x0000e2000c1ef900,0x0000580018127a11,0x000fe400078210ff\n"
".quad 0x0000580016047a11,0x000fe400078010ff,0x0000590018137a11,0x100fe400008f1419\n"
".quad 0x0000590016057a11,0x000fe400000f1419,0x0000001b14187812,0x000fc800078ef615\n"
".quad 0x0000000404057981,0x0002e2000c1ef900,0x0000580018167a11,0x000fc600078210ff\n"
".quad 0x0000000412047981,0x0022e2000c1ef900,0x0000590018177a11,0x000fe400008f1419\n"
".quad 0x0000001a14127812,0x002fc800078ef615,0x0000580012027a11,0x001fe400078010ff\n"
".quad 0x0000001c14187812,0x000fe400078ef615,0x0000590012037a11,0x000fe400000f1419\n"
".quad 0x0000580018127a11,0x000fc800078010ff,0x0000000402037981,0x0000e2000c1ef900\n"
".quad 0x0000590018137a11,0x000fe400000f1419,0x0000001e14187812,0x040fe400078ef615\n"
".quad 0x0000001f14257812,0x040fe400078ef425,0x0000000412137981,0x000ee8000c1ef900\n"
".quad 0x0000000416027981,0x0010e4000c1ef900,0x0000001d14167812,0x001fc800078ef615\n"
".quad 0x0000580016147a11,0x000fc800078010ff,0x0000590016157a11,0x000fe400000f1419\n"
".quad 0x0000580018167a11,0x000fc600078010ff,0x0000000414147981,0x000ee2000c1ef900\n"
".quad 0x0000590018177a11,0x000fe400000f1419,0x0000580025187a11,0x000fc800078010ff\n"
".quad 0x0000000416177981,0x000ee2000c1ef900,0x0000590025197a11,0x000fca00000f1419\n"
".quad 0x0000000418187981,0x000ee2000c1ef900,0x0000002423007210,0x004fc80007ffe000\n"
".quad 0x0000002221007210,0x020fc80007ffe000,0x000000201f007210,0x000fc80007ffe000\n"
".quad 0x0000001e1d007210,0x000fc80007ffe000,0x0000001c1b007210,0x000fc80007ffe000\n"
".quad 0x0000001a11007210,0x000fc80007ffe000,0x000000100f007210,0x000fc80007ffe000\n"
".quad 0x0000000e0d007210,0x010fc80007ffe000,0x0000000c0b007210,0x000fc80007ffe000\n"
".quad 0x0000000a09007210,0x008fc80007ffe000,0x0000000807007210,0x000fc80007ffe000\n"
".quad 0x0000000605007210,0x000fc80007ffe000,0x0000000403007210,0x000fc80007ffe000\n"
".quad 0x0000000213007210,0x000fc80007ffe000,0x0000001417177210,0x000fca0007ffe000\n"
".quad 0x0000000117177824,0x000fca00078e0218,0x000000ff1700720c,0x000fda0003f05270\n"
".quad 0x000000000000894d,0x000fea0003800000,0x00005a00ff027624,0x000fe400078e00ff\n"
".quad 0x00005b00ff037624,0x000fca00078e00ff,0x0000001702007986,0x000fe2000c101904\n"
".quad 0x000000000000794d,0x000fea0003800000,0xfffffff000007947,0x000fc0000383ffff\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000007918,0x000fc00000000000\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000007918,0x000fc00000000000\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000007918,0x000fc00000000000\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000007918,0x000fc00000000000\n"
".quad 0x0000000000007918,0x000fc00000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000300000001,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000040,0x00000000000001e8,0x0000000000000000\n"
".quad 0x0000000000000001,0x0000000000000000,0x000000030000000b,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000228,0x0000000000000239,0x0000000000000000\n"
".quad 0x0000000000000001,0x0000000000000000,0x0000000200000013,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000468,0x00000000000000c0,0x0000000600000002\n"
".quad 0x0000000000000008,0x0000000000000018,0x00000001000001b8,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000528,0x00000000000000e0,0x0000000000000000\n"
".quad 0x0000000000000001,0x0000000000000000,0x7000000000000037,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000608,0x0000000000000060,0x0000000000000005\n"
".quad 0x0000000000000004,0x0000000000000000,0x700000000000006e,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000668,0x000000000000006c,0x0000000b00000005\n"
".quad 0x0000000000000004,0x0000000000000000,0x7000000000000130,0x0000000000000000\n"
".quad 0x0000000000000000,0x00000000000006d4,0x000000000000004c,0x0000000c00000005\n"
".quad 0x0000000000000004,0x0000000000000000,0x00000009000001c5,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000720,0x0000000000000020,0x0000000400000005\n"
".quad 0x0000000000000008,0x0000000000000010,0x00000001000000d2,0x0000000000000002\n"
".quad 0x0000000000000000,0x0000000000000740,0x0000000000000178,0x0000000b00000000\n"
".quad 0x0000000000000004,0x0000000000000000,0x0000000100000188,0x0000000000000002\n"
".quad 0x0000000000000000,0x00000000000008b8,0x0000000000000170,0x0000000c00000000\n"
".quad 0x0000000000000004,0x0000000000000000,0x0000000100000040,0x0000000000100006\n"
".quad 0x0000000000000000,0x0000000000000a80,0x0000000000000400,0x1000000600000005\n"
".quad 0x0000000000000080,0x0000000000000000,0x0000000100000108,0x0000000000000006\n"
".quad 0x0000000000000000,0x0000000000000e80,0x0000000000000a80,0x2800000700000005\n"
".quad 0x0000000000000080,0x0000000000000000,0x0000000500000006,0x0000000000001c40\n"
".quad 0x0000000000000000,0x0000000000000000,0x00000000000000a8,0x00000000000000a8\n"
".quad 0x0000000000000008,0x0000000500000001,0x0000000000000740,0x0000000000000000\n"
".quad 0x0000000000000000,0x00000000000011c0,0x00000000000011c0,0x0000000000000008\n"
".quad 0x0000000500000001,0x0000000000001c40,0x0000000000000000,0x0000000000000000\n"
".quad 0x00000000000000a8,0x00000000000000a8,0x0000000000000008,0x0000004801010001\n"
".quad 0x0000000000000a18,0x0000004000000a11,0x0000005600080001,0x0000000000000000\n"
".quad 0x0000000000002011,0x0000000000000000,0x0000000000002435,0x0000000000000000\n"
".quad 0x762e1cf200010a13,0x38206e6f69737265,0x677261742e0a312e,0x36385f6d73207465\n"
".quad 0x7365726464612e0a,0x3620657a69735f73,0x6973692dff002f34,0x746e652e20656c62\n"
".quad 0x6635315a5f207972,0x5f326c5f6873756c,0x4c496c656e72656b,0x5076454538323169\n"
".quad 0x702e0a286950694b,0x36752e206d617261,0x002d5f110f002f34,0xf32200372c305f3f\n"
".quad 0x2e0a7b0a290a3108,0x6572702e20676572,0x3b3e323c70252064,0x2520323362970012\n"
".quad 0x02f2001330313c72,0x313c647225203436,0x6c0a0a0a3b3e3533,0x0019752e22007764\n"
".quad 0x00b55b202c34335f,0x311f00413b5d2d16,0x0a3b5d3191180040,0xf300a8752e766f6d\n"
".quad 0x697425202c363600,0x646e610a3b782e64,0x001c2c37363300be,0x3814001932332d39\n"
".quad 0x7200473133290019,0x4961746325202c39,0x3300306c68733300,0x3b3760001e2c3037\n"
".quad 0x330300b17476630a,0x00222c3533644100,0x2e34367353001902,0x8300353611001973\n"
".quad 0x732e6464610a3b37,0x0035030093010124,0x9b02004f3633643e,0x72726f0a3b385400\n"
".quad 0x13003c2c39333801,0x3434001d02009b38,0x006b321900242c30,0x00260101952c3224\n"
".quad 0x30202c349200e808,0x0001d97b090a0a3b,0x01916c61763100b1,0x2e6c61626f6c67b2\n"
".quad 0x2c300016622e6763,0x005c5d13004d5b20,0x25c4001a01004004,0x090a0a0a7d3b3472\n"
".quad 0x2c3123012b726f78,0x341100dc311d0161,0x2800dc313728001c,0xdc31342a00dc3234\n"
".quad 0xdc0a00242c332400,0xcc331f00dc331900,0x141600cc331f1b00,0x0100cc321e00cc32\n"
".quad 0x1900cc323729007c,0x2400cc341a00cc35,0x1900cc0a00242c36,0x1b00cc361f00cc34\n"
".quad 0xcc33141600cc341f,0x00b10100cc331e00,0xcc381900cc333729,0x2c392400cc371a00\n"
".quad 0xcc351900cc0a0024,0x351f1b00cc391f00,0x1d00cc34141600cc,0x28030f351100cc34\n"
".quad 0xcc31352800cc3437,0x353400cc30352900,0x1800cc0a00242c32,0x00cc32352f00cc36\n"
".quad 0x35141600cc361f1b,0xb40100cc351e00cc,0x341900cc35372901,0x352400cc331a00cc\n"
".quad 0x371900cc0a00242c,0x1f1b00cc351f00cc,0x00cc36141600cc37,0x29001c351104d80e\n"
".quad 0x00cc371900cc3637,0x242c382400cc361a,0x00cc381900cc0a00,0xcc381f1b00cc381f\n"
".quad 0xf30e00cc37141600,0x37372802ff351105,0x1900cc30362900cc,0x242c31363400cc39\n"
".quad 0x00cc391800cc0a00,0x391f1b00cc31362f,0x1d00cc38141600cc,0x1902ff361100cc38\n"
".quad 0x00cc333628067037,0x00ad0300cc32362a,0xcd30312900cc331c,0x312f1b00cd341f00\n"
".quad 0x00ce39141600ce30,0x2903010100ce391e,0x00ce361900ce3937,0x1d00160300ce351a\n"
".quad 0x1f00ce311900ce36,0x00ce311f1c00ce37,0x312e00ce30382415,0x382901b90100cf30\n"
".quad 0x0a00cf391900cf30,0x36642d08a902080d,0x2f00cf323128080d,0x07ff0f1c00cf3037\n"
".quad 0x000e00cf31382516,0x08003819081c0208,0x31372a00cf323728,0x0b00242c332400cf\n"
".quad 0x010f00cf331900cf,0x25160802311f1c08,0x0208030e00cf3238,0x3729080338190687\n"
".quad 0x200208030a00cf35,0x1900cf0b00240105,0x1f1c08040f00cf34,0xcf33382516080531\n"
".quad 0x1904f20208060e00,0x00cf383729080638,0x240103890208060a,0x00cf351900cf0b00\n"
".quad 0x0808311f1c08070f,0x090e00cf34382516,0x0809381903590208,0x30382900cf313828\n"
".quad 0x00240101ec0200cf,0x2f00cf361800cf0b,0x080b0f1c00cf3238,0x0c0e00cf35382516\n"
".quad 0x080c381901bb0208,0x080c0a00cf343829,0xcf0b002401004e02,0x080d0f00cf371900\n"
".quad 0x382516080e311f1c,0x1d02080f0e00cf36,0x373829080f381900,0x383834080f0a00cf\n"
".quad 0x381900cf0b00242c,0x311f1c08100f00cf,0x00cf373825160811,0x19030b381108120e\n"
".quad 0x00cf303929081238,0x242c31393408120a,0x00cf391800cf0b00,0x14311f1c0813391f\n"
".quad 0x0e00cf3838251608,0x3829030b39110815,0x1a00cf331800cf38,0x1d00af3913081539\n"
".quad 0x0f00cf30190e8533,0x160815321f1c0815,0x08160e00cf393825,0xcf393829030b3911\n"
".quad 0x08160a00cf361900,0x00cf361d00163913,0x1c08160f00cf3119,0x303924160816321f\n"
".quad 0x39110816321e00cf,0x39290816391901bb,0x314408160a00cf39,0x00d00b00252c3030\n"
".quad 0x1630312f00d03218,0x39251608180f1d10,0x312108180e00d131,0x00d2313928001e30\n"
".quad 0x312a00d332303138,0x2c33303145081b30,0xd5331a00d50b0027,0x1e321f1c081e0f00\n"
".quad 0x0e00d53239251608,0x2a0080303121081e,0x00d5351a00d53239,0x2c3630314508210a\n"
".quad 0xd5341a00d50b0027,0x24321f1c08240f00,0x0e00d53339251608,0x1900b93031210824\n"
".quad 0xd53830313a082539,0x3930314508270a00,0x351a00d50b00272c,0x321f1c082a0f00d5\n"
".quad 0x00d534392516082a,0x290cba3112082a0e,0xd531312900d53439,0x510300d530312a00\n"
".quad 0x1900d50b0027010b,0x00d532312f00d536,0x3539251608300f1c,0x23311208300e00d5\n"
".quad 0x341a00d535392a0b,0xb9311308330a00d5,0x1a00d50b00270109,0x1f1c08360f00d537\n"
".quad 0xd536392516083632,0x098b311208360e00,0x3731313a08373919,0x21311308390a00d5\n"
".quad 0x1a00d50b00270108,0x1f1c083c0f00d538,0xd537392516083c32,0x07f33112083c0e00\n"
".quad 0x30322a00d5373929,0x893113083f0a00d5,0x3229084132312d06,0x00d531322f00d539\n"
".quad 0x3839251608420f1c,0x5a311208420e00d5,0x331900d538392a06,0x0400d532322b00d5\n"
".quad 0x332a00d5331c00b4,0x1f1c08480f00d530,0xd539392516084833,0x04b0311208480e00\n"
".quad 0x3632313a08493919,0x3a3113084b0a00d5,0x332a084d32312d03,0x1f1c084e0f00d531\n"
".quad 0x0108000316084e33,0x073112084f0e15fd,0x1a00d70807fd0103,0x920308530b00d739\n"
".quad 0x3329085432312d01,0x00d730332f00d732,0x31151700d7321f1c,0x5f020008550f00d7\n"
".quad 0x2900d70708380101,0xd731332b00d73233,0xd70b00272c332500,0x08560f00d7331a00\n"
".quad 0x73720c0856331f1c,0x001f71652e707465,0x02f019a62c317035,0x6172622031702540\n"
".quad 0x3042425f5f4c2420,0x617476637406505f,0x1b4004006d6f742e,0x74730a3b45009d04\n"
".quad 0x1d5b20323342001c,0x0a3b3500565d1100,0x65720a3a9f004b0a,0x021cad7d0a0a3b74\n"
".quad 0x616c771b6a643920,0x111b8d79636e6574,0x536a506a6d1b8c30,0x1100350f1cb35f32\n"
".quad 0x1f1f003d0f1cb90e,0x290a32d029003d31,0x69746e78616d2e0a,0x2c3105ff01ec2064\n"
".quad 0x6e6e696d2e0a3120,0x6d73726570617463,0x1d371d101d1e3120,0x00021d1c39322f1d\n"
".quad 0x0f1c011e5b1f078e,0x1f1e00460f011d22,0x0047341f01004631,0x31261c405d32281e\n"
".quad 0x2e6c756d831d6f34,0xfd03001b65646977,0x1c8f341f00220011,0x0840641208960200\n"
".quad 0x6f31722536032e0d,0x1003d3090a0a3c1c,0x001c0a311f003d36,0x62990b1501005d03\n"
".quad 0x20636e79732e7261,0x6c63510022001cf3,0x007c0f00596b636f,0x007c0f1c1f331602\n"
".quad 0x1bba331f04310100,0x00d20f00202c1201,0x00560f1ba9341604,0x0056070393381300\n"
".quad 0x38312f005c2c3526,0x0f1b333516040056,0x351f05bb01000056,0x312f005c02001ace\n"
".quad 0x1abd361604005639,0x361f08920200560e,0x322f005c02001a58,0x1a47371604005630\n"
".quad 0x0a04eb010000560f,0x2f005c2c38261f25,0xd138160400563132,0x0211010000560f19\n"
".quad 0x005c0200196c381f,0x391604005632322f,0xeb010000560f195b,0x18f6030056391901\n"
".quad 0x005733322f005d02,0x312f005830312204,0x2f01ee0103005930,0x0061030118823031\n"
".quad 0x330305005b34322f,0x0103005b31312f03,0x01180e31312f01f3,0x005b35322f006203\n"
".quad 0x03360117ff321705,0x5d33312903035c0f,0x0306e66275733303,0x32723f001f00040c\n"
".quad 0x2f0940030406b63b,0x001d04010c713431,0x3732210106d3351f,0x073f00001d0106d2\n"
".quad 0x32312f073f656e28,0x080740311f010740,0x1100dc31190c1003,0x1200007d0f004636\n"
".quad 0x1507503615007d38, 0x0a0a7d0a50075031, 0x0000000000000000\n"
".text\n");
#ifdef __cplusplus
extern "C" {
#endif
extern const unsigned long long fatbinData[1267];
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
