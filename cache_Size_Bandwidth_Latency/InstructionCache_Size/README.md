L0 i-cache 属于 scheduler / processing block
L1 i-cache 属于 SM
L2 i-cache 被所有SM共享

Turing T4的L0 i-cache是16KB
A100的 L0 i-cache是32KB
所以 3060的L0 i-cache上限是32KB 大概就是个16KB

Turing T4的L1 i-cache是46KB
A100的 L1 i-cache是128KB
所以 3060的L1 i-cache上限是128KB 大概就是个64KB

3060的L2 i-cache上限是3*1024KB

一条指令128bit = 16B； 1KB就是64条 
1024 * 16B * 2 = 32KB （预热，所以*2）

16KB=1024条
32KB=2048条

64KB=4096条
128KB=8192条

256KB=16384条

3\*1024KB=3\*65536条
6\*1024KB=6\*65536条



FFMA指令序列被执行两次 第一次预热指令缓存 第二次记录时间
FFMA指令仅对寄存器进行操作
选择操作数寄存器，使每条指令与其邻居不存在寄存器依赖


### 结论
- 3060：
- 16KB的L0
- 32KB的L1
