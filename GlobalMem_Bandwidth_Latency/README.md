# Global Memory Bandwidth
## 结论
- float
  - GRD_SIZE=90000: Global Memory Bandwidth: 327.241499GB/s
  - GRD_SIZE=9000: Global Memory Bandwidth: 326.575679GB/s
## 思路
- Global Mem的理论访存峰值吞吐 = mem frequency * DDR_factor * 总线宽度 
  - GDDR和DDR的区别在于 图形内存的有效带宽是DDR的4倍。 DDR就是双倍数据速率。
- nvidia-smi 查出来的 mem freq 就是已经乘4了
  - 3060     7000M * 2 * 192/8  = 336 GB/s
  - TuringT4  5000M * 2 * 256/8  = 320GB/s

- BLK_SIZE/GRD_SIZE/计时的选择同L2_D-Cache，让没有邻居依赖的ldg_cv跑满整个GPU，获得吞吐。
- 用float2没有提升。
## 步骤
~~~bash
nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/globalMem_bandwidth globalMem_bandwidth.cu
~~~



## globalMem_bandwidth_YHs
> 这份代码直接copy自：https://github.com/Yinghan-Li/YHs_Sample 作为参考






# Global Memory Latency
> 关于全局内存 L1/L2 TLB 的理论理解，我做的很差，所以MicroBenchmark和思路极有可能 是错的！！！
## 结论
- globalMem_latency_None: In the case of L2 miss and L2 TLB hit, global memory load latency is: 543.532000 cycles
- globalMem_latency_IADD: global memory load latency: 517.060000 cycles
- globalMem_latency_IMAD: global memory load latency: 533.520000 cycles
## 思路
- 全局内存的访问涉及到 L1TLB L1Cache L2TLB L2Cache。
- TuringT4的TLB部分，我的理解：
  - L1Cache的TLB是VIPT的，TLB miss对性能影响不大(存疑)。在测latency的时候，我直接忽略了它的影响。
  - L2Cache的TLB是PIPT的，TLB miss的性能损失很明显。
- 基于此，全局内存的latency分:
  - L2TLB mis & L2cache mis  & L1cache mis 
  - L2TLB mis & L2cache hit  & L1cache mis
  - L2TLB hit & L2cache mis  & L1cache mis
  - L2TLB hit & L2cache hit  & L1cache mis
  - L2TLB --- & L2cache ---  & L1cache hit
- L1TLB和L2TLB可以用L1_TLB_detect.cu（测试过）和L2_TLB_detect.cu（理论上）测试。
- 但是L2_TLB_detect 按 TuringT4 的论文的结论来看，需要大于8G的全局内存，我的设备达不到，所以放弃测试，并且假设不会有L2TLB miss的情况。
- 所以，这里的globalMem_latency测试专指 L2TLB hit & L2cache mis  & L1cache mis。

- 测latency仍旧是一个warp运行邻居依赖背靠背的ldg。
- L2Cache有硬件预取策略(Dissecting the GPU memory hierarchy through Microbenchmarking)，为了避免该预取造成的L2Cache hit，需要用无关数据填充L2cache(flushL2.cuh)。
## 步骤
~~~bash
# L1_TLB_detect (注意! 这俩TLB的测试可能根本就是错的!)
nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/L1_TLB_detect L1_TLB_detect.cu
python3 L1_TLB_detect_res_process.py

# L2_TLB_detect 在Ampere架构上可能需要8G左右的全局内存才能跑起来，因为L2TLB的覆盖范围有那么大。
# 因此，L2_TLB_detect.cu可能有错误存在。
nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/L2_TLB_detect L2_TLB_detect.cu

# globalMem_latency_None：核函数中ldg的结果是指针
nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/globalMem_latency_None globalMem_latency_None.cu
# globalMem_latency_IADD：核函数中ldg的结果是偏移量，用IADD进行指针计算
nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/globalMem_latency_IADD globalMem_latency_IADD.cu
# globalMem_latency_IMAD：核函数中ldg的结果是偏移量，用IMAD进行指针计算
nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/globalMem_latency_IMAD globalMem_latency_IMAD.cu
~~~



## globalMem_latency_YHs
> 这份代码直接copy自：https://github.com/Yinghan-Li/YHs_Sample 作为参考