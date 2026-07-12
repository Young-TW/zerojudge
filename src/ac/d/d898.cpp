#include <iostream>
#include <cstring>

using namespace std;

long long dp[20][20][20];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    memset(dp, 0, sizeof(dp));
    dp[1][1][1] = 1;
    
    for (int n = 2; n <= 13; ++n) {
        for (int p = 1; p <= 13; ++p) {
            for (int r = 1; r <= 13; ++r) {
                dp[n][p][r] = dp[n-1][p-1][r] + dp[n-1][p][r-1] + dp[n-1][p][r] * (n - 2);
            }
        }
    }

    int T;
    if (cin >> T) {
        while (T--) {
            int n, p, r;
            cin >> n >> p >> r;
            if (n >= 1 && n <= 13 && p >= 1 && p <= 13 && r >= 1 && r <= 13) {
                cout << dp[n][p][r] << "\n";
            } else {
                cout << 0 << "\n";
            }
        }
    }
    
    return 0;
}
