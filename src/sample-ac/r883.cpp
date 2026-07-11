#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, K;
    while (cin >> N >> K) {
        vector<long long> dp(K + 1, 1);
        vector<long long> next_dp(K + 1, 0);
        
        for (int i = 2; i <= N; ++i) {
            long long total = 0;
            for (int j = 1; j <= K; ++j) {
                total = (total + dp[j]) % MOD;
            }
            
            for (int j = 1; j <= K; ++j) {
                long long val = total;
                for (int m = 2 * j; m <= K; m += j) {
                    val = (val - dp[m] + MOD) % MOD;
                }
                next_dp[j] = val;
            }
            
            swap(dp, next_dp);
        }
        
        long long ans = 0;
        for (int j = 1; j <= K; ++j) {
            ans = (ans + dp[j]) % MOD;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
