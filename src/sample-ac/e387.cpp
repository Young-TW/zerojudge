#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <array>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n) {
        vector<double> x(n), y(n);
        for (int i = 0; i < n; ++i) {
            cin >> x[i] >> y[i];
        }

        vector<vector<double>> dist(n, vector<double>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dist[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
            }
        }

        vector<vector<int>> masks(n + 1);
        for (int i = 0; i < (1 << n); ++i) {
            masks[__builtin_popcount(i)].push_back(i);
        }

        vector<int> id(1 << n);
        vector<vector<array<double, 20>>> dp(2);

        dp[0].resize(masks[1].size());
        for (int i = 0; i < masks[1].size(); ++i) {
            int mask = masks[1][i];
            id[mask] = i;
            array<double, 20> arr;
            arr.fill(1e18);
            for (int j = 0; j < n; ++j) {
                if (mask == (1 << j)) {
                    arr[j] = 0.0;
                }
            }
            dp[0][i] = arr;
        }

        for (int k = 1; k < n; ++k) {
            int cur = (k - 1) & 1;
            int nxt = k & 1;
            dp[nxt].clear();
            dp[nxt].reserve(masks[k + 1].size());

            for (int mask : masks[k + 1]) {
                id[mask] = dp[nxt].size();
                array<double, 20> arr;
                arr.fill(1e18);
                dp[nxt].push_back(arr);
            }

            for (int mask : masks[k]) {
                int u = id[mask];
                for (int i = 0; i < n; ++i) {
                    if (dp[cur][u][i] < 1e17) {
                        for (int j = 0; j < n; ++j) {
                            if (!(mask & (1 << j))) {
                                int next_mask = mask | (1 << j);
                                int v = id[next_mask];
                                if (dp[cur][u][i] + dist[i][j] < dp[nxt][v][j]) {
                                    dp[nxt][v][j] = dp[cur][u][i] + dist[i][j];
                                }
                            }
                        }
                    }
                }
            }
        }

        int last = (n - 1) & 1;
        double ans = 1e18;
        for (int mask : masks[n]) {
            int u = id[mask];
            for (int i = 0; i < n; ++i) {
                if (dp[last][u][i] < ans) {
                    ans = dp[last][u][i];
                }
            }
        }

        cout << fixed << setprecision(2) << ans << "\n";
    }

    return 0;
}
