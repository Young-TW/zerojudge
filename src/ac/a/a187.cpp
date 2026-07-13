#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

const int MOD = 1024523;
const int MAXN = 505;

int dp[2][MAXN][MAXN];
char U[MAXN];
char D[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    while (cin >> n >> m) {
        string u_str, d_str;
        cin >> u_str >> d_str;
        
        // 反转字符串，下标从 1 开始
        for (int i = 0; i < n; ++i) U[i + 1] = u_str[n - 1 - i];
        for (int i = 0; i < m; ++i) D[i + 1] = d_str[m - 1 - i];
        
        memset(dp, 0, sizeof(dp));
        dp[0][0][0] = 1;
        
        for (int i = 0; i <= n; ++i) {
            int cur = i % 2;
            int nxt = 1 - cur;
            if (i > 0) memset(dp[nxt], 0, sizeof(dp[nxt]));
            for (int k = 0; k <= m; ++k) {
                int min_j = max(0, i + k - m);
                int max_j = min(n, i + k);
                for (int j = min_j; j <= max_j; ++j) {
                    if (!dp[cur][j][k]) continue;
                    int l = i + k - j;
                    int val = dp[cur][j][k];
                    
                    // 1. 第一个取上，第二个取上
                    if (i < n && j < n && U[i+1] == U[j+1]) {
                        dp[nxt][j+1][k] += val;
                        if (dp[nxt][j+1][k] >= MOD) dp[nxt][j+1][k] -= MOD;
                    }
                    // 2. 第一个取上，第二个取下
                    if (i < n && l < m && U[i+1] == D[l+1]) {
                        dp[nxt][j][k] += val;
                        if (dp[nxt][j][k] >= MOD) dp[nxt][j][k] -= MOD;
                    }
                    // 3. 第一个取下，第二个取上
                    if (k < m && j < n && D[k+1] == U[j+1]) {
                        dp[cur][j+1][k+1] += val;
                        if (dp[cur][j+1][k+1] >= MOD) dp[cur][j+1][k+1] -= MOD;
                    }
                    // 4. 第一个取下，第二个取下
                    if (k < m && l < m && D[k+1] == D[l+1]) {
                        dp[cur][j][k+1] += val;
                        if (dp[cur][j][k+1] >= MOD) dp[cur][j][k+1] -= MOD;
                    }
                }
            }
        }
        
        cout << dp[n % 2][n][m] << "\n";
    }
    return 0;
}
