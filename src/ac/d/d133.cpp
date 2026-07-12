#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAXN = 30000;
    long long dp[MAXN + 1] = {0};
    int coins[] = {1, 5, 10, 25, 50};
    
    dp[0] = 1;
    for (int c : coins) {
        for (int i = c; i <= MAXN; ++i) {
            dp[i] += dp[i - c];
        }
    }

    int n;
    while (cin >> n) {
        if (dp[n] == 1) {
            cout << "There is only 1 way to produce " << n << " cents change.\n";
        } else {
            cout << "There are " << dp[n] << " ways to produce " << n << " cents change.\n";
        }
    }

    return 0;
}
