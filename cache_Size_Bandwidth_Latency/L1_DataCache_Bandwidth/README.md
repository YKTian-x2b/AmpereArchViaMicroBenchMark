# L1cacheBW_myDefine
## 结论
- float: L1 Data cache Bandwidth is  63.5629 Bytes per cycle per SM
- float2: L1 Data cache Bandwidth is  124.652 Bytes per cycle per SM
## 思路
- 按 Volta 论文里的观点，L1_D-Cache的理论访存峰值吞吐应该是： 每个SM的LSU数量 \* 每LSU每cycle能加载的字节数。
- 从 TuringT4 的数据表反推：每LSU每clock能加载4B；假设Ampere也这样，算出来理论值是 4\*4\*4 = 64B
- 那就是保证所有线程跑在一个SM上，拉满线程数（即启动一个1024线程的Block），做多次ldg_ca，获取实际吞吐。
- 为了保证数据都是从L1_D-Cache里拿到的 且接近峰值，需要在实际运行前做一次warmup，kernel里做L1填充。
- 但用LDG.E.64(float2)发现上限是128B，可能每LSU每clock能加载8B？这样16个LSU每clock就能加载一次过L1内存事务。
- 我暂时不懂为什么LDG.E不能让L1和SMem的访存达到峰值，但LDG.E.64可以。
- 结合L1_DataCache_Latency 连续两次内存事务的延迟只是比一次稍长一些，感觉要长脑子了。。。
## 步骤
~~~bash
nvcc -gencode=arch=compute_86,code=\"sm_86,compute_86\" -I../../Utils -L /usr/local/cuda/lib64 -l cuda -o res/L1cacheBW_myDefine L1cacheBW_myDefine.cu
~~~