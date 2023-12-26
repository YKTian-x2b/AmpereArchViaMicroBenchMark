# Global Memory Bandwidth
// Global Mem的理论访存峰值吞吐 = mem frequency * DDR_factor * 总线宽度 
// GDDR和DDR的区别在于 图形内存的有效带宽是DDR的4倍。 DDR就是双倍数据速率。
// 这里nvidia-smi 查出来的 mem freq 就是已经乘4了
// 3060     7000M * 2 * 192/8  = 336 GB/s
// turing t4  5000M * 2 * 256/8  = 320GB/s


// UNROLL = 10
(base) yujixuan@yujixuan:GlobalMem_Bandwidth_Latency$ res/globalMem_latency_YHs 
DRAM latency 475 cycles
(base) yujixuan@yujixuan:GlobalMem_Bandwidth_Latency$ res/globalMem_latency_IADD
global memory load latency: 482.300000 cycles
(base) yujixuan@yujixuan:GlobalMem_Bandwidth_Latency$ res/globalMem_latency_IMAD
global memory load latency: 518.800000 cycles
(base) yujixuan@yujixuan:GlobalMem_Bandwidth_Latency$ res/globalMem_latency_None
In the case of L2 miss and L2 TLB hit, global memory load latency is: 528.900000 cycles

// UNROLL = 50
(base) yujixuan@yujixuan:GlobalMem_Bandwidth_Latency$ res/globalMem_latency_YHs 
DRAM latency 526 cycles
(base) yujixuan@yujixuan:GlobalMem_Bandwidth_Latency$ res/globalMem_latency_YHs 
DRAM latency 518 cycles
(base) yujixuan@yujixuan:GlobalMem_Bandwidth_Latency$ res/globalMem_latency_YHs 
DRAM latency 530 cycles
(base) yujixuan@yujixuan:GlobalMem_Bandwidth_Latency$ res/globalMem_latency_YHs 
DRAM latency 524 cycles
(base) yujixuan@yujixuan:GlobalMem_Bandwidth_Latency$ res/globalMem_latency_YHs 
DRAM latency 520 cycles
(base) yujixuan@yujixuan:GlobalMem_Bandwidth_Latency$ res/globalMem_latency_YHs 
DRAM latency 521 cycles
(base) yujixuan@yujixuan:GlobalMem_Bandwidth_Latency$ res/globalMem_latency_YHs 
DRAM latency 519 cycles
(base) yujixuan@yujixuan:GlobalMem_Bandwidth_Latency$ res/globalMem_latency_IADD
global memory load latency: 516.260000 cycles
(base) yujixuan@yujixuan:GlobalMem_Bandwidth_Latency$ res/globalMem_latency_IADD
global memory load latency: 515.440000 cycles
(base) yujixuan@yujixuan:GlobalMem_Bandwidth_Latency$ res/globalMem_latency_IMAD
global memory load latency: 535.480000 cycles
(base) yujixuan@yujixuan:GlobalMem_Bandwidth_Latency$ res/globalMem_latency_IMAD
global memory load latency: 546.440000 cycles
(base) yujixuan@yujixuan:GlobalMem_Bandwidth_Latency$ res/globalMem_latency_IMAD
global memory load latency: 538.740000 cycles
(base) yujixuan@yujixuan:GlobalMem_Bandwidth_Latency$ res/globalMem_latency_None
In the case of L2 miss and L2 TLB hit, global memory load latency is: 527.888000 cycles
(base) yujixuan@yujixuan:GlobalMem_Bandwidth_Latency$ res/globalMem_latency_None
In the case of L2 miss and L2 TLB hit, global memory load latency is: 543.264000 cycles
(base) yujixuan@yujixuan:GlobalMem_Bandwidth_Latency$ res/globalMem_latency_None
In the case of L2 miss and L2 TLB hit, global memory load latency is: 563.110000 cycles
(base) yujixuan@yujixuan:GlobalMem_Bandwidth_Latency$ res/globalMem_latency_None
In the case of L2 miss and L2 TLB hit, global memory load latency is: 528.614000 cycles




# Global Memory Latency
- 全局内存的访问涉及到 L1TLB L1Cache L2TLB L2Cache。
- TuringT4的TLB部分，我的理解：
  - L1Cache的TLB是VIPT的，因为可以并行，所以TLB miss对性能影响不大。在测latency的时候，我直接忽略了它的影响。
  - L2Cache的TLB是PIPT的，TLB miss的性能损失很明显。
- 基于此，全局内存的latency分:
  - L2TLB mis & L2cache mis  & L1cache mis 
  - L2TLB hit & L2cache mis  & L1cache mis
  - L2TLB hit & L2cache hit  & L1cache mis
  - L2TLB --- & L2cache ---  & L1cache hit