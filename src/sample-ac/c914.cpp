#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long dp[31];
    dp[0] = 1;
    dp[1] = 2;
    dp[2] = 7;
    for (int i = 3; i <= 30; ++i) {
        dp[i] = 3 * dp[i - 1] + dp[i - 2] - dp[i - 3];
    }
    
    int k;
    while (cin >> k) {
        while (k--) {
            int n;
            cin >> n;
            cout << dp[n] << "\n";
        }
    }
    
    return 0;
}
