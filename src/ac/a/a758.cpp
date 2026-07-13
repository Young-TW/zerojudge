#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;
int W, N;
int T[55];
int dp[55][2005];
long long cnt[55][2005];
int suffix_sum[55];

void dfs(int idx, int current_weight, int current_count, vector<int>& path) {
    if (current_weight == W) {
        if (current_count == dp[0][W]) {
            for (size_t i = 0; i < path.size(); ++i) {
                if (i > 0) cout << " ";
                cout << path[i];
            }
            cout << "\n";
        }
        return;
    }
    if (idx == N) return;
    if (current_weight + suffix_sum[idx] < W) return;

    if (current_weight + T[idx] <= W) {
        if (current_count + 1 + dp[idx + 1][W - current_weight - T[idx]] <= dp[0][W]) {
            path.push_back(T[idx]);
            dfs(idx + 1, current_weight + T[idx], current_count + 1, path);
            path.pop_back();
        }
    }

    if (current_count + dp[idx + 1][W - current_weight] <= dp[0][W]) {
        dfs(idx + 1, current_weight, current_count, path);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> W >> N) {
        for (int i = 0; i < N; ++i) {
            cin >> T[i];
        }
        sort(T, T + N);
        
        suffix_sum[N] = 0;
        for (int i = N - 1; i >= 0; --i) {
            suffix_sum[i] = suffix_sum[i + 1] + T[i];
        }

        for (int i = 0; i <= N; ++i) {
            for (int w = 0; w <= W; ++w) {
                dp[i][w] = INF;
                cnt[i][w] = 0;
            }
        }
        dp[N][0] = 0;
        cnt[N][0] = 1;

        for (int i = N - 1; i >= 0; --i) {
            for (int w = 0; w <= W; ++w) {
                dp[i][w] = dp[i + 1][w];
                cnt[i][w] = cnt[i + 1][w];

                if (w >= T[i] && dp[i + 1][w - T[i]] != INF) {
                    if (dp[i + 1][w - T[i]] + 1 < dp[i][w]) {
                        dp[i][w] = dp[i + 1][w - T[i]] + 1;
                        cnt[i][w] = cnt[i + 1][w - T[i]];
                    } else if (dp[i + 1][w - T[i]] + 1 == dp[i][w]) {
                        cnt[i][w] += cnt[i + 1][w - T[i]];
                    }
                }
            }
        }

        cout << dp[0][W] << " " << cnt[0][W] << "\n";
        vector<int> path;
        dfs(0, 0, 0, path);
    }
    return 0;
}
