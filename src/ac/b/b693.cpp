#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int A[16][16];
int B[16][16];
long long dp_arr[1 << 16];
long long new_dp_arr[1 << 16];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    long long M;
    while (cin >> N >> M) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> A[i][j] >> B[i][j];
            }
        }

        int size = 1 << N;
        long long *dp = dp_arr;
        long long *new_dp = new_dp_arr;

        fill(dp, dp + size, 0);
        dp[0] = 1;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                fill(new_dp, new_dp + size, 0);
                for (int mask = 0; mask < size; ++mask) {
                    if (dp[mask] == 0) continue;
                    for (int c = 0; c < 2; ++c) {
                        if (c == 1 && B[i][j] == A[i][j]) continue;
                        int col = (c == 0 ? A[i][j] : B[i][j]);
                        bool ok = true;
                        if (j > 0) {
                            int c_l = (mask >> (j - 1)) & 1;
                            int col_l = (c_l == 0 ? A[i][j - 1] : B[i][j - 1]);
                            if (col == col_l) ok = false;
                        }
                        if (i > 0 && ok) {
                            int c_u = (mask >> j) & 1;
                            int col_u = (c_u == 0 ? A[i - 1][j] : B[i - 1][j]);
                            if (col == col_u) ok = false;
                        }
                        if (ok) {
                            int new_mask = (mask & ~(1 << j)) | (c << j);
                            new_dp[new_mask] = (new_dp[new_mask] + dp[mask]) % M;
                        }
                    }
                }
                swap(dp, new_dp);
            }
        }

        long long ans = 0;
        for (int mask = 0; mask < size; ++mask) {
            ans = (ans + dp[mask]) % M;
        }
        cout << ans << "\n";
    }

    return 0;
}
