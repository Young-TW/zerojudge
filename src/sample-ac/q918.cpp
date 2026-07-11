#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;

int N;
vector<int> bit;

void init(int n) {
    N = n;
    bit.assign(N + 1, 0);
}

void add(int idx, int val) {
    val = (val % MOD + MOD) % MOD;
    for (; idx <= N; idx += idx & -idx) {
        bit[idx] = (bit[idx] + val) % MOD;
    }
}

int query(int idx) {
    int res = 0;
    for (; idx > 0; idx -= idx & -idx) {
        res = (res + bit[idx]) % MOD;
    }
    return res;
}

int range_query(int l, int r) {
    if (l > r) return 0;
    return (query(r) - query(l - 1) + MOD) % MOD;
}

int main() {
    int n, D, k, r;
    while (scanf("%d %d %d %d", &n, &D, &k, &r) == 4) {
        vector<int> h(n), x(n);
        vector<int> vals;
        for (int i = 0; i < n; ++i) {
            scanf("%d %d", &h[i], &x[i]);
            vals.push_back(x[i]);
        }
        
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        
        int m = vals.size();
        init(m);
        
        vector<int> house_by_h(n + 1);
        for (int i = 0; i < n; ++i) {
            house_by_h[h[i]] = i;
        }
        
        vector<int> dp(n, 0);
        int ptr = n;
        
        for (int cur_h = n; cur_h >= 1; --cur_h) {
            int i = house_by_h[cur_h];
            
            while (ptr > cur_h + k) {
                int j = house_by_h[ptr];
                int idx_j = lower_bound(vals.begin(), vals.end(), x[j]) - vals.begin() + 1;
                add(idx_j, -dp[j]);
                ptr--;
            }
            
            int L = lower_bound(vals.begin(), vals.end(), x[i] - r) - vals.begin() + 1;
            int R = upper_bound(vals.begin(), vals.end(), x[i] + r) - vals.begin();
            
            int sum = range_query(L, R);
            dp[i] = (1 + sum) % MOD;
            
            int idx_i = lower_bound(vals.begin(), vals.end(), x[i]) - vals.begin() + 1;
            add(idx_i, dp[i]);
        }
        
        vector<int> ans(n + 1);
        for (int i = 0; i < n; ++i) {
            ans[h[i]] = dp[i];
        }
        
        for (int i = 1; i <= n; ++i) {
            printf("%d%c", ans[i], (i == n ? '\n' : ' '));
        }
    }
    return 0;
}
