#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, K;
    while (cin >> N >> M >> K) {
        int OFFSET = N + M + K + 5;
        int size = 2 * OFFSET + 5;
        vector<vector<int>> sum(size, vector<int>(size, 0));

        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M; ++j) {
                int val;
                cin >> val;
                int U = i + j + OFFSET;
                int V = i - j + M + OFFSET;
                sum[U][V] = val;
            }
        }

        for (int i = 1; i < size; ++i) {
            for (int j = 1; j < size; ++j) {
                sum[i][j] += sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
            }
        }

        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M; ++j) {
                int U = i + j + OFFSET;
                int V = i - j + M + OFFSET;
                int r1 = U - K;
                int c1 = V - K;
                int r2 = U + K;
                int c2 = V + K;
                
                int ans = sum[r2][c2] - sum[r1-1][c2] - sum[r2][c1-1] + sum[r1-1][c1-1];
                cout << ans << (j == M ? "\n" : " ");
            }
        }
    }

    return 0;
}
