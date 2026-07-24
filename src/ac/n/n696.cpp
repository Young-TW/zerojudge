#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    while (cin >> n >> m && (n || m)) {
        vector<vector<int>> sum_y(n + 1, vector<int>(m + 1, 0));
        vector<vector<int>> sum_b(n + 1, vector<int>(m + 1, 0));
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                int val;
                cin >> val;
                sum_y[i][j] = sum_y[i][j - 1] + val;
            }
        }
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                int val;
                cin >> val;
                sum_b[i][j] = sum_b[i - 1][j] + val;
            }
        }
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                dp[i][j] = max(dp[i - 1][j] + sum_y[i][j], dp[i][j - 1] + sum_b[i][j]);
            }
        }
        
        cout << dp[n][m] << "\n";
    }
    
    return 0;
}
