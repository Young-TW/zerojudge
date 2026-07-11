#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    while (cin >> N) {
        long long maze[65][65][65];
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    cin >> maze[i][j][k];
                }
            }
        }

        long long dp[65][65][65];
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    if (i == 0 && j == 0 && k == 0) {
                        dp[i][j][k] = maze[i][j][k];
                    } else {
                        long long min_prev = 1e18;
                        if (i > 0) min_prev = min(min_prev, dp[i-1][j][k]);
                        if (j > 0) min_prev = min(min_prev, dp[i][j-1][k]);
                        if (k > 0) min_prev = min(min_prev, dp[i][j][k-1]);
                        dp[i][j][k] = maze[i][j][k] + min_prev;
                    }
                }
            }
        }

        cout << dp[N-1][N-1][N-1] << "\n";
    }

    return 0;
}
