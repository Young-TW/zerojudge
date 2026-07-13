#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m, n;
    while (cin >> m >> n) {
        vector<vector<long long>> matrix(m, vector<long long>(n));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> matrix[i][j];
            }
        }

        vector<vector<long long>> dp(m, vector<long long>(n));
        vector<vector<int>> next_row(m, vector<int>(n));

        for (int i = 0; i < m; ++i) {
            dp[i][n - 1] = matrix[i][n - 1];
            next_row[i][n - 1] = -1;
        }

        for (int j = n - 2; j >= 0; --j) {
            for (int i = 0; i < m; ++i) {
                int candidates[3] = {(i - 1 + m) % m, i, (i + 1) % m};
                sort(candidates, candidates + 3);
                
                int best_r = candidates[0];
                long long best_val = dp[candidates[0]][j + 1];
                
                for (int k = 1; k < 3; ++k) {
                    if (dp[candidates[k]][j + 1] < best_val) {
                        best_val = dp[candidates[k]][j + 1];
                        best_r = candidates[k];
                    }
                }
                
                dp[i][j] = matrix[i][j] + best_val;
                next_row[i][j] = best_r;
            }
        }

        long long min_weight = dp[0][0];
        int start_row = 0;
        for (int i = 1; i < m; ++i) {
            if (dp[i][0] < min_weight) {
                min_weight = dp[i][0];
                start_row = i;
            }
        }

        cout << start_row + 1;
        int curr_row = start_row;
        for (int j = 0; j < n - 1; ++j) {
            curr_row = next_row[curr_row][j];
            cout << " " << curr_row + 1;
        }
        cout << "\n" << min_weight << "\n";
    }

    return 0;
}
