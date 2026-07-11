#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct BIT {
    int n;
    vector<long long> bit1, bit2;
    BIT(int n = 0) : n(n), bit1(n + 2, 0), bit2(n + 2, 0) {}
    void init(int n_) {
        n = n_;
        bit1.assign(n + 2, 0);
        bit2.assign(n + 2, 0);
    }
    void add(vector<long long>& bit, int idx, long long val) {
        for (; idx <= n; idx += idx & -idx) bit[idx] += val;
    }
    void range_add(int l, int r, long long v) {
        add(bit1, l, v);
        add(bit1, r + 1, -v);
        add(bit2, l, v * (l - 1));
        add(bit2, r + 1, -v * r);
    }
    long long prefix_sum(int idx) {
        long long sum1 = 0, sum2 = 0;
        for (int i = idx; i > 0; i -= i & -i) {
            sum1 += bit1[i];
            sum2 += bit2[i];
        }
        return sum1 * idx - sum2;
    }
    long long range_sum(int l, int r) {
        if (l > r) return 0;
        return prefix_sum(r) - prefix_sum(l - 1);
    }
};

struct SubQuery {
    int t, l, r, id, sign;
    bool operator<(const SubQuery& other) const {
        return t < other.t;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        vector<long long> A(n + 1);
        for (int i = 1; i <= n; ++i) cin >> A[i];
        vector<long long> preA(n + 1, 0);
        for (int i = 1; i <= n; ++i) preA[i] = preA[i - 1] + A[i];

        vector<int> op_l(m + 1), op_r(m + 1);
        vector<long long> op_v(m + 1);
        for (int i = 1; i <= m; ++i) {
            cin >> op_l[i] >> op_r[i] >> op_v[i];
        }

        int k;
        cin >> k;
        vector<long long> ans(k, 0);
        vector<SubQuery> subqs;
        subqs.reserve(2 * k);

        for (int i = 0; i < k; ++i) {
            int l, r, L, R;
            cin >> l >> r >> L >> R;
            ans[i] = preA[r] - preA[l - 1];
            subqs.push_back({R, l, r, i, 1});
            if (L > 1) subqs.push_back({L - 1, l, r, i, -1});
        }

        sort(subqs.begin(), subqs.end());

        BIT bit(n);
        size_t ptr = 0;
        for (int t = 1; t <= m; ++t) {
            bit.range_add(op_l[t], op_r[t], op_v[t]);
            while (ptr < subqs.size() && subqs[ptr].t == t) {
                long long val = bit.range_sum(subqs[ptr].l, subqs[ptr].r);
                ans[subqs[ptr].id] += subqs[ptr].sign * val;
                ++ptr;
            }
        }

        for (int i = 0; i < k; ++i) {
            cout << ans[i] << '\n';
        }
    }
    return 0;
}
