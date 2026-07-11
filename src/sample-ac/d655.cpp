#include <iostream>

using namespace std;

const int MAX = 20000;
int dp[MAX];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int coins[] = {1, 5, 10, 30, 50, 70, 100, 110, 500, 1000};
    dp[0] = 0;
    for (int i = 1; i < MAX; ++i) {
        dp[i] = dp[i - 1] + 1;
        for (int c : coins) {
            if (i >= c) {
                if (dp[i - c] + 1 < dp[i]) {
                    dp[i] = dp[i - c] + 1;
                }
            }
        }
    }

    int t;
    while (cin >> t) {
        while (t--) {
            long long n;
            if (!(cin >> n)) return 0;
            if (n < MAX) {
                cout << dp[n] << "\n";
            } else {
                long long k = (n - 10000) / 1000;
                long long r = n - k * 1000;
                cout << dp[r] + k << "\n";
            }
        }
    }
    return 0;
}
