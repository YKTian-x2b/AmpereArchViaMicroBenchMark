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

# 结论是 Ampere的寄存器是两个bank

def build(use_driver_api=True):
    cuasm2cubin(projectPath + 'regBank/midRes/regBankTest_2Bank.sm_86.cuasm')
    if not use_driver_api:
        print("not using driver api, so exit(0)")
        exit(0)


def parseResult(res:str):
    print(res)
    res = res.splitlines()[2]
    return res


def run_exe():
    try:
        res = subprocess.check_output(projectPath + 'regBank/res/regBankTest_2Bank')
        return res
    except subprocess.CalledProcessError as e:
        print(f'Error happened when running exe (return code={e.returncode})!')
        exit(e.returncode)


# for ampere this is no BankConflict
def test_BankConflict(seq_num, regIdx, regnum, FFMA_seqs):
    cat = CuAsmTemplate(projectPath + 'regBank/res/regBankTest_2Bank.template.sm_86.cuasm')
    
    s_init  = '[B------:R-:W-:-:S01]  MOV R6, RZ ; \n'
    for r in range(7,17):
        s_init += f'[B------:R-:W-:-:S01]  MOV R{r:d}, 0x3f800000 ; \n'

    s_work1  = f'      [B------:R-:W-:Y:S04]  FFMA R6, R{seq_num:d}, R9, R{regIdx:d}; \n'
    s_work1 = s_work1 * FFMA_seqs

    cat.setMarker('INIT', s_init)
    cat.setMarker('WORK_1', s_work1)

    s_regnum = f'  	.sectioninfo	@"SHI_REGISTERS={regnum}"'
    cat.setMarker('REGNUM', s_regnum)

    cat.generate(projectPath + 'regBank/midRes/regBankTest_2Bank.sm_86.cuasm')

    build()

    res = run_exe()
    return parseResult(res.decode())


def doTest_BankConflict():
    with open('res/res_2Bank.txt', 'w') as fout:
        regnum = 32
        FFMA_seqs = 4096
        for seq_num in [7, 8]:
            fout.write(f'\n================= {seq_num:1d},9,X =================\n')
            for regIdx in range(10,17):
                fout.write(f'FFMA R6, R{seq_num:d}, R9, R{regIdx:02d};\n')
                res = test_BankConflict(seq_num, regIdx, regnum, FFMA_seqs)
                fout.write(res+'\n')
        
        


if __name__ == '__main__':
    #
    os.system('nvidia-smi -ac 7000,1702')
    
    doTest_BankConflict()
