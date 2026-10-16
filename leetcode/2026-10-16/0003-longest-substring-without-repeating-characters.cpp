// 3. 无重复字符的最长子串 (Longest Substring Without Repeating Characters) — 2026-10-16
// 思路：滑动窗口 + 记录每个字符最后出现位置；遇到窗口内的重复字符就把左界跳到其后一位
// 时间 O(n) / 空间 O(1)（字符集固定 128）
// 提交结果：通过 1036/1036 用例，8 ms 击败 87.96%
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