#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 計算將區間 [l, r] 塗成目標顏色所需的最少筆數
// 使用動態規劃 (Interval DP)
// dp[l][r] 表示完成區間 [l, r] 所需的最少筆數
int solve_case() {
    int N, M;
    if (!(cin >> N >> M)) return 0;
    
    vector<int> c(N);
    for (int i = 0; i < N; ++i) {
        cin >> c[i];
    }

    // dp[i][j] 代表塗好區間 [i, j] 所需的最小次數
    vector<vector<int>> dp(N, vector<int>(N, 0));

    // 初始化：長度為 1 的區間，只需要 1 次
    for (int i = 0; i < N; ++i) {
        dp[i][i] = 1;
    }

    // len 為區間長度，從 2 到 N
    for (int len = 2; len <= N; ++len) {
        // i 為區間起點
        for (int i = 0; i <= N - len; ++i) {
            int j = i + len - 1; // 區間終點
            
            // 預設策略：先塗好 [i, j-1]，再單獨塗 c[j]
            // 或者先塗 c[i]，再塗好 [i+1, j]
            // 這裡採用標準轉移：dp[i][j] = dp[i][j-1] + 1
            dp[i][j] = dp[i][j-1] + 1;

            // 嘗試尋找 k，使得 c[k] == c[j] 且 i <= k < j
            // 如果 c[k] == c[j]，則可以在塗 c[k] 所屬的那一筆時，順便延伸到 j
            // 此時成本為 dp[i][k] + dp[k+1][j-1]
            // 解釋：
            // 1. dp[i][k]：處理 [i, k]，假設最後一筆是顏色 c[k] (等於 c[j])
            // 2. dp[k+1][j-1]：處理中間這段，這段的顏色會被覆蓋或獨立處理
            // 3. 因為 c[k] == c[j]，原本塗 c[k] 的那一筆可以向右延伸到 j，不需要額外增加次數
            for (int k = i; k < j; ++k) {
                if (c[k] == c[j]) {
                    int cost = dp[i][k] + ( (k + 1 <= j - 1) ? dp[k+1][j-1] : 0 );
                    if (cost < dp[i][j]) {
                        dp[i][j] = cost;
                    }
                }
            }
        }
    }

    return dp[0][N-1];
}

int main() {
    // 加速 I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (cin >> T) {
        while (T--) {
            cout << solve_case() << "\n";
        }
    }
    
    return 0;
}
