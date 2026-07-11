#include <iostream>
#include <string>
#include <cstring>

using namespace std;

const int MOD = 998244353;

int dp[205][2];
int next_dp[205][2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        int m = s.length();
        long long n_mod = 0;
        for (char c : s) {
            n_mod = (n_mod * 2 + (c - '0')) % MOD;
        }
        
        long long ans = 0;
        for (int k = 1; k <= m; ++k) {
            for (int c = 0; c < k; ++c) {
                dp[c][0] = dp[c][1] = 0;
            }
            dp[0][1] = 1;
            
            for (int i = 0; i < m; ++i) {
                for (int c = 0; c < k; ++c) {
                    next_dp[c][0] = next_dp[c][1] = 0;
                }
                int limit = s[i] - '0';
                for (int c = 0; c < k; ++c) {
                    for (int t = 0; t < 2; ++t) {
                        if (!dp[c][t]) continue;
                        for (int d = 0; d <= 1; ++d) {
                            if (t == 1 && d > limit) continue;
                            int nt = (t == 1 && d == limit) ? 1 : 0;
                            int nc = d == 1 ? c + 1 : 0;
                            if (nc >= k) continue;
                            next_dp[nc][nt] = (next_dp[nc][nt] + dp[c][t]) % MOD;
                        }
                    }
                }
                for (int c = 0; c < k; ++c) {
                    dp[c][0] = next_dp[c][0];
                    dp[c][1] = next_dp[c][1];
                }
            }
            
            long long C_k = 0;
            for (int c = 0; c < k; ++c) {
                for (int t = 0; t < 2; ++t) {
                    C_k = (C_k + dp[c][t]) % MOD;
                }
            }
            C_k = (C_k - 1 + MOD) % MOD;
            
            long long cnt_ge_k = (n_mod - C_k + MOD) % MOD;
            ans = (ans + cnt_ge_k) % MOD;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
