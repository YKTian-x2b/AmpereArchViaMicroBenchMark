# MicroBenchmark For Ampere
> 写在最前面：部分代码和思路来自知乎 cloudcore 和 李少侠，详见参考。

## 1.3060(阉割版)测试结果
### Memory hierarchy
|               | Size                    | Bandwidth                       | BW理论上限            | Latency     |
| ------------- | ----------------------- | ------------------------------- | --------------------- | ----------- |
| L0_I-Cache    | 16KB                    | -                               | -                     | -           |
| L1_I-Cache    | 32KB                    | -                               | -                     | -           |
| L1_D-Cache    | 128/120/112/96/64/28 KB | 124.7B per cycle per SM         | 128B per cycle per SM | 33 cycles   |
| L2_D-Cache    | 3 MB                    | 1276.2 GB/s                     | -                     | 219 cycles  |
| Shared Memory | 100/64/32/16/8/0 KB     | 214.4 GB/s per SM               | 217.6 GB/s per SM     | 23 cycles   |
| Global Memory | 6 GB                    | 327.2 GB/s                      | 336 GB/s              | ~515 cycles |

### Register Bank
- 2_Bank
- Reuse

### Warp Schedule
- scheduler_Idx = warp_Idx % 4;




## 2. 运行和指令
### 如何运行
- 首先需要一个CuAssembler: https://github.com/cloudcores/CuAssembler
~~~python
# 将Utils/test_Common.py文件头部的CuAssembler位置（如下） 替换为您安装的位置
sys.path.append('/opt/kaiProjects/cuda_libs/CuAssembler-master/CuAsm')
~~~
- 然后从各个文件夹的README里获取具体的执行指令
### 公用的指令
~~~bash
# cuda驱动编译
nvcc -L /usr/local/cuda/lib64 -l cuda -o res/test test.cu


###### CuAssembler的使用 ###### 
# 核心思路是：把源cuda代码先按官方流程编译成cubin，然后用CuAssembler反汇编成能看能改的cuasm，改成想要的效果之后再把cuasm会变成cubin，最后用驱动api执行cubin。
# cuda->cubin
nvcc --keep --keep-dir midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/regBankTest regBankTest.cu 
# cubin->cuasm
cuasm --bin2asm midRes/regBankTest.sm_86.cubin -o midRes/regBankTest.sm_86.cuasm
## 手动修改regBankTest.sm_86.cuasm 或者 
python3 test_regBank.py
# cuasm->cubin
cuasm --asm2bin midRes/regBankTest.sm_86.cuasm -o midRes/regBankTest.sm_86.cubin
# 运行
res/regBankTest
##############################  


# 
nvidia-smi --query -d CLOCK
# 锁频 但是warning Setting applications clocks is not supported for GPU 00000000:01:00.0.
nvidia-smi -ac 7000,1702
~~~



## 3. 一些参考结论
### 3.1 论文Ampere Mem
- A100的latency：
  - Global Mem: 290 Cycles (HBM2 for A100)
  - L2 cache: 200 Cycles
  - L1 cache: 33 Cycles
  - SMem(ld/st): 23/19 Cycles
### 3.2 知乎YHs
- GDDR 内存延迟一般 450\~550 cycle，HBM 内存 350\~400 cycle，smem 约 20\~30 cycle
### 3.3 Turingas 代码结果
- SASS Level Memory Latency Result：
  - Global    Memory    Latency     =  882 cycle
  - Global    TLB       Latency     =  515 cycle
  - Global    L2-Cache  Latency     =  212 cycle
  - Global    L1-Cache  Latency     =  212 cycle
  - Shared    Memory    Latency     =   24 cycle
  - Constant  Memory    Latency     =  658 cycle
  - Constant  L2-Cache  Latency     =   59 cycle
  - Constant  L1-Cache  Latency     =    4 cycle



## 4.参考

> 知乎 cloudcore ！！！

- https://zhuanlan.zhihu.com/p/348234642
- https://github.com/cloudcores/CuAssembler
- CuAssembler 和 RegBank相关MB

> 知乎 李少侠 

- https://zhuanlan.zhihu.com/p/441146275
- https://github.com/Yinghan-Li/YHs_Sample
- 所有Mem相关MB

> 一些经典论文/白皮书/博客

- **Dissecting the NVidia Turing T4 GPU via Microbenchmarking**
- **Dissecting the Volta GPU Architecture through Microbenchmarking**
- Optimizing Batched Winograd Convolution on GPUs (Turingas)
- Dissecting the Ampere GPU Architecture through Microbenchmarking
- Demystifying the NVidia Ampere Architecture through Microbenchmarking and Instruction-level Analysis
- **Dissecting the GPU memory hierarchy through Microbenchmarking**
- GA102 Whitepaper
- Turing Whitepaper
