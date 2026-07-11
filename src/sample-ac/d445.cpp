#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long dp[800] = {0};
    long long ans[40] = {0};
    dp[0] = 1;
    
    for (int j = 1; j <= 39; ++j) {
        for (int i = 780; i >= j; --i) {
            dp[i] += dp[i - j];
        }
        int sum = j * (j + 1) / 2;
        if (sum % 2 == 0) {
            ans[j] = dp[sum / 2] / 2;
        } else {
            ans[j] = 0;
        }
    }
    
    int n;
    while (cin >> n) {
        cout << ans[n] << "\n";
    }
    
    return 0;
}
