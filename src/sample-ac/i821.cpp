#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdint>

using namespace std;

const int MOD = 1000000007;
const int MAXN = 1000000;

int fact[MAXN + 1];
int inv_fact[MAXN + 1];
int inv[MAXN + 1];
int subset_sum[1 << 19]; // 524288

int modpow(int a, int e) {
    long long res = 1;
    long long cur = a;
    while (e > 0) {
        if (e & 1) res = res * cur % MOD;
        cur = cur * cur % MOD;
        e >>= 1;
    }
    return (int)res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Precompute factorials and inverses
    fact[0] = 1;
    for (int i = 1; i <= MAXN; ++i) {
        fact[i] = (long long)fact[i - 1] * i % MOD;
    }
    inv_fact[MAXN] = modpow(fact[MAXN], MOD - 2);
    for (int i = MAXN; i >= 1; --i) {
        inv_fact[i - 1] = (long long)inv_fact[i] * i % MOD;
    }
    inv[1] = 1;
    for (int i = 2; i <= MAXN; ++i) {
        inv[i] = MOD - (long long)(MOD / i) * inv[MOD % i] % MOD;
    }

    string s;
    while (cin >> s) {
        int n = s.size();
        int cnt[20] = {0};
        for (char c : s) {
            cnt[c - 'a']++;
        }
        int A = cnt[0];
        vector<int> others;
        others.reserve(19);
        for (int i = 1; i < 20; ++i) {
            if (cnt[i] > 0) others.push_back(cnt[i]);
        }
        int k = others.size();
        int num_masks = 1 << k;

        long long total_perms = fact[n];
        total_perms = total_perms * inv_fact[A] % MOD;
        for (int c : others) {
            total_perms = total_perms * inv_fact[c] % MOD;
        }

        subset_sum[0] = 0;
        for (int mask = 1; mask < num_masks; ++mask) {
            int lb = mask & -mask;
            int idx = __builtin_ctz(lb);
            subset_sum[mask] = subset_sum[mask ^ lb] + others[idx];
        }

        long long sum_subsets = 0;
        for (int mask = 0; mask < num_masks; ++mask) {
            int bits = __builtin_popcount(mask);
            int denom = A + subset_sum[mask];
            long long term = inv[denom];
            if (bits & 1) {
                sum_subsets -= term;
                if (sum_subsets < 0) sum_subsets += MOD;
            } else {
                sum_subsets += term;
                if (sum_subsets >= MOD) sum_subsets -= MOD;
            }
        }

        long long ans = total_perms * A % MOD * sum_subsets % MOD;
        cout << ans << '\n';
    }

    return 0;
}
