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
    cuasm2cubin(projectPath + 'warpSchedule/midRes2/warpScheduleTest_my.sm_86.cuasm')
    if not use_driver_api:
        print("not using driver api, so exit(0)")
        exit(0)


def run_exe():
    try:
        res = subprocess.check_output(projectPath + 'warpSchedule/res/warpScheduleTest_my')
        return res
    except subprocess.CalledProcessError as e:
        print(f'Error happened when running exe (return code={e.returncode})!')
        exit(e.returncode)

#
def test_warpSchedule(n_FFMA_seqs):
    cat = CuAsmTemplate(projectPath + 'warpSchedule/res/warpScheduleTest_my.template.sm_86.cuasm')

    s_init = '      [B------:R-:W-:-:S01]  MOV R14, RZ ; \n'
    s_init += '      [B------:R-:W-:-:S01]  MOV R15, RZ ; \n'
    for r in range(16,20):
        s_init += f'      [B------:R-:W-:-:S01]  MOV R{r:d}, 0x3f800000 ; \n'

    s_work1 = ''
    for i in range(4):
        s_work1 += f'      [B------:R-:W-:Y:S04]    FFMA R{i+16}, R14.reuse, 1, R{i+16} ;\n'
    s_work1 = s_work1 * (n_FFMA_seqs-1)
    for i in range(3):
        s_work1 += f'      [B------:R-:W-:Y:S04]    FFMA R{i+16}, R14.reuse, 1, R{i+16} ;\n'
    s_work1 += f'      [B------:R-:W-:Y:S04]    FFMA R19, R14, 1, R19 ;\n'

    cat.setMarker('INIT', s_init)
    cat.setMarker('WORK_1', s_work1)

    s_regnum = f'  	.sectioninfo	@"SHI_REGISTERS={32}"'
    cat.setMarker('REGNUM', s_regnum)

    cat.generate(projectPath + 'warpSchedule/midRes2/warpScheduleTest_my.sm_86.cuasm')

    build()

    res = run_exe()
    return res.decode()


def doTest_warpSchedule():
    n_FFMA_seqs = 4096
    with open(projectPath + 'warpSchedule/res/res_warpScheduleTest_my.txt', 'a') as fout:
        res = test_warpSchedule(n_FFMA_seqs)
        print(res)
        fout.write(res + '\n')


if __name__ == '__main__':
    # 虽然在这台设备上没用 但还是写了
    os.system('nvidia-smi -ac 7001,1702')
    
    doTest_warpSchedule()