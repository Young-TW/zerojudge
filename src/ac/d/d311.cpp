#include <iostream>

using namespace std;

const int MOD = 1572869;
const int MAXN = 1005;

int dp[MAXN][MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    dp[0][0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        dp[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            dp[i][j] = (dp[i-1][j] + (long long)i * dp[i-1][j-1]) % MOD;
        }
    }

    int n, m;
    while (cin >> n >> m) {
        if (m > n) {
            cout << 0 << "\n";
        } else {
            cout << dp[n][m] << "\n";
        }
    }

    return 0;
}
