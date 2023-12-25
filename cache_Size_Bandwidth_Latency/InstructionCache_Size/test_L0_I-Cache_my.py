import os
import re
import sys
import subprocess
import math

projectPath = '/home/yujixuan/kaiPro/GitHubLocal/AmpereArchViaMicroBenchmark/AmpereArchViaMicroBenchMark/'
sys.path.append(projectPath + 'Utils')

from test_Common import CuAsmTemplate
from test_Common import cubin2cuasm
from test_Common import cuasm2cubin

def build(use_driver_api=True):
    cuasm2cubin(projectPath + 'cache_Size_Bandwidth_Latency/InstructionCache_Size/midRes_my/L0_I-CacheSizeTest_my.sm_86.cuasm')
    if not use_driver_api:
        print("not using driver api, so exit(0)")
        exit(0)


def parseResult(res:str):
    print(res)
    for line in res.splitlines():
        r = re.search('avg Cycles: (.*)', line)
        if r is not None:
            avgCycles = float(r.groups()[0])
            break
    return avgCycles


def run_exe():
    try:
        res = subprocess.check_output(projectPath + 'cache_Size_Bandwidth_Latency/InstructionCache_Size/res/L0_I-CacheSizeTest_my')
        return res
    except subprocess.CalledProcessError as e:
        print(f'Error happened when running exe (return code={e.returncode})!')
        exit(e.returncode)

#
def test_L0CacheSize(n_FFMA_seqs):
    cat = CuAsmTemplate(projectPath + 'cache_Size_Bandwidth_Latency/InstructionCache_Size/res/L0_I-CacheSizeTest_my.template.sm_86.cuasm')

    # FFMA指令要执行两次，以进行预热。选择操作数寄存器，避免相邻指令的寄存器依赖。
    s_init = '      [B------:R-:W-:-:S01]  MOV R14, RZ ; \n'
    s_init += '      [B------:R-:W-:-:S01]  MOV R15, RZ ; \n'
    for r in range(16,20):
        s_init += f'      [B------:R-:W-:-:S01]  MOV R{r:d}, 0x3f800000 ; \n'

    s_work1 = ''
    for i in range(4):
        s_work1 += f'      [B------:R-:W-:-:S01]    FFMA R{i+16}, R14.reuse, 1, R{i+16} ;\n'
    s_work1 = s_work1 * (n_FFMA_seqs-1)
    for i in range(3):
        s_work1 += f'      [B------:R-:W-:-:S01]    FFMA R{i+16}, R14.reuse, 1, R{i+16} ;\n'
    s_work1 += f'      [B------:R-:W-:-:S01]    FFMA R19, R14, 1, R19 ;\n'

    s_work2 = s_work1

    cat.setMarker('INIT', s_init)
    cat.setMarker('WORK_1', s_work1)
    cat.setMarker('WORK_2', s_work2)


    s_regnum = f'  	.sectioninfo	@"SHI_REGISTERS={32}"'
    cat.setMarker('REGNUM', s_regnum)

    cat.generate(projectPath + 'cache_Size_Bandwidth_Latency/InstructionCache_Size/midRes_my/L0_I-CacheSizeTest_my.sm_86.cuasm')

    build()

    res = run_exe()
    return parseResult(res.decode())


def doTest_L0CacheSize():
    with open(projectPath + 'cache_Size_Bandwidth_Latency/InstructionCache_Size/res/res_L0_I-CacheSize_my.txt', 'w') as fout:
        fout.write(f'{"avgCycles":16s}    {"n_FFMA_seqs":8s}    {"avgCPI":12s}    {"seqSize_IN_KB":6s}'+'\n')
        # L0/L1 detect
        n_FFMA_seqs = 256
        while (n_FFMA_seqs < 1536):
            avgCycles = test_L0CacheSize(n_FFMA_seqs)
            s = f'{avgCycles:16.4f}    {n_FFMA_seqs:08d}    {(avgCycles/n_FFMA_seqs):12.4f}    {(n_FFMA_seqs/32):6.2f}'
            print(s)
            fout.write(s+'\n')
            n_FFMA_seqs += 8
            
        while(n_FFMA_seqs < 8192):
            avgCycles = test_L0CacheSize(n_FFMA_seqs)
            s = f'{avgCycles:16.4f}    {n_FFMA_seqs:08d}    {(avgCycles/n_FFMA_seqs):12.4f}    {(int)(n_FFMA_seqs/32):04d}'
            print(s)
            fout.write(s+'\n')
            n_FFMA_seqs += 512
            
        # # L2 detect 上限应该差不多是65536*4。但实际做出来的结果和Unified L2 cache有很大偏差
        # # 感觉 L2_I-Cache 基本不会出现溢出的情况，所以放弃研究了。只得到L0和L1的大小 目前来说足够了
        # n_FFMA_seqs = 8192
        # while(n_FFMA_seqs < 65536*4):
        #     avgCycles = test_L0CacheSize(n_FFMA_seqs)
        #     s = f'{avgCycles:16.4f}    {n_FFMA_seqs:08d}    {(avgCycles/n_FFMA_seqs):12.4f}    {(int)(n_FFMA_seqs/32):04d}'
        #     print(s)
        #     fout.write(s+'\n')
        #     n_FFMA_seqs += 8192


if __name__ == '__main__':
    #
    os.system('nvidia-smi -ac 7000,1702')
    
    doTest_L0CacheSize()