
# regBankTest_2Bank
- 寄存器文件属于 warpScheduler/processingBlock 
- 寄存器文件分为两组 每组有两个32位端口 每个端口每个clock只能进行一次32位读取
- 寄存器映射方式： 组索引 = 寄存器索引 % 2
- FFMA R6, R98, R99, RX; 和 FFMA R6, R97, R99, RX;
- 从 res/res_BankConflict.txt 可以看出当源操作数出自同一bank时性能会差，印证了上述理论。


# regBankTest

## test_NoBankConflict
- 没有BankConflict和Reuse的baseline