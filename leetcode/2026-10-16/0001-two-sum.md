# 1. 两数之和 (Two Sum)

- 难度：简单
- 日期：2026-10-16
- 链接：https://leetcode.cn/problems/two-sum/

## 题目

给定一个整数数组 `nums` 和一个整数目标值 `target`，请你在该数组中找出**和为目标值** `target` 的那**两个**整数，
并返回它们的数组下标。你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。

## 思路

一次遍历 + 哈希表（空间换时间）：

1. 顺序扫描 `nums`，对当前元素 `v` 计算需要的补数 `need = target - v`；
2. 若 `need` 已在哈希表里，说明前面出现过，直接返回 `[该元素下标, 当前下标]`；
3. 否则把 `v -> i` 存入哈希表继续。

因为题目保证**恰好一个答案**，且要求不能重复使用同一元素，
"先查后存"的顺序天然避免了把自己和自己配对。

## 复杂度

- 时间复杂度：**O(n)**，每个元素只进出哈希表各一次
- 空间复杂度：**O(n)**，最坏情况下哈希表存 n 个元素

## 代码（C++）

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> pos;
        for (int i = 0; i < (int)nums.size(); ++i) {
            int need = target - nums[i];
            auto it = pos.find(need);
            if (it != pos.end()) return {it->second, i};
            pos[nums[i]] = i;
        }
        return {};
    }
};
```

## 手算验证

| 输入 | 输出 | 说明 |
|---|---|---|
| `nums=[2,7,11,15], target=9` | `[0,1]` | 2 + 7 = 9 |
| `nums=[3,2,4], target=6` | `[1,2]` | 2 + 4 = 6 |
| `nums=[3,3], target=6` | `[0,1]` | 两个 3，先查后存能正确取到两个不同下标 |
