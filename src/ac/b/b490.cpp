#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int grid[15][15];
int dp[15][15][15][15];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        if (n == 0) break;
        
        memset(grid, 0, sizeof(grid));
        memset(dp, 0, sizeof(dp));
        
        int x, y, val;
        while (cin >> x >> y >> val) {
            if (x == 0 && y == 0 && val == 0) break;
            grid[x][y] = val;
        }
        
        for (int i1 = 1; i1 <= n; ++i1) {
            for (int j1 = 1; j1 <= n; ++j1) {
                for (int i2 = 1; i2 <= n; ++i2) {
                    for (int j2 = 1; j2 <= n; ++j2) {
                        int max_prev = 0;
                        max_prev = max(max_prev, dp[i1-1][j1][i2-1][j2]);
                        max_prev = max(max_prev, dp[i1-1][j1][i2][j2-1]);
                        max_prev = max(max_prev, dp[i1][j1-1][i2-1][j2]);
                        max_prev = max(max_prev, dp[i1][j1-1][i2][j2-1]);
                        
                        if (i1 == i2 && j1 == j2) {
                            dp[i1][j1][i2][j2] = max_prev + grid[i1][j1];
                        } else {
                            dp[i1][j1][i2][j2] = max_prev + grid[i1][j1] + grid[i2][j2];
                        }
                    }
                }
            }
        }
        
        cout << dp[n][n][n][n] << "\n";
    }
    
    return 0;
}
