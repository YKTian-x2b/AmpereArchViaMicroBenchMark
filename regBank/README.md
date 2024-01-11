# regBankTest_2Bank
## 结论
- 寄存器文件分为两个bank，寄存器映射方式：bank索引 = 寄存器索引 % 2。
- 主要是区分到底是4个bank还是2个bank。
## 思路
- 运行如下指令序列，获得浮点性能：FFMA R6, R8, R9, RX; 和 FFMA R6, R7, R9, RX; （X取10-16）
- 如果是分四个bank且bank索引 = 寄存器索引 % 4； 那么R12/R16和R8应该是冲突的，R7和R11应该是冲突的，此类指令序列的浮点性能应该比其余非冲突序列差
- 如果是分两个bank且bank索引 = 寄存器索引 % 2； 就分一个时钟周期能读1个还是2个32位寄存器。
  - 按TuringT4论文的结论，一个bank有两个port，每时钟周期每port能读一个32位寄存器的话，三个源寄存器全都来自一个bank才会发生冲突。
  - 按cloudcore大佬的结论，每时钟周期每bank能读一个32位寄存器的话，FFMA这样的三源操作数指令，在没有reuse情况下，是一定会有性能损失的。
- 所以，加一个指令序列 FFMA R6, R8, R9, 1; 来揭露一下TuringT4在思路上没说到的点。更详细的MicroBenchmark见 regBankTest。

- 从结果res/res_2Bank.txt 可以看出应该不是四个bank，是两个。
- 考虑加入立即数的FFMA性能更好，可能是每时钟周期每bank能读一个32位寄存器。
## 步骤
~~~bash
nvcc --keep --keep-dir midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I/opt/kaiProjects/GEMM_kai/Utils -L /usr/local/cuda/lib64 -l cuda -o res/regBankTest_2Bank regBankTest_2Bank.cu

cuasm --bin2asm midRes/regBankTest_2Bank.sm_86.cubin -o midRes/regBankTest_2Bank.sm_86.cuasm

cp midRes/regBankTest_2Bank.sm_86.cuasm res/regBankTest_2Bank.template.sm_86.cuasm && cp midRes/regBankTest_2Bank.sm_86.cuasm res/regBankTest_2Bank.origin.sm_86.cuasm
# 在cuasm里插入FFMA序列 可以在res/*.template.sm_86.cuasm里找到插入位置
// @CUASM_INSERT_MARKER_POS.

python3 test_regBank_2Bank.py
~~~



# regBankTest

> 思路和代码来源：https://zhuanlan.zhihu.com/p/373063821
## 步骤
~~~bash
nvcc --keep --keep-dir midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I/opt/kaiProjects/GEMM_kai/Utils -L /usr/local/cuda/lib64 -l cuda -o res/regBankTest regBankTest.cu

cuasm --bin2asm midRes/regBankTest.sm_86.cubin -o midRes/regBankTest.sm_86.cuasm

cp midRes/regBankTest.sm_86.cuasm res/regBankTest.template.sm_86.cuasm && cp midRes/regBankTest.sm_86.cuasm res/regBankTest.origin.sm_86.cuasm

// @CUASM_INSERT_MARKER_POS.

python3 test_regBank.py
~~~
## test_NoBankConflict
### 结论
- 没有BankConflict和Reuse的baseline, 理论峰值是4x左右（FFMA的latency是4个clock，所以序列是4个一组）
- 在没有reuse的情况下，大概只能7x 不到峰值的2倍 
- 如果每时钟周期每bank能读一个32位寄存器的话，FFMA可能需要两个clock才能拿到全部操作数。（达不到吞吐峰值的原因是re-issue吗？）

## test_ReuseBankConflict
### 结论
- 一个bank读一个操作数      + 两个reuse             4x
- 两个bank各读一个操作数    + 一个reuse              5x
- 一个bank读两个操作数      + 一个reuse/广播         7x
- 一个bank读两个操作数      + 另一个bank读一个        7x
- 一个bank读三个操作数                              11x
- 每个bank每个clock只能进行一次32位读取

~~~assembly
# 说明每个bank每个clock只能进行一次32位读取 
# 不到2或3倍，可能是有优化？
(R8 , R10, R16, "--"):    6.399 ( 10.9104)      # bankConflict且没有reuse 不到峰值的3倍 
(R8 , R10, R16, "-R"):    4.101 (  6.9913)      # bankConflict且reuse一个 不到峰值的2倍 
(R8 , R10, R16, "R-"):    4.100 (  6.9910)
(R8 , R10, R16, "RR"):    2.377 (  4.0530)      # bankConflict且reuse两个 接近峰值

# bankConflict但两个slot的操作数一样，reuse一个和没reuse性能一样是不到峰值的2倍，说明每个Operand slot的reuse独立。
# 没reuse和reuse一个性能一样，说明只取了一次R8，会广播。但从reuseCache取没有广播。
(R8 , R8 , R16, "--"):    4.099 (  6.9890)      
(R8 , R8 , R16, "-R"):    4.100 (  6.9896)
(R8 , R8 , R16, "R-"):    4.100 (  6.9903)
(R8 , R8 , R16, "RR"):    2.376 (  4.0517)

(R9 , R10, R16, "--"):    4.100 (  6.9903)        # 不到峰值的2倍而不是3倍 说明不是4个bank，就是2个
(R9 , R10, R16, "-R"):    2.946 (  5.0228)        # 两个bank各取一个，但不是峰值！！！ 不懂
(R9 , R10, R16, "R-"):    4.100 (  6.9900)        # 和没有reuse性能一样
(R9 , R10, R16, "RR"):    2.377 (  4.0527)        # 
~~~


## other
> 更加细节的测试没做，等后续需要的时候补上



