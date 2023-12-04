import os
import re
import sys
import subprocess
import math

sys.path.append('/opt/kaiProjects/cuda_libs/CuAssembler-master/CuAsm')

import CubinFile
import CuInsAssemblerRepos
import CuInsFeeder
import CuAsmParser
import CuAsmLogger


# baseline result for:
# -  grid=7200, block=128, NIter=256, 192 instruction per iteration
# -  No bank conflict
# -  MemFreq = 7200 MHz, SMFreq = 2100 MHz
BASELINE = 16.74

class CuAsmTemplate:
    def __init__(self, template_name):
        self.m_FileParts = []
        self.m_MarkerDict = {}

        p = re.compile(r'@CUASM_INSERT_MARKER_POS\.(\w+)')

        with open(template_name) as fin:
            # print(f'Loading template file {template_name}...')
            buf = ''
            iline = 0
            for line in fin:
                iline += 1
                res = p.search(line)
                if res is not None:
                    # push buf in and reset buf
                    self.m_FileParts.append(buf)
                    buf = ''

                    marker = res.groups()[0]
                    if marker in self.m_MarkerDict:
                        print(f'  Duplicate marker "{marker}" in line {iline:d}')
                    else:
                        # print(f'  New marker "{marker}" in line {iline:d}')
                        self.m_MarkerDict[marker] = None
                    
                    self.m_FileParts.append((marker, line))
                else:
                    buf += line

            self.m_FileParts.append(buf)

    def setMarker(self, marker, s):
        self.m_MarkerDict[marker] = s
    
    def resetAllMarkers(self):
        for k in self.m_MarkerDict:
            self.m_MarkerDict[k] = None

    def generate(self, outfile):
        with open(outfile, 'w') as fout:
            for p in self.m_FileParts:
                if isinstance(p, str):
                    fout.write(p)
                elif isinstance(p, tuple):
                    marker, orig_line = p

                    # original line is always written back
                    fout.write(orig_line)
                    if self.m_MarkerDict[marker] is not None:
                        fout.write(self.m_MarkerDict[marker])
                        fout.write('\n') # ensure a newline after the insertion


def cubin2cuasm(binname, asmname=None):
    cf = CubinFile.CubinFile(binname)
    
    if asmname is None:
        if binname.endswith('.cubin'):
            asmname = binname.replace('.cubin', '.cuasm')
        else:
            asmname = binname + '.cuasm'
            
    cf.saveAsCuAsm(asmname)


def cuasm2cubin(asmname, binname=None):
    cap = CuAsmParser.CuAsmParser()
    cap.parse(asmname)
    if binname is None:
        if asmname.endswith('.cuasm'):
            binname = asmname.replace('.cuasm', '.cubin')
        else:
            binname = asmname + '.cubin'

    cap.saveAsCubin(binname)


def build(use_driver_api=True):
    cuasm2cubin('/opt/kaiProjects/GEMM_kai/MicroBenchmark/regBank/regBankTest.sm_86.cuasm')
    if not use_driver_api:
        print("not using driver api, so exit(0)")
        exit(0)
        # os.environ['PTXAS_HACK'] = "G:\\Work\\CuAssembler\\TestData\\microbench\\RegBank\\ptxhack.map"
        # subprocess.check_output('make clean')
        # subprocess.check_output('make')


def template_test():
    cat = CuAsmTemplate('/opt/kaiProjects/GEMM_kai/MicroBenchmark/save/regBankTest.template.sm_86.cuasm')
    
    cat.setMarker('INIT', '      // hehe init here!')
    cat.setMarker('WORK_1', '      // work1 here!')

    cat.generate('test.cuasm')


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
        res = subprocess.check_output('/opt/kaiProjects/GEMM_kai/MicroBenchmark/regBank/res/regBankTest')
        return res
    except subprocess.CalledProcessError as e:
        print(f'Error happened when running exe (return code={e.returncode})!')
        exit(e.returncode)


def test_NoBankConflict(stall1, stall2, yflag, regnum):
    cat = CuAsmTemplate('/opt/kaiProjects/GEMM_kai/MicroBenchmark/save/regBankTest.template.sm_86.cuasm')
    
    s_init  = '[B------:R-:W-:-:S01]  MOV R4, RZ ; \n'
    for r in range(8,17):
        s_init += f'[B------:R-:W-:-:S01]  MOV R{r:d}, 0x3f800000 ; \n'

    s_work1  = f'      [B------:R-:W-:{yflag}:S{stall1:02d}]  FFMA R4, R9, R10, R4; \n' # R4 += 1
    for i in range(3):
        s_work1 += f'      [B------:R-:W-:{yflag}:S{stall2:02d}]  FFMA R{i+12}, R9, R10, R11; \n' # R4 += 1
    s_work1 = s_work1 * 2

    s_work2 = s_work1

    cat.setMarker('INIT', s_init)
    cat.setMarker('WORK_1', s_work1)
    cat.setMarker('WORK_2', s_work2)

    # s_regnum = f'  	.sectioninfo	@"SHI_REGISTERS={regnum}"'
    # cat.setMarker('REGNUM', s_regnum)

    cat.generate('/opt/kaiProjects/GEMM_kai/MicroBenchmark/regBank/regBankTest.sm_86.cuasm')

    build()

    res = run_exe()
    return parseResult(res.decode())


def doTest_NoBankConflict():
    with open('res_NoBankConflict.txt', 'w') as fout:
        regnum = 32
        # print(f'{"":8s} {"TAvg":>8s} ({"TRatio":>8s}) {"TStd":>8s}    {"Results":s}')
        for stall in range(1,16):
            for yflag in ['-', 'Y']:
                tavg, tstd, tres, sfull = test_NoBankConflict(stall, stall, yflag, regnum)
                tratio = tavg * 6 / BASELINE
                s = f'[{yflag}:S{stall:02d}]: {tavg:8.3f} ({tratio:8.4f}), {tstd:8.3f},  {tres:s}  {sfull}'
                print(s)
                fout.write(s+'\n')
        
        s = '\n######### S## + 5*S01 ############\n' # + f'{"":8s} {"TAvg":>8s}  {"TStd":>8s} ({"TRatio":>8s})   {"Results":s}'
        print(s)
        fout.write(s+'\n')
        for stall in range(1,16):
            for yflag in ['-', 'Y']:
                tavg, tstd, tres, sfull = test_NoBankConflict(stall, 1, yflag, 32)
                s = f'[{yflag}:S{stall:02d}]: {tavg:8.3f} ({tratio:8.4f}), {tstd:8.3f},  {tres:s}  {sfull}'
                print(s)
                fout.write(s+'\n')


if __name__ == '__main__':
    
    os.system('nvidia-smi -ac 7000,2100')

    # cubin2cuasm('G:\\Work\\CuAssembler\\TestData\\microbench\\RegBank\\regbank_test.2.sm_50.cubin')
    # cubin2cuasm('G:\\Work\\CuAssembler\\TestData\\microbench\\RegBank\\regbank_test.uni.sm_50.cubin')
    # cubin2cuasm('G:\\Temp\CubinSample\\eigenvalues\\NVIDIA.4.sm_50.cubin')
    # build()

    #CuAsmLogger.disable()
    
    doTest_NoBankConflict()
    # doTest_BankConflictComb()
    # doTest_ReuseBankConflict()

    # doTest_ReuseSwitch()
    # doTest_ReuseStall()

    # test_Simple2()