#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m, n;
    while (cin >> m >> n) {
        vector<vector<int>> val(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                cin >> val[i][j];
            }
        }
        
        // dp[i][k] 表示第一個人在第 i 行，第二個人在第 k 行時的最大好感度之和
        vector<vector<int>> dp(m + 1, vector<int>(m + 1, -1));
        dp[1][1] = 0; // 起點 (1,1) 好感度為 0
        
        for (int s = 2; s <= m + n; ++s) {
            vector<vector<int>> next_dp(m + 1, vector<int>(m + 1, -1));
            for (int i = 1; i <= m; ++i) {
                int j = s - i;
                if (j < 1 || j > n) continue;
                for (int k = 1; k <= m; ++k) {
                    int l = s - k;
                    if (l < 1 || l > n) continue;
                    
                    int max_prev = -1;
                    // 四種可能的上一個狀態
                    if (dp[i-1][k-1] != -1) max_prev = max(max_prev, dp[i-1][k-1]);
                    if (dp[i-1][k] != -1) max_prev = max(max_prev, dp[i-1][k]);
                    if (dp[i][k-1] != -1) max_prev = max(max_prev, dp[i][k-1]);
                    if (dp[i][k] != -1) max_prev = max(max_prev, dp[i][k]);
                        
                    if (max_prev != -1) {
                        if (i == k) {
                            // 兩人在同一個格子，只加一次
                            next_dp[i][k] = max_prev + val[i][j];
                        } else {
                            // 兩人在不同格子，加兩次
                            next_dp[i][k] = max_prev + val[i][j] + val[k][l];
                        }
                    }
                }
            }
            dp = next_dp;
        }
        
        cout << dp[m][m] << "\n";
    }
    
    return 0;
}
