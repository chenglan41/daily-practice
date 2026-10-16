# 3. 无重复字符的最长子串 (Longest Substring Without Repeating Characters)

- 难度：中等 · 日期：2026-10-16
- 链接：https://leetcode.cn/problems/longest-substring-without-repeating-characters/
- 结果：**通过 1036/1036 用例，8 ms 击败 87.96%**，内存 18.16 MB

## 思路

**滑动窗口**：维护窗口 `[start, i]`，保证窗口内没有重复字符。

1. `last[c]` 记录字符 `c` **上一次出现的下标**（初值 -1）；
2. 遍历到位置 `i` 的字符 `c` 时，若 `last[c] >= start`（说明重复字符落在**当前窗口内**），
   就把左界 `start` 跳到 `last[c] + 1`；
3. 更新 `last[c] = i`，用 `i - start + 1` 更新答案。

**关键点**：判断条件必须写 `last[c] >= start`，而不是 `last[c] != -1`。
若写成后者，像 `abba` 这种会把窗口往回缩（`last['a']=0` 在窗口外，不该影响左界）。

## 复杂度

- 时间 **O(n)**：每个字符只被访问一次，`start` 只增不减
- 空间 **O(1)**：字符集固定（这里按 ASCII 128 开数组）

## 代码（C++）

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> last(128, -1);
        int best = 0, start = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            unsigned char c = (unsigned char)s[i];
            if (last[c] >= start) start = last[c] + 1;
            last[c] = i;
            best = max(best, i - start + 1);
        }
        return best;
    }
};
```

## 本地自测（g++ 16.2.0，8/8 通过）

| 输入 | 输出 | 输入 | 输出 |
|---|---|---|---|
| `abcabcbb` | 3 | `dvdf` | 3 |
| `bbbbb` | 1 | `abba` | 2 |
| `pwwkew` | 3 | `" "`（空格） | 1 |
| `""` | 0 | `au` | 2 |

## 踩坑记录（本地编译）

本地测试文件里 **`using namespace std;` 必须写在 `#include "sol.cpp"` 之前**，
否则解答里的 `string`/`vector` 找不到（力扣评测环境自带该 using，本地要自己补）。