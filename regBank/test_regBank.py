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

# baseline result for:
# -  grid=1800, block=128, NIter=256, 192 instruction per iteration
# -  No bank conflict
# -  MemFreq = 7200 MHz, SMFreq = 1702 MHz
# 30*128*1702 = 6535.68 G 指令/s
# (4*64+4)*1800*128*256 = 15.335424G 条指令
BASELINE = 2.3461

def build(use_driver_api=True):
    cuasm2cubin(projectPath + 'regBank/midRes/regBankTest.sm_86.cuasm')
    if not use_driver_api:
        print("not using driver api, so exit(0)")
        exit(0)


def parseResult(res:str):
    nt = 0      
    tsum = 0.0
    tsq = 0.0
    tres = ''
    tlist = []

    for line in res.splitlines():
        r = re.search('Test(.*):(.*)ms', line)
        if r is not None:
            t = float(r.groups()[1])
            tlist.append(t)

            nt += 1
            tsum += t
            tsq += t*t
        
        r2 = re.search(r'res\[\s*0\]\s*:(.*)', line)
        if r2 is not None:
            tres = r2.groups()[0].strip()

    # assert(nt==5)
    
    tavg = tsum/nt
    tstd = math.sqrt(tsq/nt - tavg*tavg)

    # teq = tavg * 6 / 16.74 # ratio to base line per instruction
    sfull = '[' + (', '.join(['%8.3f'%t for t in tlist])) + ']'
    return tavg, tstd, tres, sfull


def run_exe():
    try:
        res = subprocess.check_output(projectPath + 'regBank/res/regBankTest')
        return res
    except subprocess.CalledProcessError as e:
        print(f'Error happened when running exe (return code={e.returncode})!')
        exit(e.returncode)


def test_NoBankConflict(stall1, stall2, yflag, regnum):
    cat = CuAsmTemplate(projectPath + 'regBank/res/regBankTest.template.sm_86.cuasm')
    
    s_init  = '[B------:R-:W-:-:S01]  MOV R5, RZ ; \n'
    for r in range(8,14):
        s_init += f'[B------:R-:W-:-:S01]  MOV R{r:d}, 0x3f800000 ; \n'

    s_work1  = f'      [B------:R-:W-:{yflag}:S{stall1:02d}]  FFMA R5, R8, R9, R5; \n' # R5 += 1
    for i in range(3):
        s_work1 += f'      [B------:R-:W-:{yflag}:S{stall2:02d}]  FFMA R{i+11}, R8, R9, R10; \n'
    s_work1 = s_work1 * 64

    # s_work2 = s_work1

    cat.setMarker('INIT', s_init)
    cat.setMarker('WORK_1', s_work1)
    # cat.setMarker('WORK_2', s_work2)

    s_regnum = f'  	.sectioninfo	@"SHI_REGISTERS={regnum}"'
    cat.setMarker('REGNUM', s_regnum)

    cat.generate(projectPath + 'regBank/midRes/regBankTest.sm_86.cuasm')

    build()

    res = run_exe()
    return parseResult(res.decode())

# 没有BankConflict和Reuse的Baseline
def doTest_NoBankConflict():
    with open('res/res_NoBankConflict_Baseline.txt', 'w') as fout:
        regnum = 32
        s = f'{"":8s} {"TAvg":>8s} ({"TRatio":>8s}) {"TStd":>8s}    {"Results":s}'
        fout.write(s+'\n')
        for stall in range(1,16):
            for yflag in ['-', 'Y']:
                tavg, tstd, tres, sfull = test_NoBankConflict(stall, stall, yflag, regnum)
                tratio = tavg * 4 / BASELINE
                s = f'[{yflag}:S{stall:02d}]: {tavg:8.3f} ({tratio:8.4f}), {tstd:8.3f},  {tres:s}  {sfull}'
                print(s)
                fout.write(s+'\n')
        
        s = '\n######### S## + 3*S01 ############\n' + f'{"":8s} {"TAvg":>8s}  {"TRatio":>8s} ({"TStd":>8s})   {"Results":s}'
        print(s)
        fout.write(s+'\n')
        for stall in range(1,16):
            for yflag in ['-', 'Y']:
                tavg, tstd, tres, sfull = test_NoBankConflict(stall, 1, yflag, 32)
                tratio = tavg * 4 / BASELINE
                s = f'[{yflag}:S{stall:02d}]: {tavg:8.3f} ({tratio:8.4f}), {tstd:8.3f},  {tres:s}  {sfull}'
                print(s)
                fout.write(s+'\n')


def test_ReuseBankConflict(r1, r2, reuse1, reuse2):
    cat = CuAsmTemplate(projectPath + 'regBank/res/regBankTest.template.sm_86.cuasm')
    
    s_init  = '[B------:R-:W-:-:S01]  MOV R5, RZ ; \n'
    for r in range(8,17):
        s_init += f'[B------:R-:W-:-:S01]  MOV R{r:d}, 0x3f800000 ; \n'

    s_work1  = f'      [B------:R-:W-:-:S01]  FFMA R5, R{r1}{reuse1}, R{r2}{reuse2}, R5; \n' # R5 += 1
    for i in range(3):
        s_work1 += f'      [B------:R-:W-:-:S01]  FFMA R{i+20}, R{r1}{reuse1}, R{r2}{reuse2}, R16; \n'
    s_work1 = s_work1 * 64

    cat.setMarker('INIT', s_init)
    cat.setMarker('WORK_1', s_work1)

    s_regnum = f'  	.sectioninfo	@"SHI_REGISTERS={32}"'
    cat.setMarker('REGNUM', s_regnum)

    cat.generate(projectPath + 'regBank/midRes/regBankTest.sm_86.cuasm')

    build()

    res = run_exe()
    
    return parseResult(res.decode()) 

# Bank映射关系及Reuse Cache的效果
def doTest_ReuseBankConflict():
    with open('res/res_ReuseBankConflict.txt', 'w') as fout:
        for r1 in range(8, 16):
            r1s = f'R{r1}'
            for r2 in range(8, 16):
                r2s = f'R{r2}'
                for reuse1 in ['', '.reuse']:
                    reuse1_s = '-' if reuse1!='.reuse' else 'R'
                    for reuse2 in ['', '.reuse']:
                        tavg, tstd, tres, sfull = test_ReuseBankConflict(r1, r2, reuse1, reuse2)
                        tratio = tavg * 4 / BASELINE
                        reuse2_s = '-' if reuse2!='.reuse' else 'R'
                        s = f'({r1s:3s}, {r2s:3s}, "{reuse1_s}{reuse2_s}"): {tavg:8.3f} ({tratio:8.4f}), {tstd:8.3f},  {tres:s}  {sfull}'
                        print(s)
                        fout.write(s+'\n')


if __name__ == '__main__':
    # 
    os.system('nvidia-smi -ac 7000,1702')
    
    # doTest_NoBankConflict()
    doTest_ReuseBankConflict()