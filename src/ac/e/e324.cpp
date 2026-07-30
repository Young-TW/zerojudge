#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdint>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int INF = 0x3f3f3f3f;
    const long long INFLL = (1LL << 60);

    int n, m;
    bool firstOut = true;

    while (cin >> n >> m) {
        int N = 1 << n;
        int ALL = N - 1;

        vector<vector<int>> w(n, vector<int>(n, INF));
        for (int i = 0; i < m; ++i) {
            int u, v, c;
            cin >> u >> v >> c;
            --u; --v;
            if (u == v) continue;
            if (c < w[u][v]) {
                w[u][v] = c;
                w[v][u] = c;
            }
        }

        vector<vector<int>> mn(N, vector<int>(n, INF));
        for (int mask = 1; mask < N; ++mask) {
            int low = mask & -mask;
            int b = __builtin_ctz(low);
            int pre = mask ^ low;
            for (int v = 0; v < n; ++v) {
                mn[mask][v] = min(mn[pre][v], w[b][v]);
            }
        }

        vector<vector<long long>> dp(n + 1, vector<long long>(N, INFLL));
        for (int r = 0; r < n; ++r) dp[1][1 << r] = 0;

        for (int d = 2; d <= n; ++d) {
            for (int mask = 1; mask < N; ++mask) {
                if (__builtin_popcount(mask) < d) continue;

                long long best = INFLL;
                for (int S = (mask - 1) & mask; S; S = (S - 1) & mask) {
                    long long base = dp[d - 1][S];
                    if (base >= INFLL) continue;

                    int R = mask ^ S;
                    long long sum = 0;
                    bool ok = true;

                    for (int bits = R; bits; bits &= bits - 1) {
                        int v = __builtin_ctz(bits);
                        int c = mn[S][v];
                        if (c >= INF) {
                            ok = false;
                            break;
                        }
                        sum += c;
                    }

                    if (ok) {
                        long long val = base + 1LL * (d - 1) * sum;
                        if (val < best) best = val;
                    }
                }
                dp[d][mask] = best;
            }
        }

        long long ans = INFLL;
        for (int d = 1; d <= n; ++d) ans = min(ans, dp[d][ALL]);

        if (!firstOut) cout << '\n';
        firstOut = false;

        if (ans >= INFLL) cout << -1 << '\n';
        else cout << ans << '\n';
    }

    return 0;
}
