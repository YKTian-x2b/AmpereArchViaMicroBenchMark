## warpScheduleTest_my

### 结论

- scheduler_Idx = warp_Idx % 4;

### 思路

- 如果FFMA要隔4个clock才能二次发射。用TLP塞满FFMA port就需要4个warp
- 先给每个scheduler分配4个warp 4\*32\*4=512个线程，作为baseline
- 然后每次递增1个warp，观察硬件不足的情况下，CPI的变化情况。

- 从结果'res/res_warpScheduleTest.txt'可以看出来, （warpIdx % 4）相同的线程束的CPI改变情况相同，说明调度到了同一个scheduler。
- 且 123000/5 和 99000/4 大致相等， 也能印证该结论

### 步骤
~~~bash
# warpScheduleTest_my.cu 编译得到中间结果 warpScheduleTest_my.cubin

# cubin 转 cuasm

# 计时代码中间的代码替换成 没有邻居依赖的FFMA序列

# cuasm 转 cubin 驱动运行修改cubin

~~~



## warpScheduleTest_t4

### 结论

- Turing T4描述的 只启动两个活跃warp算浮点性能 的想法，我做不出来效果。



