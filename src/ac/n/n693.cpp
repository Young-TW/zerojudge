#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k, m;
    while (cin >> n >> k >> m) {
        long long dp[55][55] = {0};
        dp[0][0] = 1;
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= k; ++j) {
                for (int w = 1; w <= m; ++w) {
                    if (i - w >= 0) {
                        dp[i][j] += dp[i - w][j - 1];
                    }
                }
            }
        }
        
        cout << dp[n][k] << "\n";
    }
    
    return 0;
}
