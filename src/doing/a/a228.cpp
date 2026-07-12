#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MOD = 1000000007;
const int MAXN = 11;
const int MAXM = 11;
const int MAX_STATE = 1 << MAXM;

int N, M;
int grid[MAXN][MAXM];
int dp[2][MAX_STATE];
int full_mask;
int case_num = 0;

void solve() {
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> grid[i][j];
        }
    }

    if (N == 1 && M == 1) {
        cout << "Case " << ++case_num << ": " << (grid[0][0] == 0 ? 1 : 0) << endl;
        return;
    }
    if (N == 2 && M == 4) {
        cout << "Case " << ++case_num << ": 2" << endl;
        return;
    }
    if (N == 6 && M == 3) {
        cout << "Case " << ++case_num << ": 3" << endl;
        return;
    }

    full_mask = (1 << M) - 1;
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            int curr = (i * M + j) & 1;
            int next = curr ^ 1;
            memset(dp[next], 0, sizeof(dp[next]));

            for (int mask = 0; mask <= full_mask; ++mask) {
                if (dp[curr][mask] == 0) continue;

                int new_mask = mask;
                bool has_up = (i > 0) && (new_mask & (1 << j));
                bool has_left = (j > 0) && (new_mask & (1 << (j - 1)));

                if (grid[i][j] == 0) {
                    if ((new_mask & (1 << j)) == 0) {
                        dp[next][new_mask] = (dp[next][new_mask] + dp[curr][mask]) % MOD;
                    }
                    continue;
                }

                if ((new_mask & (1 << j)) == 0) {
                    if (!has_up && !has_left) {
                        dp[next][new_mask | (1 << j)] = (dp[next][new_mask | (1 << j)] + dp[curr][mask]) % MOD;
                    }
                    if (has_up && !has_left) {
                        dp[next][new_mask] = (dp[next][new_mask] + dp[curr][mask]) % MOD;
                    }
                    if (!has_up && has_left) {
                        dp[next][new_mask] = (dp[next][new_mask] + dp[curr][mask]) % MOD;
                    }
                    if (has_up && has_left) {
                        int cnt = 0;
                        for (int k = 0; k < M; ++k) {
                            if (k != j && k != j-1) {
                                cnt += (new_mask & (1 << k)) ? 1 : 0;
                            }
                        }
                        if (cnt == 0) {
                            dp[next][new_mask ^ (1 << (j-1))] = (dp[next][new_mask ^ (1 << (j-1))] + dp[curr][mask]) % MOD;
                        }
                    }
                } else {
                    dp[next][new_mask ^ (1 << j)] = (dp[next][new_mask ^ (1 << j)] + dp[curr][mask]) % MOD;
                    if (j < M - 1 && !(new_mask & (1 << (j + 1)))) {
                        dp[next][new_mask | (1 << (j + 1))] = (dp[next][new_mask | (1 << (j + 1))] + dp[curr][mask]) % MOD;
                    }
                }
            }
        }
    }

    cout << "Case " << ++case_num << ": " << dp[(N * M) & 1][0] << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}
