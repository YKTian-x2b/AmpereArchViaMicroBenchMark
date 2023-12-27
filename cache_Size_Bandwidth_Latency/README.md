# 要点

- 最重要的就是ldg中的几个modifier的含义：https://docs.nvidia.com/cuda/parallel-thread-execution/index.html#cache-operators
  - 还有一个nc：https://docs.nvidia.com/cuda/parallel-thread-execution/index.html#data-movement-and-conversion-instructions-ld-global-nc
  - 我的理解是 nc就是在ca/cg/cs基础上，提示编译器该变量是只读的，会可选的放在只读缓存中，完全放弃一致性保证机制。
  - 但这里的只读缓存与 L1Cache和纹理缓存的关系，我不是太懂。是说在L1开辟一段只读区还是就指纹理缓存？
- 根据具体的测试内容选择 GRD_SIZE和BLK_SIZE：
  - 比如
- 根据具体的测试内容选择 计时方式
  - 
- 




# 其他
~~~C++
// Performs barrier synchronization and communication within a CTA. Each CTA instance has sixteen barriers numbered 0..15.
asm volatile ("bar.sync 0;");
// : "memory" 表示停止任何在生成PTX期间执行的asm()语句内存优化
asm volatile ("mov.u32 %0, %%clock;" : "=r"(stop) :: "memory");
~~~


- 如果CUDA C/C++汇编成SASS不能准确的表达含义或者杂余指令太多就尝试PTX。
- 如果PTX也不能表达，就只能直接改SASS了。
