#include <iostream>
#include <string>

using namespace std;

const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        long long dp[5] = {0, 0, 0, 0, 0};
        for (char ch : s) {
            if (ch == 'c') {
                dp[0] = (dp[0] + 1) % MOD;
            } else if (ch == '8') {
                dp[1] = (dp[1] + dp[0]) % MOD;
            } else if (ch == '7') {
                dp[2] = (dp[2] + dp[1]) % MOD;
            } else if (ch == '6') {
                dp[3] = (dp[3] + dp[2]) % MOD;
            } else if (ch == '3') {
                dp[4] = (dp[4] + dp[3]) % MOD;
            }
        }
        cout << dp[4] << "\n";
    }
    
    return 0;
}
