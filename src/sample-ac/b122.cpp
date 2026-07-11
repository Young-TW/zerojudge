#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m, n;
    while (cin >> m >> n) {
        vector<vector<int>> grid(m, vector<int>(n));
        long long total_sum = 0;
        vector<long long> row_sum(m, 0);
        vector<long long> col_sum(n, 0);

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> grid[i][j];
                row_sum[i] += grid[i][j];
                col_sum[j] += grid[i][j];
                total_sum += grid[i][j];
            }
        }

        int ans_x = 0;
        long long current_sum = 0;
        for (int i = 0; i < m; ++i) {
            current_sum += row_sum[i];
            if (current_sum * 2 >= total_sum) {
                ans_x = i;
                break;
            }
        }

        int ans_y = 0;
        current_sum = 0;
        for (int j = 0; j < n; ++j) {
            current_sum += col_sum[j];
            if (current_sum * 2 >= total_sum) {
                ans_y = j;
                break;
            }
        }

        cout << ans_x + 1 << " " << ans_y + 1 << "\n";
    }
    
    return 0;
}
