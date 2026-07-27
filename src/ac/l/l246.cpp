#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int c, T;
    while (cin >> c >> T) {
        vector<int> p(c + 1), s(c + 1), n(c + 1);
        for (int i = 1; i <= c; ++i) cin >> p[i];
        for (int i = 1; i <= c; ++i) cin >> s[i];
        for (int i = 1; i <= c; ++i) cin >> n[i];

        vector<vector<int>> r(c + 1, vector<int>(c + 1, 0));
        for (int i = 1; i <= c; ++i) {
            for (int j = 1; j <= i; ++j) {
                cin >> r[i][j];
            }
        }

        vector<int> S_n(c + 1, 0), S_p(c + 1, 0);
        for (int i = 1; i <= c; ++i) {
            S_n[i] = S_n[i - 1] + n[i];
            S_p[i] = S_p[i - 1] + p[i];
        }

        vector<vector<int>> R(c + 1, vector<int>(c + 1, 0));
        for (int i = 1; i <= c; ++i) {
            vector<int> prefix_r(c + 1, 0);
            for (int j = 1; j <= i; ++j) {
                prefix_r[j] = prefix_r[j - 1] + r[i][j];
            }
            for (int k = 0; k < i; ++k) {
                R[i][k] = prefix_r[i] - prefix_r[k];
            }
        }

        vector<vector<pair<int, int>>> dp(c + 1);
        dp[0].push_back({0, 0});

        for (int i = 1; i <= c; ++i) {
            vector<pair<int, int>> tmp;
            for (int k = 0; k < i; ++k) {
                if (dp[k].empty()) continue;
                int load_cost_factor = S_n[c] - S_n[k];
                int load_p_factor = S_p[i] - S_p[k];
                int sell_cost_factor = S_n[i] - S_n[k];
                int sell_gain = R[i][k];
                
                for (auto& state : dp[k]) {
                    int cost = state.first;
                    int val = state.second;
                    int new_cost = cost + load_cost_factor * load_p_factor + sell_cost_factor * s[i];
                    if (new_cost <= T) {
                        tmp.push_back({new_cost, val + sell_gain});
                    }
                }
            }
            
            sort(tmp.begin(), tmp.end());
            for (auto& p_state : tmp) {
                if (!dp[i].empty() && dp[i].back().second >= p_state.second) continue;
                if (!dp[i].empty() && dp[i].back().first == p_state.first) dp[i].pop_back();
                dp[i].push_back(p_state);
            }
        }

        int ans = -1;
        if (S_n[c] * S_p[c] <= T) {
            ans = 0;
        }

        for (int i = 1; i <= c; ++i) {
            if (dp[i].empty()) continue;
            int final_load_cost = (S_n[c] - S_n[i]) * (S_p[c] - S_p[i]);
            for (auto& state : dp[i]) {
                if (state.first + final_load_cost <= T) {
                    ans = max(ans, state.second);
                }
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
