# L0_I-CacheSizeTest_my
## 结论
- 3060：
  - 16KB的L0_I-Cache
  - 32KB的L1_I-Cache
  - L2_I-Cache的测试结果与理论结果差别很大，但是一般不会用到这个数据，所以放弃研究。
## 思路
- L0 i-cache 属于 scheduler / processing block。L1 i-cache 属于 SM。L2 i-cache 被所有SM共享。
- Turing T4的L0 i-cache是16KB
  - A100的 L0 i-cache是32KB
  - 所以 3060的L0 i-cache上限是32KB 大概就是个16KB
- Turing T4的L1 i-cache是46KB
  - A100的 L1 i-cache是128KB
  - 所以 3060的L1 i-cache上限是128KB 大概就是个64KB
- 3060的L2 i-cache上限是3*1024KB

- 在单个warp中插入递增长度的FFMA指令序列，观察指令长度溢出各级指令缓存时对CPI的影响
- FFMA指令序列被执行两次 第一次预热指令缓存 第二次记录时间
- FFMA指令仅对寄存器进行操作
- 选择操作数寄存器，使每条指令与其邻居不存在寄存器依赖
## 步骤
~~~bash
nvcc --keep --keep-dir midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/I-CacheSizeTest I-CacheSizeTest.cu

cuasm --bin2asm midRes/I-CacheSizeTest.sm_86.cubin -o midRes/I-CacheSizeTest.sm_86.cuasm

cp midRes/I-CacheSizeTest.sm_86.cuasm res/I-CacheSizeTest.template.sm_86.cuasm && cp midRes/I-CacheSizeTest.sm_86.cuasm res/I-CacheSizeTest.origin.sm_86.cuasm
# 在res/I-CacheSizeTest.template.sm_86.cuasm中手动插入如下注释，提示python脚本在对应位置插入FFMA序列
// @CUASM_INSERT_MARKER_POS.
# python脚本运行递增长度的FFMA序列，计时并绘制结果图
python3 test_I-CacheSize.py
~~~
## 其他
- 一条指令128bit = 16B； 1KB就是64条 
  - 16KB=1024条
  - 32KB=2048条
  - 64KB=4096条
  - 128KB=8192条
  - 256KB=16384条
  - 3\*1024KB=3\*65536条
  - 6\*1024KB=6\*65536条
- 因为有预热指令，所以实际存储在指令缓存中的指令条数应该乘2。

