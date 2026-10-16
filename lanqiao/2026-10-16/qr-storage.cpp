// 2. 二维码存储 — 蓝桥云课 2026-10-16
// 每行按 32 bit 对齐，1 Byte = 8 bit，答案 = n * (((m+31)/32)*32/8)
// 提交结果：通过率 100%（20/20 用例），1 ms / 1668 KB
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
