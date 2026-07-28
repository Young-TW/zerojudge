#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int H, W;
    while (cin >> H >> W) {
        vector<vector<long long>> val(H + 1);
        for (int r = 1; r <= H; ++r) {
            int cols = (r % 2 == 1) ? W : W + 1;
            val[r].resize(cols + 1);
            for (int c = 1; c <= cols; ++c) {
                cin >> val[r][c];
            }
        }

        const long long INF = 1e18;
        vector<vector<long long>> dp(H + 1);
        for (int r = 1; r <= H; ++r) {
            int cols = (r % 2 == 1) ? W : W + 1;
            dp[r].assign(cols + 1, INF);
        }

        for (int r = 1; r <= H; ++r) {
            dp[r][1] = val[r][1];
        }

        int max_c = W + 1;
        for (int c = 1; c <= max_c; ++c) {
            // 偶數列先處理
            for (int r = 1; r <= H; ++r) {
                if (r % 2 == 0) {
                    int cols = W + 1;
                    if (c <= cols) {
                        long long cur = dp[r][c];
                        if (cur == INF) continue;
                        // 右
                        if (c < cols) {
                            dp[r][c + 1] = min(dp[r][c + 1], cur + val[r][c + 1]);
                        }
                        // 右上 (r-1, c)
                        if (r > 1 && c <= W) {
                            dp[r - 1][c] = min(dp[r - 1][c], cur + val[r - 1][c]);
                        }
                        // 右下 (r+1, c)
                        if (r < H && c <= W) {
                            dp[r + 1][c] = min(dp[r + 1][c], cur + val[r + 1][c]);
                        }
                    }
                }
            }
            // 奇數列後處理
            for (int r = 1; r <= H; ++r) {
                if (r % 2 == 1) {
                    int cols = W;
                    if (c <= cols) {
                        long long cur = dp[r][c];
                        if (cur == INF) continue;
                        // 右
                        if (c < cols) {
                            dp[r][c + 1] = min(dp[r][c + 1], cur + val[r][c + 1]);
                        }
                        // 右上 (r-1, c+1)
                        if (r > 1) {
                            dp[r - 1][c + 1] = min(dp[r - 1][c + 1], cur + val[r - 1][c + 1]);
                        }
                        // 右下 (r+1, c+1)
                        if (r < H) {
                            dp[r + 1][c + 1] = min(dp[r + 1][c + 1], cur + val[r + 1][c + 1]);
                        }
                    }
                }
            }
        }

        long long ans = INF;
        for (int r = 1; r <= H; ++r) {
            if (r % 2 == 1) {
                ans = min(ans, dp[r][W]);
            } else {
                ans = min(ans, dp[r][W + 1]);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
