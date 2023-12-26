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
    cuasm2cubin(projectPath + 'warpSchedule/midRes/warpScheduleTest_my.sm_86.cuasm')
    if not use_driver_api:
        print("not using driver api, so exit(0)")
        exit(0)

def parseResult(res:str, n_FFMA_seqs):
    new_res = ''
    for line in res.splitlines():
        r = re.search('elapsed: (.*)clks', line)
        if r is not None:
            clks = float(r.groups()[0])
            line += f',    CPI: {clks/n_FFMA_seqs:.2f}'
        new_res += line + '\n'
    print(new_res)
    return new_res

def run_exe():
    try:
        res = subprocess.check_output(projectPath + 'warpSchedule/res/warpScheduleTest_my')
        return res
    except subprocess.CalledProcessError as e:
        print(f'Error happened when running exe (return code={e.returncode})!')
        exit(e.returncode)


def test_warpSchedule(n_FFMA_seqs):
    cat = CuAsmTemplate(projectPath + 'warpSchedule/res/warpScheduleTest_my.template.sm_86.cuasm')

    s_init = '      [B------:R-:W-:-:S01]  MOV R15, RZ ; \n'
    for r in range(16,20):
        s_init += f'      [B------:R-:W-:-:S01]  MOV R{r:d}, 0x3f800000 ; \n'

    s_work1 = ''
    for i in range(4):
        s_work1 += f'      [B------:R-:W-:Y:S04]    FFMA R15, R{i+16}, 1, R15;\n'
    s_work1 = s_work1 * (int(n_FFMA_seqs/4))

    cat.setMarker('INIT', s_init)
    cat.setMarker('WORK_1', s_work1)

    s_regnum = f'  	.sectioninfo	@"SHI_REGISTERS={32}"'
    cat.setMarker('REGNUM', s_regnum)

    cat.generate(projectPath + 'warpSchedule/midRes/warpScheduleTest_my.sm_86.cuasm')

    build()

    res = run_exe()
    return parseResult(res.decode(), n_FFMA_seqs)


def doTest_warpSchedule():
    n_FFMA_seqs = 4096
    with open(projectPath + 'warpSchedule/res/res_warpScheduleTest_my.txt', 'w') as fout:
        res = test_warpSchedule(n_FFMA_seqs)
        fout.write(res + '\n')


if __name__ == '__main__':
    #
    os.system('nvidia-smi -ac 7000,1702')
    
    doTest_warpSchedule()