#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int dp[1005][1005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s1, s2;
    while (getline(cin, s1)) {
        if (!getline(cin, s2)) break;
        
        if (!s1.empty() && s1.back() == '\r') s1.pop_back();
        if (!s2.empty() && s2.back() == '\r') s2.pop_back();
        
        int n = s1.length();
        int m = s2.length();
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (s1[i-1] == s2[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        
        cout << dp[n][m] << "\n";
    }
    
    return 0;
}
