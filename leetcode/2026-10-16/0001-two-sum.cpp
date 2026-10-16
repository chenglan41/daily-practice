// 1. 两数之和 (Two Sum) — 2026-10-16
// 思路：一次遍历 + 哈希表；对每个数查补数，命中即返回，否则存入
// 时间 O(n) / 空间 O(n)
#include <vector>
#include <unordered_map>
using namespace std;

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
