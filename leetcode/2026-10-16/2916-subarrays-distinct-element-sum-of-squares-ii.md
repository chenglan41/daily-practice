# 2916. 子数组不同元素数目的平方和 II（力扣「每日一题」2026-10-16）

- 难度：**困难** · 类型：**每日一题（打卡）**
- 链接：https://leetcode.cn/problems/subarrays-distinct-element-sum-of-squares-ii/
- 结果：**通过 542/542 用例**，470 ms，内存 145.43 MB；**完成每日打卡 +10 积分（连续打卡 1 天）**

## 题意

对 `nums` 的每个子数组，统计其**不同元素个数** `c`，求所有子数组 `c²` 之和（对 1e9+7 取模）。

## 思路（线段树 + 懒标记，O(n log n)）

固定右端点 `r`，记 `cnt[l]` = 子数组 `nums[l..r]` 的不同元素个数。
当 `r` 右移一位、当前值为 `x`，设 `x` 上次出现位置为 `pos`：

- 只有左端点 `l ∈ [pos+1, r]` 的子数组会**新增一个不同元素** ⇒ 对这段区间 `cnt` **区间 +1**；
- 于是「以 r 结尾的所有子数组的不同元素个数平方和」= `Σ_{l=0..r} cnt[l]²`。

维护 `S1 = Σcnt`、`S2 = Σcnt²`：对区间整体 +1 时
`S2 ← S2 + 2·S1 + len`，`S1 ← S1 + len`。用**带懒标记的线段树**同时维护这两个量即可。

把每个 `r` 的 `S2` 累加就是答案。

## 代码（C++，见同目录 .cpp）

关键片段：

```cpp
void apply(int node, int l, int r, long long v) {   // 区间整体 +v
    long long len = r - l + 1;
    sq[node] = (sq[node] + 2*v%MOD*sm[node]%MOD + v*v%MOD*(len%MOD)) % MOD;
    sm[node] = (sm[node] + v*(len%MOD)) % MOD;
    lz[node] += v;
}
// 主循环
for (int r = 0; r < n; ++r) {
    int pos = last.count(nums[r]) ? last[nums[r]] : -1;
    if (pos + 1 <= r) upd(1, 0, n-1, pos+1, r, 1);
    last[nums[r]] = r;
    ans = (ans + qry(1, 0, n-1, 0, r)) % MOD;      // 询问 [0,r] 的 Σcnt²
}
```

## 本地验证（g++ 16.2.0）

| 项目 | 结果 |
|---|---|
| 样例 `[1,2,1] → 15` | PASS |
| 样例 `[1,1] → 3` | PASS |
| **300 组随机小数组 与暴力对拍** | **全部一致** |
| 性能 n = 1e5 | 135 ms |

合计 302/302 通过后提交。