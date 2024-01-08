# L2cacheBW_float*
## 结论
- float
  - GRD_SIZE=90000: L2 cache bandwidth: 1276.236447GB/s
  - GRD_SIZE=9000: L2 cache bandwidth: 1126.735069GB/s
- float2
  - GRD_SIZE=90000: L2 cache bandwidth: 1312.528804GB/s
  - GRD_SIZE=9000: L2 cache bandwidth: 1266.337617GB/s
## 思路
- L2统一cache的访问延迟大概是200个时钟周期，且全局内存访问指令的发射延迟是4个时钟周期（maxwell）。
- L2Cache属于GPU，要达到L2的访存峰值，就要把所有SM用起来。所以，计时就得用event来做。
- 3060一个SM最多启动 3*16个warp，BLK_SIZE最大取512，最好不要小过128。
- GRD_SIZE至少是数千个(CUDA C * Guide里写的)，但是，这里选择了数万个：
  - 要想掩盖流水线最后一个LDG的200个时钟周期，就需要尽可能多的LDG指令，只有流水线超长的时候，流水线结束的尾耗时对BW计算的影响才能忽略不计。
- 此外，核函数写干净一点，LDG的指令占比尽可能的高，通过warp切换发射LDG互相掩盖延迟，才能更接近极限。

- TuringT4论文里说: 与访存延迟相比，浮点加消耗的时间可以忽略不计。
  - 但我对指令流水线的理解不深，理解不了这句话。虽然从结果上观察，确实如此，但不懂怎么解释。
  - 在TLP的作用下，latency是不会影响BW的，或者说影响会被掩盖。
  - 那scheduler在LDG的发射过程中插入算术指令的发射，不是照样会延后LDG的发射吗。
  - 除非TLP不能让schduler一直发LDG。

- 此外，float2可以一定程度上提高BW。
## 步骤
~~~bash
# float
nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/L2cacheBW_float L2cacheBW_float.cu
# float2
nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/L2cacheBW_float2 L2cacheBW_float2.cu
~~~



# L2cacheBW_float_YHs
> 这份代码直接copy自：https://github.com/Yinghan-Li/YHs_Sample 作为参考