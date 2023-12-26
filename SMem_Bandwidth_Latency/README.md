# Shared Memory Bandwidth
## smem_bandwidth_*
### 结论





如果cuda code汇编成sass不能准确的表达含义 就尝试ptx code。


nvcc --keep --keep-dir latency_midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/smem_latency smem_latency.cu && cuasm --bin2asm latency_midRes/smem_latency.sm_86.cubin -o latency_midRes/smem_latency.sm_86.cuasm
### 思路
- SM的峰值访存吞吐计算方式：bank带宽 * 32 * SM频率
按 TuringT4 和 Volta 的结论： V100/P100的bank带宽是一个时钟周期4B 阉割过的架构是两个时钟周期4B

B = P\*Bs\*ws\*fg 
Turing T4  1590M * 32 * 4B * 40 / 2 = 4070GB/s

3060:
1700M * 32 * 4 * 30 = 6528GB/s  或 SM是217.6GB/s
1700M * 32 * 4 * 30 / 2 = 3264GB/s  或 SM是108.8GB/s
这里是否除以2 是看该架构 读一个bank到底需要1个还是2个时钟周期。
### 步骤



# Shared Memory Latency
## smem_latency_*
### 结论

### 思路

### 步骤