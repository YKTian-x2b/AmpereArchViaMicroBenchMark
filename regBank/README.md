
# regBankTest_2Bank
- 寄存器文件属于 warpScheduler/processingBlock 
- 寄存器文件分为两个bank
- 寄存器映射方式： 组索引 = 寄存器索引 % 2
- FFMA R6, R98, R99, RX; 和 FFMA R6, R97, R99, RX;
- 从 res/res_BankConflict.txt 可以看出当源操作数出自同一bank时性能会差，印证了上述理论。


# regBankTest
> https://zhuanlan.zhihu.com/p/373063821
## test_NoBankConflict
- 没有BankConflict和Reuse的baseline, 理论峰值是4x左右
- 在没有reuse的情况下，大概只能7x 不到峰值的2倍 

## test_ReuseBankConflict
### 结论
- 一个bank读一个操作数      + 两个reuse             4x
- 两个bank各读一个操作数    + 一个reuse              5x
- 一个bank读两个操作数      + 一个reuse/广播         7x
- 一个bank读两个操作数      + 另一个bank读一个        7x
- 一个bank读三个操作数                              11x
- 每个bank每个clock只能进行一次32位读取



// 说明每个bank每个clock只能进行一次32位读取 
// 不到2或3倍，可能是有优化？
(R8 , R10, R16, "--"):    6.399 ( 10.9104)      // bankConflict且没有reuse 不到峰值的3倍 
(R8 , R10, R16, "-R"):    4.101 (  6.9913)      // bankConflict且reuse一个 不到峰值的2倍 
(R8 , R10, R16, "R-"):    4.100 (  6.9910)
(R8 , R10, R16, "RR"):    2.377 (  4.0530)      // bankConflict且reuse两个 接近峰值

// bankConflict但两个slot的操作数一样，reuse一个和没reuse性能一样是不到峰值的2倍，说明每个Operand slot的reuse独立。
// 没reuse和reuse一个性能一样，说明只取了一次R8，会广播。但从reuseCache取没有广播。
(R8 , R8 , R16, "--"):    4.099 (  6.9890)      
(R8 , R8 , R16, "-R"):    4.100 (  6.9896)
(R8 , R8 , R16, "R-"):    4.100 (  6.9903)
(R8 , R8 , R16, "RR"):    2.376 (  4.0517)


(R9 , R10, R16, "--"):    4.100 (  6.9903)        // 不到峰值的2倍而不是3倍 说明不是4个bank，就是2个
(R9 , R10, R16, "-R"):    2.946 (  5.0228)        // 两个bank各取一个，但不是峰值！！！
(R9 , R10, R16, "R-"):    4.100 (  6.9900)        // 和没有reuse性能一样
(R9 , R10, R16, "RR"):    2.377 (  4.0527)        // 



> 更加细节的测试没做，等后续需要的时候补上



