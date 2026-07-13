#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int dp[1005][1005] = {0};
    dp[0][0] = 1;
    for (int i = 1; i <= 1000; ++i) {
        for (int j = 1; j <= i; ++j) {
            if (j % 2 == 0) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                dp[i][j] = (dp[i-1][j] + dp[i-1][j-1]) % 2;
            }
        }
    }

    int t;
    if (cin >> t) {
        bool first = true;
        while (t--) {
            int n, m;
            cin >> n >> m;
            if (!first) {
                cout << "\n";
            }
            cout << dp[n][m] << "\n";
            first = false;
        }
    }

    return 0;
}
