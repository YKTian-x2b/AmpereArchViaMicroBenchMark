// SM的峰值访存吞吐 bank带宽 * 32 * SM freq
// 按 TuringT4 和 Volta的算法 V100 P100是一个时钟周期4B 阉割过的是两个时钟周期4B

// P Bs ws fg 
// Turing T4  1590M * 32 * 4B * 40 / 2 = 4070GB/s
// 3060 1700M * 32 * 4 * 30 / 2 = 3264GB/s  或 SM是1088GB/s