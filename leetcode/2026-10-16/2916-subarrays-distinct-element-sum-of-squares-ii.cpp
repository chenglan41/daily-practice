class Solution {
    static const long long MOD = 1000000007;
    vector<long long> sm, sq, lz;
    void apply(int node, int l, int r, long long v) {
        long long len = r - l + 1;
        sq[node] = (sq[node] + 2 * v % MOD * sm[node] % MOD + v * v % MOD * (len % MOD)) % MOD;
        sm[node] = (sm[node] + v * (len % MOD)) % MOD;
        lz[node] += v;
    }
    void push(int node, int l, int r) {
        if (lz[node] == 0 || l == r) return;
        int mid = (l + r) >> 1;
        apply(node << 1, l, mid, lz[node]);
        apply(node << 1 | 1, mid + 1, r, lz[node]);
        lz[node] = 0;
    }
    void upd(int node, int l, int r, int ql, int qr, long long v) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) { apply(node, l, r, v); return; }
        push(node, l, r);
        int mid = (l + r) >> 1;
        upd(node << 1, l, mid, ql, qr, v);
        upd(node << 1 | 1, mid + 1, r, ql, qr, v);
        sm[node] = (sm[node << 1] + sm[node << 1 | 1]) % MOD;
        sq[node] = (sq[node << 1] + sq[node << 1 | 1]) % MOD;
    }
    long long qry(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return sq[node];
        push(node, l, r);
        int mid = (l + r) >> 1;
        return (qry(node << 1, l, mid, ql, qr) + qry(node << 1 | 1, mid + 1, r, ql, qr)) % MOD;
    }
public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        sm.assign(4 * n + 4, 0);
        sq.assign(4 * n + 4, 0);
        lz.assign(4 * n + 4, 0);
        unordered_map<int, int> last;
        long long ans = 0;
        for (int r = 0; r < n; ++r) {
            auto it = last.find(nums[r]);
            int pos = (it == last.end()) ? -1 : it->second;
            if (pos + 1 <= r) upd(1, 0, n - 1, pos + 1, r, 1);
            last[nums[r]] = r;
            ans = (ans + qry(1, 0, n - 1, 0, r)) % MOD;
        }
        return (int)ans;
    }
};
