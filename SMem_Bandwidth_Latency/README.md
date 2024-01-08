# Shared Memory Bandwidth
## smem_bandwidth_*
### 结论
- float:
  - Shared Mem Bandwidth is  62.844 Bytes per cycle per SM
  - Shared Mem Bandwidth is  106.835 GBps per SM
- float4:
  - Shared Mem Bandwidth is  113.974 Bytes per cycle per SM
  - Shared Mem Bandwidth is  193.755 GBps per SM
- float2:
  - Shared Mem Bandwidth is  126.099 Bytes per cycle per SM
  - Shared Mem Bandwidth is  214.368 GBps per SM
### 思路
- SM的峰值访存吞吐计算方式：bank带宽 * 32 * SM频率
按 TuringT4 和 Volta 的结论推断： V100/P100的bank带宽是一个时钟周期4B 旧架构阉割过的版本是两个时钟周期4B
- 整个GPU的吞吐：
B = P\*Bs\*ws\*fg 
TuringT4：
1590M * 32 * 4B * 40 / 2 = 4070GB/s
3060:
1700M * 32 * 4B * 30 = 6528GB/s  或 SM是217.6GB/s
- 这里是否除以2 是看该架构 读一个bank到底需要1个还是2个时钟周期。
- 217.6GB/s 对应的就是 128B per cycle per SM

- 保证所有线程跑在一个SM上，拉满线程数（即启动一个1024线程的Block），做多次STS，获取实际吞吐。

- 从实验结果分析，同样长度的STS.64和STS序列，执行花费了同样的时钟周期，说明STS内核的TLP+ILP并不能使LSU单元满载。
- 更进一步的原因，我不懂。
### 步骤
~~~bash
# float
nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/smem_bandwidth_float smem_bandwidth_float.cu
# float4
nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/smem_bandwidth_float4 smem_bandwidth_float4.cu
# float2
nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/smem_bandwidth_float2 smem_bandwidth_float2.cu
~~~




# Shared Memory Latency
## smem_latency_ld
### 结论
- UNROLL 500次的ld结果是：22.9620 约等于 23 个时钟周期
- UNROLL 50次的ld结果是：22.620000 cycles
### 思路
- 在kernel计时代码中间放一系列有邻居依赖的背靠背SMem加载指令，就能严格算出来每条指令从发出到取回结果的时间。
- 让读取结果直接就是指针的方法非常巧妙，详见代码注释，得到的SASS同样非常干净，只有LDS。
- SMem是片上的，GRD_SIZE取1。限制BLK_SIZE使，不冲突得取32个bank一次。
- shared Memory和L1_D-Cache的硬件是相同的，但前者的基本单元bank，后者的基本单元是cacheline。
### 步骤
~~~bash
nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/smem_latency_ld smem_latency_ld.cu
~~~


## smem_latency_st
### 结论
- 我测到的结果是11cycle
### 思路
- 首先，根据 TuringT4 和 Demystifying Ampere 论文的结论：共享内存的存储延迟应该是19cycle。
  - 大概率是我知识有限，搞错了。后面放了测试的过程和分析。
- 有邻居依赖的背靠背存储操作，我只想到修改ControlCode的barrier，[B0-----:R0:W-:-:S04]。
### 步骤
~~~bash
nvcc --keep --keep-dir latency_midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/smem_latency_st smem_latency_st.cu
cuasm --bin2asm latency_midRes/smem_latency_st.sm_86.cubin -o latency_midRes/smem_latency_st.sm_86.cuasm
# 修改方式见下面的汇编
cuasm --asm2bin latency_midRes/smem_latency_st.sm_86.cuasm -o latency_midRes/smem_latency_st.sm_86.cubin
~~~
~~~assembly
## UNROLL = 50

# 标准的隔4个周期发射
4.000000 cycles:
[B------:R-:W-:Y:S02]         /*0360*/                   CS2R.32 R11, SR_CLOCKLO ;
[B------:R0:W-:-:S04]         /*0370*/                   STS [R0.X4], R0 ;
[B------:R0:W-:-:S04]         /*0380*/                   STS [R0.X4+0x4], R0 ;
[B------:R0:W-:-:S04]         /*0390*/                   STS [R0.X4+0x8], R0 ;
[B------:R0:W-:-:S04]         /*03a0*/                   STS [R0.X4+0xc], R0 ;
[B------:R0:W-:-:S04]         /*03b0*/                   STS [R0.X4+0x10], R0 ;
...
[B------:R0:W-:-:S04]         /*0640*/                   STS [R0.X4+0xb4], R0 ;
[B------:R0:W-:-:S04]         /*0650*/                   STS [R0.X4+0xb8], R0 ;
[B------:R0:W-:-:S04]         /*0660*/                   STS [R0.X4+0xbc], R0 ;
[B------:R0:W-:-:S04]         /*0670*/                   STS [R0.X4+0xc0], R0 ;
[B------:R0:W-:-:S02]         /*0680*/                   STS [R0.X4+0xc4], R0 ;
[B------:R-:W-:Y:S02]         /*0690*/                   CS2R.32 R13, SR_CLOCKLO ;
[B------:R-:W1:-:S01]         /*06a0*/                   LDS R9, [R0.X4+0xc4] ;

# 加一个barrier
4.200000 cycles：
[B------:R-:W-:Y:S02]         /*0360*/                   CS2R.32 R11, SR_CLOCKLO ;
[B------:R0:W-:-:S04]         /*0370*/                   STS [R0.X4], R0 ;
[B------:R0:W-:-:S04]         /*0380*/                   STS [R0.X4+0x4], R0 ;
[B------:R0:W-:-:S04]         /*0390*/                   STS [R0.X4+0x8], R0 ;
[B------:R0:W-:-:S04]         /*03a0*/                   STS [R0.X4+0xc], R0 ;
[B------:R0:W-:-:S04]         /*03b0*/                   STS [R0.X4+0x10], R0 ;
...
[B------:R0:W-:-:S04]         /*0640*/                   STS [R0.X4+0xb4], R0 ;
[B------:R0:W-:-:S04]         /*0650*/                   STS [R0.X4+0xb8], R0 ;
[B------:R0:W-:-:S04]         /*0660*/                   STS [R0.X4+0xbc], R0 ;
[B------:R0:W-:-:S04]         /*0670*/                   STS [R0.X4+0xc0], R0 ;
[B------:R0:W-:-:S02]         /*0680*/                   STS [R0.X4+0xc4], R0 ;
[B0-----:R-:W-:Y:S02]         /*0690*/                   CS2R.32 R13, SR_CLOCKLO ;
[B------:R-:W1:-:S01]         /*06a0*/                   LDS R9, [R0.X4+0xc4] ;

# 以我目前的认知 这样就是有邻居依赖的背靠背了 算出来大概是11个cycle
11.040000 cycles:
[B------:R-:W-:Y:S02]         /*0360*/                   CS2R.32 R11, SR_CLOCKLO ;
[B------:R0:W-:-:S04]         /*0370*/                   STS [R0.X4], R0 ;
[B0-----:R0:W-:-:S04]         /*0380*/                   STS [R0.X4+0x4], R0 ;
[B0-----:R0:W-:-:S04]         /*0390*/                   STS [R0.X4+0x8], R0 ;
[B0-----:R0:W-:-:S04]         /*03a0*/                   STS [R0.X4+0xc], R0 ;
[B0-----:R0:W-:-:S04]         /*03b0*/                   STS [R0.X4+0x10], R0 ;
...
[B0-----:R0:W-:-:S04]         /*0640*/                   STS [R0.X4+0xb4], R0 ;
[B0-----:R0:W-:-:S04]         /*0650*/                   STS [R0.X4+0xb8], R0 ;
[B0-----:R0:W-:-:S04]         /*0660*/                   STS [R0.X4+0xbc], R0 ;
[B0-----:R0:W-:-:S04]         /*0670*/                   STS [R0.X4+0xc0], R0 ;
[B0-----:R0:W-:-:S02]         /*0680*/                   STS [R0.X4+0xc4], R0 ;
[B0-----:R-:W-:Y:S02]         /*0690*/                   CS2R.32 R13, SR_CLOCKLO ;
[B------:R-:W1:-:S01]         /*06a0*/                   LDS R9, [R0.X4+0xc4] ;

# 单独测试是13个cycle 可能是计时的两条指令造成2个cycle误差
13.000000 cycles:
[B------:R-:W-:Y:S02]         /*0360*/                   CS2R.32 R11, SR_CLOCKLO ;
[B------:R0:W-:-:S04]         /*0680*/                   STS [R0.X4+0xc4], R0 ;
[B0-----:R-:W-:Y:S02]         /*0690*/                   CS2R.32 R13, SR_CLOCKLO ;
[B------:R-:W1:-:S01]         /*06a0*/                   LDS R9, [R0.X4+0xc4] ;

# 因为这里应该是23，但实际结果是25
25.000000 cycles:
[B------:R-:W-:Y:S02]         /*0360*/                   CS2R.32 R11, SR_CLOCKLO ;
[B------:R-:W1:-:S04]         /*06a0*/                   LDS R9, [R0.X4+0xc4] ;
[B-1----:R-:W-:Y:S02]         /*0690*/                   CS2R.32 R13, SR_CLOCKLO ;

# 那这里就是 11 + 23 + 2
36.000000 cycles:
[B------:R-:W-:Y:S02]         /*0360*/                   CS2R.32 R11, SR_CLOCKLO ;
[B------:R0:W-:-:S04]         /*0680*/                   STS [R0.X4+0xc4], R0 ;
[B0-----:R-:W1:-:S04]         /*06a0*/                   LDS R9, [R0.X4+0xc4] ;
[B-1----:R-:W-:Y:S02]         /*0690*/                   CS2R.32 R13, SR_CLOCKLO ;
# 所以我测到的结果是11cycle，和19cycle相差甚远
~~~



## smem_latency_YHs
> 这份代码直接copy自：https://github.com/Yinghan-Li/YHs_Sample 作为参考