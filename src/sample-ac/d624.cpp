#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m) {
        unsigned long long dp[100] = {0};
        dp[0] = 1;
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n + 1; ++j) {
                if (i - j >= 0) {
                    dp[i] += dp[i - j];
                }
            }
            if (i <= n) {
                dp[i] += 1;
            }
        }
        cout << dp[m] << "\n";
    }
    return 0;
}
