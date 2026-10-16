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
