L0 i-cache 属于 scheduler / processing block
L1 i-cache 属于 SM
L2 i-cache 被所有SM 共享

FFMA指令序列被执行两次 第一次预热指令缓存 第二次记录时间
FFMA指令仅对寄存器进行操作
选择操作数寄存器，使每条指令与其邻居不存在寄存器依赖


Turing T4的L0 i-cache是16KB
A100的 L0 i-cache是32KB

所以 3060上限是32KB 大概就是个 12KB-16KB