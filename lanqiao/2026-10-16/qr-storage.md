# 2. 二维码存储（蓝桥杯 → 蓝桥云课）

- 题目：[lanqiao.cn/problems/21590](https://www.lanqiao.cn/problems/21590/learning/)
- 日期：2026-10-16
- 语言：C++ (g++17)
- 结果：**通过率 100%，20/20 测试用例通过，1 ms / 1668 KB**

## 题意

一张二维码是 `n × m` 的黑白模块矩阵，按行优先存储，每个模块占 **1 bit**（0 白 / 1 黑）。
但硬件要求：**每一行占用的空间必须是 32 bit 的整数倍**；若 `m` 不是 32 的倍数，
本行末尾补 0 补齐到不小于 `m` 的 32 的倍数（补齐位只算本行，下一行不能复用）。
求存储整张二维码最少需要多少**字节**（1 Byte = 8 bit）。

## 思路

每行实际占用位数：`rowBits = ceil(m / 32) * 32 = ((m + 31) / 32) * 32`
每行字节数：`rowBytes = rowBits / 8 = ((m + 31) / 32) * 4`
答案：`n * rowBytes`

用整数除法即可完成向上取整，无需浮点；`n`、`m` 用 `long long` 防溢出。

## 代码（C++）

```cpp
#include <iostream>
using namespace std;
int main()
{
    long long n, m;
    if (!(cin >> n >> m)) return 0;
    long long rowBits = ((m + 31) / 32) * 32;   // 每行按 32 bit 对齐
    long long rowBytes = rowBits / 8;           // 1 Byte = 8 bit
    cout << n * rowBytes << endl;
    return 0;
}
```

## 本地自测（g++ 16.2.0）

| 输入 | 输出 | 说明 |
|---|---|---|
| `2 10` | `8` | 题目样例 ✅（10 → 32 bit = 4 B，两行 8 B） |
| `1 32` | `4` | 恰好 32 bit = 4 B，不补齐 |
| `1 33` | `8` | 33 → 补齐到 64 bit = 8 B |
| `3 1` | `12` | 1 → 32 bit = 4 B，三行 12 B |
