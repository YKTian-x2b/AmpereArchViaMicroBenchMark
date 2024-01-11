# warpScheduleTest_my
## 结论
- scheduler_Idx = warp_Idx % 4;
## 思路
- 如果FFMA要隔4个clock才能发射第二条，用TLP塞满FFMA port就需要4个warp。
- 选用有邻居依赖的背靠背FFMA（Y + S04），能比较清晰的观察到效果。
- 先给每个scheduler分配4个warp 4\*32\*4=512个线程，作为baseline
- 然后每轮递增1个warp，观察新增warp对初始warp造成的浮点性能影响

- 从结果'res/res_warpScheduleTest_my.txt'可以看出来, （warpIdx % 4）相同的线程束的CPI改变情况基本相同，说明这些warp调度到了同一个scheduler。
## 步骤
~~~bash
nvcc --keep --keep-dir midRes -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../Utils -L /usr/local/cuda/lib64 -l cuda -o res/warpScheduleTest_my warpScheduleTest_my.cu

cuasm --bin2asm midRes/warpScheduleTest_my.sm_86.cubin -o midRes/warpScheduleTest_my.sm_86.cuasm

cp midRes/warpScheduleTest_my.sm_86.cuasm res/warpScheduleTest_my.template.sm_86.cuasm && cp midRes/warpScheduleTest_my.sm_86.cuasm res/warpScheduleTest_my.origin.sm_86.cuasm
# 为了插入FFMA序列
// @CUASM_INSERT_MARKER_POS.

python3 test_warpSchedule_my.py
~~~



# warpScheduleTest_t4

## 结论
- TuringT4描述的 ***只启动两个活跃warp执行无邻居寄存器依赖FFMA序列，算浮点性能*** 的想法，我做不出来效果。



