#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<long long> p(n + 1);
        for (int i = 0; i <= n; i++) cin >> p[i];
        vector<vector<long long>> dp(n, vector<long long>(n, 0));
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                long long best = LLONG_MAX;
                for (int k = i; k < j; k++) {
                    long long cost = dp[i][k] + dp[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                    if (cost < best) best = cost;
                }
                dp[i][j] = best;
            }
        }
        cout << (n >= 1 ? dp[0][n - 1] : 0) << "\n";
    }
    return 0;
}
