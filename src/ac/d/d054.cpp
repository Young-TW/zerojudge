#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long dp[41];
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 5;
    for (int i = 3; i <= 40; ++i) {
        dp[i] = dp[i - 1] + 4 * dp[i - 2] + 2 * dp[i - 3];
    }

    int t;
    while (cin >> t) {
        while (t--) {
            int n;
            cin >> n;
            cout << dp[n] << "\n";
        }
    }

    return 0;
}
