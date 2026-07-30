#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double k1, k2;
    int m, n;
    const int L = 100;
    const double INF = 1e100;

    cout << fixed << setprecision(1);
    while (cin >> k1 >> k2 >> m >> n) {
        // dp[i][len][cnt]
        static double dp[101][101][101];
        for (int i = 0; i <= m; ++i)
            for (int len = 0; len <= L; ++len)
                for (int cnt = 0; cnt <= n; ++cnt)
                    dp[i][len][cnt] = INF;
        dp[0][0][0] = 0.0;

        for (int i = 0; i < m; ++i) {
            for (int len = 0; len <= L; ++len) {
                for (int cnt = 0; cnt <= n; ++cnt) {
                    double cur = dp[i][len][cnt];
                    if (cur >= INF) continue;
                    // remaining north intervals = m - i
                    int remNorth = m - i;
                    // we need at least 1 length for each remaining north interval
                    int maxA = L - len - (remNorth - 1);
                    for (int a = 1; a <= maxA; ++a) {
                        // remaining south intervals = n - cnt
                        int remSouth = n - cnt;
                        // each remaining north interval needs at least 1 south interval
                        int maxT = min(a, remSouth - (remNorth - 1));
                        for (int t = 1; t <= maxT; ++t) {
                            int q = a / t;
                            int r = a % t;
                            double southCost = k2 * ( (t - r) * (double)q * q
                                                    + r * (double)(q + 1) * (q + 1) );
                            double northCost = k1 * (double)a * a;
                            double nd = cur + northCost + southCost;
                            int nl = len + a;
                            int nc = cnt + t;
                            if (dp[i + 1][nl][nc] > nd)
                                dp[i + 1][nl][nc] = nd;
                        }
                    }
                }
            }
        }

        double ans = dp[m][L][n];
        cout << ans << "\n";
    }
    return 0;
}
