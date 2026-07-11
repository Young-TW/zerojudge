#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    while (cin >> t) {
        int n;
        cin >> n;
        vector<long long> P(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> P[i];
        }

        const long long NEG_INF = -1e18;
        // dp[j][0]: 進行了 j 筆交易，當前不持倉的最大利潤
        // dp[j][1]: 進行了 j 筆交易，當前持倉的最大利潤
        vector<vector<long long>> dp(t + 1, vector<long long>(2, NEG_INF));
        dp[0][0] = 0;

        for (int i = 1; i <= n; ++i) {
            vector<vector<long long>> next_dp(t + 1, vector<long long>(2, NEG_INF));
            for (int j = 0; j <= t; ++j) {
                // 維持不持倉狀態
                next_dp[j][0] = dp[j][0];
                // 賣出股票，完成一筆交易
                if (j > 0 && dp[j - 1][1] != NEG_INF) {
                    next_dp[j][0] = max(next_dp[j][0], dp[j - 1][1] + P[i] * 999);
                }
                
                // 維持持倉狀態
                next_dp[j][1] = dp[j][1];
                // 買入股票
                if (dp[j][0] != NEG_INF) {
                    next_dp[j][1] = max(next_dp[j][1], dp[j][0] - P[i] * 1001);
                }
            }
            dp = next_dp;
        }

        long long ans = 0;
        for (int j = 0; j <= t; ++j) {
            if (dp[j][0] > ans) {
                ans = dp[j][0];
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
