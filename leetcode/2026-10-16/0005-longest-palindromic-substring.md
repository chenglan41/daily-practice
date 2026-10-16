# 5. 最长回文子串 (Longest Palindromic Substring)

- 难度：中等 · 日期：2026-10-16
- 链接：https://leetcode.cn/problems/longest-palindromic-substring/
- 结果：**通过 144/144 用例，7 ms 击败 91.94%**，内存 9.25 MB 击败 81.85%

## 思路（中心扩展，O(n²)）

回文串的中心只有 `2n-1` 种可能：以某个字符为中心（**奇数**长度），或某两个字符之间（**偶数**长度）。

1. 对每个 `i`，分别调用 `expand(i, i)` 与 `expand(i, i+1)`；
2. `expand(l, r)` 向两侧扩到不匹配为止，此时回文长度为 `r - l - 1`，起点为 `l + 1`；
3. 全程记录最长的那一段，返回 `s.substr(start, maxLen)`。

**易错点**：长度公式是 `r - l - 1`（循环退出时 `l`、`r` 已经各多走了一步），
起点是 `l + 1`；单字符要初始化为长度 1（否则 `"a"` 会返回空串）。

> 另有 O(n) 的 Manacher 算法，但本题 n ≤ 1000，中心扩展常数更小、实测 7 ms 击败 91.94%。

## 代码（C++）

```cpp
class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        int start = 0, maxLen = 1;
        auto expand = [&](int l, int r) {
            while (l >= 0 && r < (int)s.size() && s[l] == s[r]) { --l; ++r; }
            int len = r - l - 1;
            if (len > maxLen) { maxLen = len; start = l + 1; }
        };
        for (int i = 0; i < (int)s.size(); ++i) {
            expand(i, i);
            expand(i, i + 1);
        }
        return s.substr(start, maxLen);
    }
};
```

## 本地自测（g++ 16.2.0，209/209 通过）

因为答案可能不唯一（如 `babad` 输出 `bab` 或 `aba` 都对），本地校验用的是
**"是回文 且 长度等于暴力求出的最大长度"**，而不是死比字符串：

| 输入 | 输出 | 最长 |
|---|---|---|
| `babad` | `bab` | 3 |
| `cbbd` | `bb` | 2 |
| `a` / `ac` / `""` | `a` / `a` / `""` | 1 / 1 / 0 |
| `aaaa` | `aaaa` | 4 |
| `forgeeksskeegfor` | `geeksskeeg` | 10 |
| `abacdfgdcaba` | `aba` | 3 |

外加 **200 组随机串与暴力对拍**，全部一致。