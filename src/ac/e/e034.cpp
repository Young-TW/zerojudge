#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int grid[55][55];
int dp[2][55][55];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> grid[i][j];
            }
        }
        
        memset(dp, -0x3f, sizeof(dp));
        dp[0][0][0] = grid[0][0];
        
        int max_k = 2 * (n - 1);
        for (int k = 1; k <= max_k; ++k) {
            int cur = k % 2;
            int prev = 1 - cur;
            memset(dp[cur], -0x3f, sizeof(dp[cur]));
            
            for (int i1 = 0; i1 < n; ++i1) {
                int j1 = k - i1;
                if (j1 < 0 || j1 >= n) continue;
                for (int i2 = 0; i2 < n; ++i2) {
                    int j2 = k - i2;
                    if (j2 < 0 || j2 >= n) continue;
                    
                    int val = -0x3f3f3f3f;
                    if (i1 > 0 && i2 > 0) val = max(val, dp[prev][i1 - 1][i2 - 1]);
                    if (i1 > 0 && j2 > 0) val = max(val, dp[prev][i1 - 1][i2]);
                    if (j1 > 0 && i2 > 0) val = max(val, dp[prev][i1][i2 - 1]);
                    if (j1 > 0 && j2 > 0) val = max(val, dp[prev][i1][i2]);
                    
                    if (val < -1000000000) continue;
                    
                    if (i1 == i2) {
                        val += grid[i1][j1];
                    } else {
                        val += grid[i1][j1] + grid[i2][j2];
                    }
                    dp[cur][i1][i2] = val;
                }
            }
        }
        
        cout << dp[max_k % 2][n - 1][n - 1] << "\n";
    }
    
    return 0;
}
