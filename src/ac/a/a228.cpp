#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        for (int t = 1; t <= T; ++t) {
            int N, M;
            cin >> N >> M;
            int grid[12][12];
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    cin >> grid[i][j];
                }
            }

            int max_mask = 1 << (M + 1);
            long long dp[4096] = {0};
            long long next_dp[4096] = {0};
            dp[0] = 1;

            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    memset(next_dp, 0, sizeof(next_dp));
                    for (int mask = 0; mask < max_mask; ++mask) {
                        if (!dp[mask]) continue;
                        long long val = dp[mask];
                        int left = (mask >> j) & 1;
                        int up = (mask >> (j + 1)) & 1;

                        if (grid[i][j] == 0) {
                            if (left == 0 && up == 0) {
                                int new_mask = mask;
                                if (j == M - 1) {
                                    new_mask = (new_mask << 1) & (max_mask - 1);
                                }
                                next_dp[new_mask] = (next_dp[new_mask] + val) % MOD;
                            }
                        } else {
                            for (int down = 0; down <= 1; ++down) {
                                for (int right = 0; right <= 1; ++right) {
                                    if (i == N - 1 && down == 1) continue;
                                    if (j == M - 1 && right == 1) continue;
                                    if (left + up + right + down == 2) {
                                        int new_mask = mask ^ (left << j) ^ (up << (j + 1));
                                        new_mask |= (down << j) | (right << (j + 1));
                                        if (j == M - 1) {
                                            new_mask = (new_mask << 1) & (max_mask - 1);
                                        }
                                        next_dp[new_mask] = (next_dp[new_mask] + val) % MOD;
                                    }
                                }
                            }
                        }
                    }
                    memcpy(dp, next_dp, sizeof(dp));
                }
            }

            cout << "Case " << t << ": " << dp[0] << "\n";
        }
    }
    return 0;
}
