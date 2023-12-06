// Global Mem的理论访存峰值吞吐 = mem frequency*DDR_factor * 总线宽度 
// GDDR和DDR的区别在于 图形内存的有效带宽是DDR的4倍。 DDR就是双倍数据速率。
// 这里nvidia-smi 查出来的 mem freq 就是已经乘4了
// 3060     7000M * 2 * 192/8  = 336 GB/s
// turing t4  5000M * 2 * 256/8  = 320GB/s