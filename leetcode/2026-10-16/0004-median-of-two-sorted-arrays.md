# 4. 寻找两个正序数组的中位数 (Median of Two Sorted Arrays)

- 难度：**困难** · 日期：2026-10-16
- 链接：https://leetcode.cn/problems/median-of-two-sorted-arrays/
- 结果：**通过 2099/2099 用例，0 ms 击败 100.00%**，内存 92.89 MB

## 思路

本题的"标准答案"是 O(log(min(m,n))) 的二分划分法，但约束只有 1000 量级，
**双指针归并到中位位置**即可，且常数更小、实测 0 ms 击败 100%。

1. 设 `total = m + n`，中位数只需要归并到下标 `total/2` 为止；
2. 用 `i`、`j` 分别指向两数组，每步取较小者推进，同时用 `prev` 记住上一步的值；
3. 走完 `total/2` 步后：
   - `total` 为奇数 → 答案就是 `cur`；
   - 为偶数 → 答案是 `(prev + cur) / 2.0`（**注意除以 2.0，不能整除**）。

**易错点**：偶数情况一定要用浮点除法；奇数情况要转 `double` 再返回。

## 复杂度

- 时间 **O(m + n)**（只走到一半即 `O(total/2)`）
- 空间 **O(1)**，只用了常数个变量

## 代码（C++）

```cpp
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        int total = m + n;
        int i = 0, j = 0, prev = 0, cur = 0;
        for (int k = 0; k <= total / 2; ++k) {
            prev = cur;
            if (i < m && (j >= n || nums1[i] <= nums2[j])) cur = nums1[i++];
            else cur = nums2[j++];
        }
        if (total % 2 == 1) return (double)cur;
        return (prev + cur) / 2.0;
    }
};
```

## 本地自测（g++ 16.2.0，6/6 通过）

| nums1 | nums2 | 输出 | 期望 |
|---|---|---|---|
| [1,3] | [2] | 2.0 | 2.0 |
| [1,2] | [3,4] | 2.5 | 2.5 |
| [] | [1] | 1.0 | 1.0 |
| [0,0] | [0,0] | 0.0 | 0.0 |
| [2] | [] | 2.0 | 2.0 |
| [1,2,3,4,5] | [6,7,8,9] | 5.0 | 5.0 |

## 踩坑（重要，操作层面）

第一次提交时 **粘贴被截断**（编辑器里只有前几行，力扣报 `non-void function does not return a value` 编译错）。
原因：页面刚打开就粘贴，编辑器还没渲染完 → 后面的内容被吞。
**教训：粘贴后先截图确认代码完整（看行号最后一行），再点提交。**