#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long N;
    int X, Y;
    while (cin >> N >> X >> Y) {
        int M = 1 << Y;
        int FULL = M - 1;

        // cnt[r][mask]
        vector< vector<int> > sum(X, vector<int>(M, 0));

        for (long long i = 0; i < N; ++i) {
            int c;               // race (1‑based)
            cin >> c;
            int mask = 0;
            for (int j = 0; j < Y; ++j) {
                int b; cin >> b;
                if (b) mask |= (1 << j);
            }
            sum[c - 1][mask]++;          // store directly in sum, will be transformed later
        }

        // SOS DP for each race: sum[r][mask] = Σ_{sub ⊆ mask} cnt[r][sub]
        for (int r = 0; r < X; ++r) {
            for (int bit = 0; bit < Y; ++bit) {
                for (int mask = 0; mask < M; ++mask) {
                    if (mask & (1 << bit)) {
                        sum[r][mask] += sum[r][mask ^ (1 << bit)];
                    }
                }
            }
        }

        long long ans = 0;
        for (int S = 0; S < M; ++S) {
            long long prod = 1;
            int comp = FULL ^ S;               // masks allowed for this S
            for (int r = 0; r < X; ++r) {
                prod = (prod * (long long)sum[r][comp]) % MOD;
                if (prod == 0) break;
            }
            if (__builtin_popcount(S) & 1) {   // odd size -> subtract
                ans += MOD - prod;
                if (ans >= MOD) ans -= MOD;
            } else {                           // even size -> add
                ans += prod;
                if (ans >= MOD) ans -= MOD;
            }
        }
        cout << ans % MOD << '\n';
    }
    return 0;
}
