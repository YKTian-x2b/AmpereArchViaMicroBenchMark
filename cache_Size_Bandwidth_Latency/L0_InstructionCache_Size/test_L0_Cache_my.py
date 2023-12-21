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
    cuasm2cubin(projectPath + 'cache_Size_Throughput_Latency/L0_Cache_Size/L0CacheSizeTest.sm_86.cuasm')
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
        res = subprocess.check_output(projectPath + 'cache_Size_Throughput_Latency/L0_Cache_Size/L0CacheSizeTest')
        return res
    except subprocess.CalledProcessError as e:
        print(f'Error happened when running exe (return code={e.returncode})!')
        exit(e.returncode)

#
def test_L0CacheSize(n_FFMA_seqs):
    cat = CuAsmTemplate(projectPath + 'cache_Size_Throughput_Latency/L0_Cache_Size/save/L0CacheSizeTest.template.sm_86.cuasm')

    # FFMA指令要执行两次，以进行预热。选择操作数寄存器，避免相邻指令的寄存器依赖。
    s_work1  = f'      [B------:R-:W-:Y:S04]    FFMA R9, R9, R2, c[0x0][0x164] ;\n' # R9 += 1
    s_work1 = s_work1 * n_FFMA_seqs

    cat.setMarker('WORK_1', s_work1)

    cat.generate(projectPath + 'cache_Size_Throughput_Latency/L0_Cache_Size/L0CacheSizeTest.sm_86.cuasm')

    build()

    res = run_exe()
    return parseResult(res.decode())


def doTest_L0CacheSize():
    with open(projectPath + 'cache_Size_Throughput_Latency/L0_Cache_Size/save/res_L0CacheSize.txt', 'w') as fout:
        fout.write(f'{"avgCycles":24s}    {"n_FFMA_seqs":8s}    {"avgCPI":12s}'+'\n')
        # num_FFMA_seqs_list = [128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 65536*2, 65536*4, 65536*8]
        # n_FFMA_seqs = 256
        # while (n_FFMA_seqs <= 16384):
        #     avgCycles = test_L0CacheSize(n_FFMA_seqs)
        #     s = f'{avgCycles:24.4f}    {n_FFMA_seqs:08d}    {avgCycles/(n_FFMA_seqs+12):12.4f}'
        #     print(s)
        #     fout.write(s+'\n')
        #     if(n_FFMA_seqs < 256):
        #         n_FFMA_seqs += 16
        #     elif(n_FFMA_seqs < 2048):
        #         n_FFMA_seqs += 64
        #     elif(n_FFMA_seqs < 8192*2):     
        #         n_FFMA_seqs += 1024
        #     elif(n_FFMA_seqs < 65536*2):    
        #         n_FFMA_seqs += 8192
        #     else:
        #         n_FFMA_seqs += 16384
        n_FFMA_seqs = 16
        while (n_FFMA_seqs <= 2048):
            avgCycles = test_L0CacheSize(n_FFMA_seqs)
            s = f'{avgCycles:24.4f}    {n_FFMA_seqs:08d}    {avgCycles/(n_FFMA_seqs+12):12.4f}'
            print(s)
            fout.write(s+'\n')
            n_FFMA_seqs += 16


if __name__ == '__main__':
    os.system('nvidia-smi -ac 7000,1702')
    
    doTest_L0CacheSize()