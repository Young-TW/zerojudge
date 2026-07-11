#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> dp(n, vector<int>(m, 0));
        int max_side = 0;
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int val;
                cin >> val;
                if (val == 1) {
                    if (i == 0 || j == 0) {
                        dp[i][j] = 1;
                    } else {
                        dp[i][j] = min(dp[i-1][j], min(dp[i][j-1], dp[i-1][j-1])) + 1;
                    }
                    if (dp[i][j] > max_side) {
                        max_side = dp[i][j];
                    }
                }
            }
        }
        cout << max_side << "\n";
    }
    
    return 0;
}
