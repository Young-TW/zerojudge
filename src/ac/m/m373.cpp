#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    while (cin >> n >> k) {
        vector<long long> dp(k + 1, 0);
        long long ans = 0;
        
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            for (int j = k; j >= 0; --j) {
                long long val = max(0LL, dp[j]) + x;
                if (j > 0 && x < 0) {
                    val = max(val, max(0LL, dp[j-1]));
                }
                dp[j] = val;
            }
            for (int j = 0; j <= k; ++j) {
                ans = max(ans, dp[j]);
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
