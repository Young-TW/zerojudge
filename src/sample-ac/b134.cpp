#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<long long> a(2 * n + 1);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            a[i + n] = a[i];
        }
        a[2 * n] = a[0];
        
        vector<vector<long long>> dp(2 * n, vector<long long>(2 * n, 0));
        
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i + len - 1 < 2 * n; ++i) {
                int j = i + len - 1;
                for (int k = i; k < j; ++k) {
                    dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j] + a[i] * a[k + 1] * a[j + 1]);
                }
            }
        }
        
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            ans = max(ans, dp[i][i + n - 1]);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
