# l1Cache_latency_my
## 结论
- l1 cache access latency: 33 cycles
## 思路
- 在kernel计时代码中间，放一系列 背靠背L1_D-Cache访存指令，就能严格算出来每条指令从发出到取回结果的时间。
- 除了用pointerChase外，还要让读取结果直接就是指针，而不是偏移量，移除掉指针计算的那条指令。这样得到的SASS就非常干净，只有LDG。
- L1是属于SM的，显然GRD_SIZE取1。BLK_SIZE限制每次warp访存的大小在一个L1事务之内，保证结果准确（详见代码注释）。
- ld.global.ca.nc中nc的含义，我并不太懂。只用 ca 结果也差不多。
## 步骤
~~~bash
# 直接编译就能得到运行结果
nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/l1Cache_latency_my l1Cache_latency_my.cu
# 可以欣赏一下非常干净的SASS实现
nvcc --keep --keep-dir midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/l1Cache_latency_my l1Cache_latency_my.cu
cuasm --bin2asm midRes/l1Cache_latency_my.sm_86.cubin midRes/l1Cache_latency_my.sm_86.cuasm
~~~



# l1Cache_latency_YHs
> 这份代码直接copy自：https://github.com/Yinghan-Li/YHs_Sample 作为参考