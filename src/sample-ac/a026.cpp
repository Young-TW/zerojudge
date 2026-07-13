#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N, K;
    while (cin >> M >> N >> K) {
        vector<vector<int>> grid(M, vector<int>(N));
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> grid[i][j];
            }
        }

        vector<vector<int>> prefix(M + 1, vector<int>(N + 1, 0));
        for (int i = 1; i <= M; ++i) {
            for (int j = 1; j <= N; ++j) {
                prefix[i][j] = grid[i-1][j-1] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1];
            }
        }

        auto get_sum = [&](int x1, int y1, int x2, int y2) {
            return prefix[x2][y2] - prefix[x1][y2] - prefix[x2][y1] + prefix[x1][y1];
        };

        vector<vector<int>> sum(M, vector<int>(N, 0));
        for (int i = 0; i <= M - K; ++i) {
            for (int j = 0; j <= N - K; ++j) {
                sum[i][j] = get_sum(i, j, i + K, j + K);
            }
        }

        int max1 = 0, max_i1 = -1, max_j1 = -1;
        for (int i = 0; i <= M - K; ++i) {
            for (int j = 0; j <= N - K; ++j) {
                if (sum[i][j] > max1) {
                    max1 = sum[i][j];
                    max_i1 = i;
                    max_j1 = j;
                }
            }
        }

        int max2 = 0, max_i2 = -1, max_j2 = -1;
        for (int i = 0; i <= M - K; ++i) {
            for (int j = 0; j <= N - K; ++j) {
                if (i >= max_i1 - K + 1 && i <= max_i1 + K - 1 && j >= max_j1 - K + 1 && j <= max_j1 + K - 1) {
                    continue;
                }
                if (sum[i][j] > max2) {
                    max2 = sum[i][j];
                    max_i2 = i;
                    max_j2 = j;
                }
            }
        }

        int max3 = 0;
        for (int i = 0; i <= M - K; ++i) {
            for (int j = 0; j <= N - K; ++j) {
                if ((i >= max_i1 - K + 1 && i <= max_i1 + K - 1 && j >= max_j1 - K + 1 && j <= max_j1 + K - 1) ||
                    (i >= max_i2 - K + 1 && i <= max_i2 + K - 1 && j >= max_j2 - K + 1 && j <= max_j2 + K - 1)) {
                    continue;
                }
                if (sum[i][j] > max3) {
                    max3 = sum[i][j];
                }
            }
        }

        cout << max1 + max2 + max3 << '\n';
    }

    return 0;
}
