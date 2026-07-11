#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXV = 305;
const double INF = 1e18;

int n, m, v, e;
int c[2005];
int d[2005];
double k[2005];
double dist[MAXV][MAXV];
double dp[2005][2005][2];

void floyd() {
    for (int kk = 1; kk <= v; ++kk) {
        for (int i = 1; i <= v; ++i) {
            for (int j = 1; j <= v; ++j) {
                if (dist[i][kk] + dist[kk][j] < dist[i][j]) {
                    dist[i][j] = dist[i][kk] + dist[kk][j];
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m >> v >> e)) return 0;

    for (int i = 1; i <= n; ++i) cin >> c[i];
    for (int i = 1; i <= n; ++i) cin >> d[i];
    for (int i = 1; i <= n; ++i) cin >> k[i];

    for (int i = 1; i <= v; ++i) {
        for (int j = 1; j <= v; ++j) {
            if (i == j) dist[i][j] = 0.0;
            else dist[i][j] = 1e9;
        }
    }

    for (int i = 0; i < e; ++i) {
        int u, w, weight;
        cin >> u >> w >> weight;
        if (weight < dist[u][w]) {
            dist[u][w] = dist[w][u] = (double)weight;
        }
    }

    floyd();

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            dp[i][j][0] = INF;
            dp[i][j][1] = INF;
        }
    }

    dp[1][0][0] = 0.0;
    if (m >= 1) dp[1][1][1] = 0.0;

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= m; ++j) {
            // Current state: i-th class, not applied (state 0)
            if (dp[i][j][0] < INF) {
                // Next: not apply (state 0)
                double cost = dist[c[i]][c[i+1]];
                if (dp[i+1][j][0] > dp[i][j][0] + cost) {
                    dp[i+1][j][0] = dp[i][j][0] + cost;
                }
                // Next: apply (state 1)
                if (j + 1 <= m) {
                    double expected_cost = k[i+1] * dist[c[i]][d[i+1]] + (1.0 - k[i+1]) * dist[c[i]][c[i+1]];
                    if (dp[i+1][j+1][1] > dp[i][j][0] + expected_cost) {
                        dp[i+1][j+1][1] = dp[i][j][0] + expected_cost;
                    }
                }
            }

            // Current state: i-th class, applied (state 1)
            if (dp[i][j][1] < INF) {
                // Next: not apply (state 0)
                double expected_cost = k[i] * dist[d[i]][c[i+1]] + (1.0 - k[i]) * dist[c[i]][c[i+1]];
                if (dp[i+1][j][0] > dp[i][j][1] + expected_cost) {
                    dp[i+1][j][0] = dp[i][j][1] + expected_cost;
                }
                // Next: apply (state 1)
                if (j + 1 <= m) {
                    double cost = k[i] * k[i+1] * dist[d[i]][d[i+1]] +
                                  k[i] * (1.0 - k[i+1]) * dist[d[i]][c[i+1]] +
                                  (1.0 - k[i]) * k[i+1] * dist[c[i]][d[i+1]] +
                                  (1.0 - k[i]) * (1.0 - k[i+1]) * dist[c[i]][c[i+1]];
                    if (dp[i+1][j+1][1] > dp[i][j][1] + cost) {
                        dp[i+1][j+1][1] = dp[i][j][1] + cost;
                    }
                }
            }
        }
    }

    double ans = INF;
    for (int j = 0; j <= m; ++j) {
        if (dp[n][j][0] < ans) ans = dp[n][j][0];
        if (dp[n][j][1] < ans) ans = dp[n][j][1];
    }

    cout << fixed << setprecision(2) << ans << endl;

    return 0;
}
