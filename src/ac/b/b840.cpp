#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    vector<vector<int>> grid(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
        }
    }

    int max_sum = 0;

    // 枚舉上邊界 row1
    for (int row1 = 0; row1 < N; ++row1) {
        vector<int> col_sum(N, 0);
        // 枚舉下邊界 row2
        for (int row2 = row1; row2 < N; ++row2) {
            // 更新當前 row1~row2 之間的行壓縮和
            for (int col = 0; col < N; ++col) {
                col_sum[col] += grid[row2][col];
            }

            // 對 col_sum 進行一維最大子陣列和 (Kadane's Algorithm)
            // 但允許空子陣列 (結果至少為 0)
            int current_sum = 0;
            for (int val : col_sum) {
                current_sum += val;
                if (current_sum < 0) {
                    current_sum = 0;
                }
                if (current_sum > max_sum) {
                    max_sum = current_sum;
                }
            }
        }
    }

    cout << max_sum << endl;

    return 0;
}
