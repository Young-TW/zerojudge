#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long dp[55];
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i <= 50; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    int n;
    while (cin >> n) {
        if (n == 0) break;
        cout << dp[n] << "\n";
    }
    
    return 0;
}
