#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> grid(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> grid[i][j];
            }
        }

        vector<vector<int>> dp(n, vector<int>(m, 0));
        dp[0][0] = grid[0][0];

        for (int i = 1; i < n; ++i) {
            dp[i][0] = dp[i-1][0] + grid[i][0];
        }
        for (int j = 1; j < m; ++j) {
            dp[0][j] = dp[0][j-1] + grid[0][j];
        }

        for (int i = 1; i < n; ++i) {
            for (int j = 1; j < m; ++j) {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + grid[i][j];
            }
        }

        cout << dp[n-1][m-1] << '\n';
    }

    return 0;
}
