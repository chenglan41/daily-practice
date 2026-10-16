class Solution {
public:
    int myAtoi(string s) {
        int i = 0, n = s.size();
        while (i < n && s[i] == ' ') ++i;
        int sign = 1;
        if (i < n && (s[i] == '+' || s[i] == '-')) {
            if (s[i] == '-') sign = -1;
            ++i;
        }
        long long val = 0;
        const long long LIMIT = (sign == 1) ? 2147483647LL : 2147483648LL;
        while (i < n && s[i] >= '0' && s[i] <= '9') {
            val = val * 10 + (s[i] - '0');
            if (val > LIMIT) return (sign == 1) ? INT_MAX : INT_MIN;
            ++i;
        }
        return (int)(sign * val);
    }
};
