// 5. 最长回文子串 (Longest Palindromic Substring) — 2026-10-16
// 思路：中心扩展。每个位置分别以 (i,i) 和 (i,i+1) 为中心向两侧扩，记录最长
// 时间 O(n^2) / 空间 O(1)
// 提交结果：通过 144/144 用例，7 ms 击败 91.94%
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