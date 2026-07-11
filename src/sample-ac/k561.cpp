#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int q, w, n, m;
    while (cin >> q >> w >> n >> m) {
        if (q == 0 && w == 0 && n == 0 && m == 0) break;

        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(n, 0)));

        for (int a = 0; a < m; ++a) {
            for (int b = 0; b < n; ++b) {
                for (int c = 0; c < n; ++c) {
                    if (a == 0 && b == 0 && c == 0) {
                        dp[a][b][c] = q % w;
                    } else if (a == 0 && b == 0) {
                        dp[a][b][c] = (c * q + c) % w;
                    } else if (a == 0) {
                        dp[a][b][c] = (b * q + c) % w;
                    } else if (b == 0 && c == 0) {
                        dp[a][b][c] = dp[a-1][n-1][n-1];
                    } else if (b == 0) {
                        long long val = 1;
                        if (c > 0) val = (val * dp[a][b][c-1]) % w;
                        val = (val * dp[a][n-1][c-1]) % w;
                        val = (val * dp[a-1][b][c]) % w;
                        dp[a][b][c] = (val + q) % w;
                    } else if (c == 0) {
                        long long val = 1;
                        val = (val * dp[a][b-1][c]) % w;
                        val = (val * dp[a-1][b][c]) % w;
                        dp[a][b][c] = (val + q) % w;
                    } else {
                        long long val = 1;
                        val = (val * dp[a-1][b][c]) % w;
                        val = (val * dp[a][b-1][c]) % w;
                        val = (val * dp[a][b][c-1]) % w;
                        dp[a][b][c] = (val + q) % w;
                    }
                }
            }
        }

        cout << dp[m-1][n-1][n-1] << '\n';
    }

    return 0;
}
