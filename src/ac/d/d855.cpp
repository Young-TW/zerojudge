#include <iostream>
#include <cstring>

using namespace std;

int dp[205][10];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int i = 1; i <= 200; ++i) {
        for (int j = 1; j <= 6; ++j) {
            if (i >= j) {
                dp[i][j] = dp[i - 1][j - 1] + dp[i - j][j];
            }
        }
    }
    
    int n, k;
    while (cin >> n >> k) {
        cout << dp[n][k] << "\n";
    }
    
    return 0;
}
