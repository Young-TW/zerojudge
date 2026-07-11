#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <utility>

using namespace std;

const int MOD = 1000000007;

int dp_arr[78125];
int next_dp_arr[78125];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (!(cin >> T)) return 0;

    int pow5[8];
    pow5[0] = 1;
    for (int i = 1; i <= 7; ++i) {
        pow5[i] = pow5[i - 1] * 5;
    }

    for (int t = 1; t <= T; ++t) {
        int M, N;
        cin >> M >> N;
        int R = N + 1;
        int C = M + 1;
        
        int K;
        cin >> K;
        vector<pair<int, int>> skips(K);
        for (int i = 0; i < K; ++i) {
            cin >> skips[i].first >> skips[i].second;
        }

        if (C > R) {
            swap(R, C);
            for (int i = 0; i < K; ++i) {
                swap(skips[i].first, skips[i].second);
            }
        }

        bool skip[8][8] = {};
        for (int i = 0; i < K; ++i) {
            int x = skips[i].first; // 1 to C
            int y = skips[i].second; // 1 to R
            skip[y - 1][x - 1] = true;
        }

        int max_mask = pow5[C];
        int* dp = dp_arr;
        int* next_dp = next_dp_arr;
        
        memset(dp, 0, sizeof(int) * max_mask);
        
        int init_mask = 0;
        for (int i = 0; i < C; ++i) {
            init_mask += 4 * pow5[i];
        }
        dp[init_mask] = 1;

        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                memset(next_dp, 0, sizeof(int) * max_mask);
                int p = pow5[j];
                int p_left = (j == 0) ? 0 : pow5[j - 1];
                
                if (skip[i][j]) {
                    for (int mask = 0; mask < max_mask; ++mask) {
                        int val = dp[mask];
                        if (val == 0) continue;
                        
                        int up_color = (mask / p) % 5;
                        int base_val = mask - up_color * p;
                        
                        int new_mask = base_val + 4 * p;
                        next_dp[new_mask] += val;
                        if (next_dp[new_mask] >= MOD) next_dp[new_mask] -= MOD;
                    }
                } else {
                    for (int mask = 0; mask < max_mask; ++mask) {
                        int val = dp[mask];
                        if (val == 0) continue;
                        
                        int up_color = (mask / p) % 5;
                        int left_color = (j == 0) ? 4 : (mask / p_left) % 5;
                        int base_val = mask - up_color * p;
                        
                        for (int new_color = 0; new_color < 4; ++new_color) {
                            if (new_color != up_color && new_color != left_color) {
                                int new_mask = base_val + new_color * p;
                                next_dp[new_mask] += val;
                                if (next_dp[new_mask] >= MOD) next_dp[new_mask] -= MOD;
                            }
                        }
                    }
                }
                swap(dp, next_dp);
            }
        }

        int ans = 0;
        for (int mask = 0; mask < max_mask; ++mask) {
            ans += dp[mask];
            if (ans >= MOD) ans -= MOD;
        }

        cout << "Case " << t << ": " << ans << "\n";
    }

    return 0;
}
