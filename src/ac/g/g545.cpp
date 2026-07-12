#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        string s;
        cin >> s;
        
        vector<long long> dp(n + 2, 0);
        dp[0] = 1;
        
        for (int i = 0; i < n; ++i) {
            vector<long long> next_dp(n + 2, 0);
            for (int j = 0; j <= i; ++j) {
                if (dp[j] == 0) continue;
                if (s[i] == '[' || s[i] == '?') {
                    if (j + 1 <= n) {
                        next_dp[j + 1] = (next_dp[j + 1] + dp[j]) % MOD;
                    }
                }
                if (s[i] == ']' || s[i] == '?') {
                    if (j - 1 >= 0) {
                        next_dp[j - 1] = (next_dp[j - 1] + dp[j]) % MOD;
                    }
                }
            }
            dp = next_dp;
        }
        
        cout << dp[0] << "\n";
    }
    
    return 0;
}
