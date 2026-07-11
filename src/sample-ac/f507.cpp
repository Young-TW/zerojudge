#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int lenS, lenT;
    string S, T;
    
    while (cin >> lenS >> S >> lenT >> T) {
        int n = S.length();
        int m = T.length();
        
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = i;
        }
        for (int j = 0; j <= m; ++j) {
            dp[0][j] = j;
        }
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (S[i - 1] == T[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + 1});
                }
            }
        }
        
        cout << dp[n][m] << "\n";
    }
    
    return 0;
}
