#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m, n;
    while (cin >> m >> n) {
        vector<int> dp(n, 0);
        for (int i = 0; i < m; ++i) {
            vector<int> val(n);
            for (int j = 0; j < n; ++j) {
                cin >> val[j];
            }
            
            vector<int> R(n);
            R[0] = dp[0] + val[0];
            for (int j = 1; j < n; ++j) {
                R[j] = max(dp[j] + val[j], R[j - 1] + val[j]);
            }
            
            vector<int> L(n);
            L[n - 1] = dp[n - 1] + val[n - 1];
            for (int j = n - 2; j >= 0; --j) {
                L[j] = max(dp[j] + val[j], L[j + 1] + val[j]);
            }
            
            for (int j = 0; j < n; ++j) {
                dp[j] = max(L[j], R[j]);
            }
        }
        
        int ans = dp[0];
        for (int j = 1; j < n; ++j) {
            ans = max(ans, dp[j]);
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
