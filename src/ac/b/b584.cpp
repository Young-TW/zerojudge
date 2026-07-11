#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m;
    while (cin >> m && m) {
        vector<int> t(m);
        for (int i = 0; i < m; ++i) {
            cin >> t[i];
        }
        
        sort(t.begin(), t.end());
        
        vector<int> dp(m + 1, 0);
        if (m >= 1) dp[1] = t[0];
        if (m >= 2) dp[2] = t[1];
        if (m >= 3) dp[3] = t[0] + t[1] + t[2];
        
        for (int i = 4; i <= m; ++i) {
            int strategy1 = 2 * t[0] + t[i - 2] + t[i - 1];
            int strategy2 = t[0] + 2 * t[1] + t[i - 1];
            dp[i] = min(strategy1, strategy2) + dp[i - 2];
        }
        
        cout << dp[m] << "\n";
    }
    
    return 0;
}
