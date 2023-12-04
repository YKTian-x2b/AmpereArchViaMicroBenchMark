// regsPerBlock和regsPerSM都是65536 这些是指32bit的寄存器
// 为了用满SM的3*16个warp，限制一个block是32*16个线程 一个SM启动三个block，那么一个block先用1/4regs 256*64个
// 如果是连续两个regs存一个double的话，一个block处理256*32个，就是16个double每线程?

// smemPerBlock是49152=128*128*3 smemPerSM是102400=32*32*100 一个SM要启动三个block，一个block就用1/3smemPerSM 128*256字节
// 限制一个block是32*16个线程 就是64字节每线程 就是8个double每线程


nvcc -l cublas -L /usr/local/cuda/lib64 -l nvToolsExt -o res/02_res 02_Transpose.cu

nsys profile --stats=true -f true -o profileRes/02_proRes res/02_res

nvcc -l cublas -L /usr/local/cuda/lib64 -l nvToolsExt -w -o res/00_res 00_cuTest.cu && res/00_res


nvcc -l cublas -L /usr/local/cuda/lib64 -l nvToolsExt -w -DVALID -o res/04_res 04_MySimpleDGEMM_v9Tov11.cu && res/04_res



nvcc test_cuda3.cu -o res/test_cuda3 -gencode=arch=compute_86,code=\"sm_86,compute_86\"  -gencode=arch=compute_52,code=\"sm_52,compute_52\" -gencode=arch=compute_75,code=\"sm_75,compute_75\"


cuobjdump -ptx res/test_cuda3 > res/test_cuda3.ptx
cuobjdump -sass res/test_cuda3 > res/test_cuda3.sass

r68 - r75   
r76 - r91
r12 - r23   3
r28 - r31   1
r40 - r51   3
r56 - r59   1




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