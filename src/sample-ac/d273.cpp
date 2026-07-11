#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (cin >> T) {
        while (T--) {
            string s;
            cin >> s;
            int n = s.length();
            vector<int> dp(n + 1, n);
            dp[0] = 0;
            
            for (int i = 0; i < n; ++i) {
                // Odd length palindromes
                for (int j = 0; i - j >= 0 && i + j < n && s[i - j] == s[i + j]; ++j) {
                    dp[i + j + 1] = min(dp[i + j + 1], dp[i - j] + 1);
                }
                // Even length palindromes
                for (int j = 0; i - j >= 0 && i + 1 + j < n && s[i - j] == s[i + 1 + j]; ++j) {
                    dp[i + j + 2] = min(dp[i + j + 2], dp[i - j] + 1);
                }
            }
            
            cout << dp[n] << "\n";
        }
    }
    
    return 0;
}
