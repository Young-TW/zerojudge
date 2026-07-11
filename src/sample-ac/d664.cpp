#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

vector<uint32_t> pre[8][128];

void gen_states(int cols, int mask, int col, int prev_color, uint32_t state, vector<uint32_t>& states) {
    if (col == cols) {
        states.push_back(state);
        return;
    }
    if (mask & (1 << col)) {
        gen_states(cols, mask, col + 1, 0, state, states);
    } else {
        for (int c = 1; c <= 4; ++c) {
            if (prev_color != 0 && c == prev_color) continue;
            gen_states(cols, mask, col + 1, c, state | (1u << ((c - 1) * cols + col)), states);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int cols = 1; cols <= 7; ++cols) {
        int max_mask = 1 << cols;
        for (int mask = 0; mask < max_mask; ++mask) {
            vector<uint32_t> states;
            gen_states(cols, mask, 0, 0, 0, states);
            pre[cols][mask] = move(states);
        }
    }

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int M, N;
        cin >> M >> N;
        int rows = M + 1;
        int cols = N + 1;
        int K;
        cin >> K;
        vector<int> row_masks(rows, 0);
        for (int i = 0; i < K; ++i) {
            int X, Y;
            cin >> X >> Y;
            int r = X - 1;
            int c = Y - 1;
            if (r >= 0 && r < rows && c >= 0 && c < cols) {
                row_masks[r] |= (1 << c);
            }
        }

        const vector<uint32_t>* prev_states = &pre[cols][row_masks[0]];
        vector<int> dp(prev_states->size(), 1);

        for (int i = 1; i < rows; ++i) {
            const vector<uint32_t>* curr_states = &pre[cols][row_masks[i]];
            vector<int> new_dp(curr_states->size(), 0);
            const uint32_t* prev_arr = prev_states->data();
            const uint32_t* curr_arr = curr_states->data();
            int prev_size = prev_states->size();
            int curr_size = curr_states->size();
            for (int ci = 0; ci < curr_size; ++ci) {
                uint32_t cs = curr_arr[ci];
                long long sum = 0;
                for (int pi = 0; pi < prev_size; ++pi) {
                    if ((prev_arr[pi] & cs) == 0) {
                        sum += dp[pi];
                    }
                }
                new_dp[ci] = sum % MOD;
            }
            dp.swap(new_dp);
            prev_states = curr_states;
        }

        long long ans = 0;
        for (int v : dp) {
            ans += v;
            if (ans >= MOD) ans -= MOD;
        }
        cout << "Case " << tc << ": " << ans % MOD << "\n";
    }
    return 0;
}
