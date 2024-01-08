# l2Cache_latency_my
## 结论
- l2 cache access latency: 222.1 cycles
## 思路
- 在kernel计时代码中间，放一系列有邻居依赖的背靠背L2_D-Cache访存指令，就能严格算出来每条指令从发出到取回结果的时间。
- 读取结果直接就是指针，这样得到的SASS就非常干净，只有LDG。
- 测试latency的线程维度选择只要能保证LDG能背靠背的发出就行。
- 全局内存访问的延迟与L2CacheTLB的hit/mis有关，我们这里测试的是L2的TLB和Cache都命中的情况。
  - 所以在核函数中加入一条指令填充L2 TLB。
  - 主函数的Warmup部分填充了L2 Cache。
  - 详见GlobalMem_Bandwidth_Latency的README分析。
## 步骤
~~~bash
# 直接编译就能得到运行结果
nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/l1Cache_latency_my l1Cache_latency_my.cu
# 可以欣赏一下非常干净的SASS实现
nvcc --keep --keep-dir midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/l1Cache_latency_my l1Cache_latency_my.cu
cuasm --bin2asm midRes/l1Cache_latency_my.sm_86.cubin midRes/l1Cache_latency_my.sm_86.cuasm
~~~




# l2Cache_latency_YHs
> 这份代码直接copy自：https://github.com/Yinghan-Li/YHs_Sample 作为参考