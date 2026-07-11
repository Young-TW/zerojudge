#include <iostream>
#include <algorithm>

using namespace std;

int dp[10005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m, n, t;
    while (cin >> m >> n >> t) {
        for (int i = 0; i <= t; ++i) {
            dp[i] = -1;
        }
        dp[0] = 0;
        for (int i = 1; i <= t; ++i) {
            if (i >= m && dp[i - m] != -1) {
                dp[i] = max(dp[i], dp[i - m] + 1);
            }
            if (i >= n && dp[i - n] != -1) {
                dp[i] = max(dp[i], dp[i - n] + 1);
            }
        }
        
        for (int i = t; i >= 0; --i) {
            if (dp[i] != -1) {
                if (i == t) {
                    cout << dp[i] << "\n";
                } else {
                    cout << dp[i] << " " << (t - i) << "\n";
                }
                break;
            }
        }
    }
    
    return 0;
}
