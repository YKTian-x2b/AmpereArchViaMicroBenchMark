# MicroBenchmark For Ampere

## 1. 现有结果

### 1.1 Storage hierarchy

|               | Size                    | Bandwidth                       | BW理论上限            | Latency    |
| ------------- | ----------------------- | ------------------------------- | --------------------- | ---------- |
| L0_I-Cache    | 待补充                  | -                               | -                     | -          |
| L1_D-Cache    | 128/120/112/96/64/28 KB | 65.3 B per cycle per SM（存疑） | 64 B per cycle per SM | 33 cycles  |
| L2_D-Cache    | 3 MB                    | 1276.2 GB/s                     | -                     | 219 cycles |
| Shared Memory | 100/64/32/16/8/0 KB     | 194.2 GB/s per SM               | 217.6 GB/s per SM     | 23 cycles  |
| Global Memory | 6 GB                    | 327.2 GB/s                      | 336 GB/s              | 待补充     |

### 1.2 Register Bank

- 2 way Bank
- 

### 1.3 Warp Schedule

- scheduler_Idx = warp_Idx % 4; 测试不到 



## 2. 一些结论

### 2.1 论文Ampere Mem

A100的latency：
Global Mem: 290 Cycles (HBM2 for A100)
L2 cache: 200 Cycles
L1 cache: 33 Cycles
SMem(ld/st): 23/19 Cycles



### 2.2 知乎YHs

GDDR 内存延迟一般 450~550 cycle，HBM 内存 350~400 cycle，smem 约 20~30 cycle



### 2.3 Turingas 代码结果

/*
>>> SASS Level Memory Latency Result
        > Global    Memory    Latency     =  882 cycle
        > Global    TLB       Latency     =  515 cycle
        > Global    L2-Cache  Latency     =  212 cycle
        > Global    L1-Cache  Latency     =  212 cycle
        > Shared    Memory    Latency     =   24 cycle
        > Constant  Memory    Latency     =  658 cycle
        > Constant  L2-Cache  Latency     =   59 cycle
        > Constant  L1-Cache  Latency     =    4 cycle
> */



全局内存的latency分
TLB未命中 & L2cache未命中 & L1cache未命中
TLB命中 & L2cache未命中 & L1cache未命中
TLB命中 & L2cache命中 & L1未cache命中
TLB命中 & L2cache命中 & L1cache命中



## 3. 编译指令

// cuda驱动函数 编译
nvcc -L /usr/local/cuda/lib64 -l cuda -o res/test test.cu



// CuAssembler
nvcc --keep -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I/opt/kaiProjects/GEMM_kai/Utils -L /usr/local/cuda/lib64 -l cuda -o res/regBankTest regBankTest.cu 

nvcc --dryrun -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I/opt/kaiProjects/GEMM_kai/Utils -L /usr/local/cuda/lib64 -l cuda -o res/regBankTest regBankTest.cu 2>&1 | tee regBankTest_dryrun.sh

cuasm --bin2asm regBankTest.sm_86.cubin -o regBankTest.sm_86.cuasm

/// mod regBankTest.sm_86.cuasm

mv -f regBankTest.sm_86.cubin regBankTest.old.sm_86.cubin && cuasm --asm2bin regBankTest.sm_86.cuasm -o regBankTest.sm_86.cubin



// 将cubin汇编为二进制
bash regBankTest_dryrun_drv.sh

//
rm -rf !(regBankTest.cu) && mkdir res

// test_regBank.py
cuasm --asm2bin save/regBankTest.sm_86_my.cuasm -o regBankTest.sm_86.cubin

