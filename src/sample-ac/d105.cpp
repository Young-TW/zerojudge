#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> dp(m + 1, vector<int>(n, 0));
        dp[0][0] = 1;
        
        for (int i = 1; i <= m; ++i) {
            for (int j = 0; j < n; ++j) {
                int left = (j - 1 + n) % n;
                int right = (j + 1) % n;
                dp[i][j] = dp[i - 1][left] + dp[i - 1][right];
            }
        }
        
        cout << dp[m][0] << "\n";
    }
    
    return 0;
}
