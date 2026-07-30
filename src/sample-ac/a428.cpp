#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

int N, M;
double K;
vector<int> S;
vector<double> C;
vector<double> powK;
vector<vector<int>> children;
vector<vector<vector<double>>> dp;

void dfs(int u) {
    dp[u].assign(1, vector<double>(N + 1, -1e18));
    for (int d = 1; d <= N; d++) {
        dp[u][0][d] = C[u] * powK[d];
    }

    int cur_size = 0;

    for (int v : children[u]) {
        dfs(v);
        int child_size = dp[v].size() - 1;

        vector<vector<double>> next_dp(cur_size + child_size + 2, vector<double>(N + 1, -1e18));

        for (int cu = 0; cu <= cur_size; cu++) {
            for (int d = 1; d <= N; d++) {
                if (dp[u][cu][d] < -1e17) continue;

                for (int cv = 0; cv <= child_size; cv++) {
                    if (d + 1 <= N) {
                        if (dp[v][cv][d + 1] > -1e17) {
                            next_dp[cu + cv][d] = max(next_dp[cu + cv][d], dp[u][cu][d] + dp[v][cv][d + 1]);
                        }
                    }
                    if (dp[v][cv][1] > -1e17) {
                        next_dp[cu + cv + 1][d] = max(next_dp[cu + cv + 1][d], dp[u][cu][d] + dp[v][cv][1]);
                    }
                }
            }
        }

        dp[u].swap(next_dp);
        cur_size += child_size + 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(2);

    while (cin >> N >> M >> K) {
        S.assign(N + 1, 0);
        C.assign(N + 1, 0.0);
        children.assign(N + 1, vector<int>());
        dp.assign(N + 1, vector<vector<double>>());

        for (int i = 1; i <= N; i++) {
            cin >> S[i];
        }
        for (int i = 1; i <= N; i++) {
            cin >> C[i];
        }

        powK.assign(N + 1, 1.0);
        for (int i = 1; i <= N; i++) {
            powK[i] = powK[i - 1] * K;
        }

        for (int i = 2; i <= N; i++) {
            children[S[i]].push_back(i);
        }

        dfs(1);

        double ans = -1e18;
        for (int d = 1; d <= N; d++) {
            double sum = 0.0;
            for (int i = 2; i <= N; i++) {
                sum += C[i] * powK[d];
            }
            for (int c = 0; c < dp[1].size(); c++) {
                if (c > M) continue;
                if (dp[1][c][d] > -1e17) {
                    ans = max(ans, dp[1][c][d] + sum);
                }
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
