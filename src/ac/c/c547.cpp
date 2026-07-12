#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    const int MOD = 1000000007;
    const int MAX_N = 10000;
    
    vector<long long> dp(MAX_N + 1);
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= MAX_N; ++i) {
        dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;
    }
    
    int n;
    while (cin >> n) {
        cout << dp[n] << "\n";
    }
    
    return 0;
}
