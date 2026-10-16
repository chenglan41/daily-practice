# 6. Z 字形变换 (Zigzag Conversion)

- 难度：中等 · 日期：2026-10-16
- 链接：https://leetcode.cn/problems/zigzag-conversion/
- 结果：**通过 1158/1158 用例，3 ms 击败 80.51%**，内存 13.26 MB 击败 72.94%

## 思路（按行收集，O(n)）

不需要真的建二维网格——**每个字符属于哪一行是确定的**：

1. 开 `numRows` 个字符串（每行一个）；
2. 用 `cur` 记当前行、`dir` 记方向（+1 向下 / -1 向上）：
   - 碰到 `cur == 0` → 方向改为向下；
   - 碰到 `cur == numRows - 1` → 方向改为向上；
3. 依次把字符追加到 `rows[cur]`，最后把各行**顺序拼接**。

**边界**：`numRows == 1` 或 `n <= numRows` 时 Z 字形不产生折返，答案就是原串，直接返回
（同时避免了越界）。

## 复杂度

- 时间 **O(n)**，每个字符只处理一次
- 空间 **O(n)**，答案本身

## 代码（C++）

```cpp
class Solution {
public:
    string convert(string s, int numRows) {
        int n = s.size();
        if (numRows <= 1 || n <= numRows) return s;
        vector<string> rows(numRows);
        int cur = 0, dir = 1;
        for (char c : s) {
            rows[cur] += c;
            if (cur == 0) dir = 1;
            else if (cur == numRows - 1) dir = -1;
            cur += dir;
        }
        string res;
        res.reserve(n);
        for (auto& r : rows) res += r;
        return res;
    }
};
```

## 本地验证（g++ 16.2.0，507/507 通过）

| 输入 | numRows | 输出 |
|---|---|---|
| `PAYPALISHIRING` | 3 | `PAHNAPLSIIGYIR` |
| `PAYPALISHIRING` | 4 | `PINALSIGYAHRPI` |
| `ABC` | 2 | `ACB` |
| `ABCD` | 2 | `ACBD` |
| `AB` | 3 | `AB`（n ≤ numRows 边界） |

另加 **500 组随机串**与**独立的二维网格模拟实现**对拍，并校验字符多重集不变，全部一致。

> 注意：对拍基准不能直接用同一个"逐行收集"算法（那是抄自己），所以暴力版是**真的建二维网格逐格摆放**再逐行读出——这样才有校验意义。