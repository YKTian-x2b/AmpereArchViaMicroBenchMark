# 要点

- 最重要的就是ldg中的几个modifier的含义：https://docs.nvidia.com/cuda/parallel-thread-execution/index.html#cache-operators
  - 还有一个nc：https://docs.nvidia.com/cuda/parallel-thread-execution/index.html#data-movement-and-conversion-instructions-ld-global-nc
  - 我的理解是 ca要求驱动保证grid间的L1缓存一致性，但grid内的L1缓存一致性并不保证。nc就是提示编译器该变量是只读的，会可选的放在只读缓存中，也不做一致性的保证。
- 根据具体的测试内容选择 GRD_SIZE和BLK_SIZE：
  - 比如
- 根据具体的测试内容选择 计时方式
  - 
- 





