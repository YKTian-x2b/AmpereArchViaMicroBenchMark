# # for ampere this is no BankConflict
# def test_BankConflict(stall1, stall2, yflag, regnum):
#     cat = CuAsmTemplate(projectPath + 'regBank/save/regBankTest.template.sm_86.cuasm')
    
#     s_init  = '[B------:R-:W-:-:S01]  MOV R5, RZ ; \n'
#     for r in range(8,14):
#         s_init += f'[B------:R-:W-:-:S01]  MOV R{r:d}, 0x3f800000 ; \n'

#     s_work1  = f'      [B------:R-:W-:{yflag}:S{stall1:02d}]  FFMA R5, R8, R9, 1; \n' # R4 += 1
#     for i in range(3):
#         s_work1 += f'      [B------:R-:W-:{yflag}:S{stall2:02d}]  FFMA R{i+11}, R8, R9, 1; \n' # R4 += 1
#     s_work1 = s_work1 * 64

#     # s_work2 = s_work1

#     cat.setMarker('INIT', s_init)
#     cat.setMarker('WORK_1', s_work1)
#     # cat.setMarker('WORK_2', s_work2)

#     s_regnum = f'  	.sectioninfo	@"SHI_REGISTERS={regnum}"'
#     cat.setMarker('REGNUM', s_regnum)

#     cat.generate(projectPath + 'regBank/regBankTest.sm_86.cuasm')

#     build()

#     res = run_exe()
#     return parseResult(res.decode())


# def doTest_BankConflict():
#     with open('res_NoBankConflict.txt', 'w') as fout:
#         regnum = 32
#         # print(f'{"":8s} {"TAvg":>8s} ({"TRatio":>8s}) {"TStd":>8s}    {"Results":s}')
#         for stall in range(1,16):
#             for yflag in ['-', 'Y']:
#                 tavg, tstd, tres, sfull = test_BankConflict(stall, stall, yflag, regnum)
#                 tratio = tavg * 6 / BASELINE
#                 s = f'[{yflag}:S{stall:02d}]: {tavg:8.3f} ({tratio:8.4f}), {tstd:8.3f},  {tres:s}  {sfull}'
#                 print(s)
#                 fout.write(s+'\n')
        
#         s = '\n######### S## + 5*S01 ############\n' # + f'{"":8s} {"TAvg":>8s}  {"TStd":>8s} ({"TRatio":>8s})   {"Results":s}'
#         print(s)
#         fout.write(s+'\n')
#         for stall in range(1,16):
#             for yflag in ['-', 'Y']:
#                 tavg, tstd, tres, sfull = test_BankConflict(stall, 1, yflag, 32)
#                 s = f'[{yflag}:S{stall:02d}]: {tavg:8.3f} ({tratio:8.4f}), {tstd:8.3f},  {tres:s}  {sfull}'
#                 print(s)
#                 fout.write(s+'\n')


if __name__ == '__main__':
    # 
    os.system('nvidia-smi -ac 7000,1702')

    # cubin2cuasm('G:\\Work\\CuAssembler\\TestData\\microbench\\RegBank\\regbank_test.2.sm_50.cubin')
    # cubin2cuasm('G:\\Work\\CuAssembler\\TestData\\microbench\\RegBank\\regbank_test.uni.sm_50.cubin')
    # cubin2cuasm('G:\\Temp\CubinSample\\eigenvalues\\NVIDIA.4.sm_50.cubin')
    # build()

    # CuAsmLogger.disable()
    
    doTest_NoBankConflict()

    # doTest_BankConflictComb()
    # doTest_ReuseBankConflict()

    # doTest_ReuseSwitch()
    # doTest_ReuseStall()

    # test_Simple2()