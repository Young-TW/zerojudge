#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long dp[10000] = {0};
    dp[0] = 1;
    
    for (int i = 1; i <= 21; ++i) {
        int coin = i * i * i;
        for (int j = coin; j < 10000; ++j) {
            dp[j] += dp[j - coin];
        }
    }
    
    int n;
    while (cin >> n) {
        cout << dp[n] << "\n";
    }
    
    return 0;
}
