#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    long long m, p;
    while (cin >> n >> m >> p) {
        vector<long long> s(n), e(n);
        for (int i = 0; i < n; ++i) cin >> s[i];
        for (int i = 0; i < n; ++i) cin >> e[i];
        
        vector<long long> coords;
        coords.reserve(n + 1);
        coords.push_back(0);
        for (int i = 0; i < n; ++i) coords.push_back(e[i]);
        sort(coords.begin(), coords.end());
        coords.erase(unique(coords.begin(), coords.end()), coords.end());
        int K = coords.size();
        
        vector<pair<int, int>> buses;
        buses.reserve(n);
        for (int i = 0; i < n; ++i) {
            int e_idx = lower_bound(coords.begin(), coords.end(), e[i]) - coords.begin();
            int s_idx = lower_bound(coords.begin(), coords.end(), s[i]) - coords.begin();
            buses.emplace_back(e_idx, s_idx);
        }
        sort(buses.begin(), buses.end());
        
        vector<long long> bit(K + 1, 0);
        auto add = [&](int idx, long long val) {
            for (; idx <= K; idx += idx & -idx) {
                bit[idx] += val;
                if (bit[idx] >= p) bit[idx] -= p;
            }
        };
        auto query = [&](int idx) {
            long long res = 0;
            for (; idx > 0; idx -= idx & -idx) {
                res += bit[idx];
            }
            return res % p;
        };
        
        vector<long long> dp(K, 0);
        int idx0 = lower_bound(coords.begin(), coords.end(), 0) - coords.begin();
        add(idx0 + 1, 1 % p);
        dp[idx0] = 1 % p;
        
        size_t i = 0;
        while (i < buses.size()) {
            int cur_e_idx = buses[i].first;
            int R = cur_e_idx - 1;
            long long total = 0;
            size_t j = i;
            while (j < buses.size() && buses[j].first == cur_e_idx) {
                int L = buses[j].second;
                if (L <= R) {
                    long long sum = (query(R + 1) - query(L) + p) % p;
                    total += sum;
                }
                ++j;
            }
            total %= p;
            if (total != 0) {
                add(cur_e_idx + 1, total);
                dp[cur_e_idx] = (dp[cur_e_idx] + total) % p;
            }
            i = j;
        }
        
        long long ans = 0;
        auto it = lower_bound(coords.begin(), coords.end(), m);
        if (it != coords.end() && *it == m) {
            int idx_m = it - coords.begin();
            ans = dp[idx_m] % p;
        }
        cout << ans << '\n';
    }
    return 0;
}
