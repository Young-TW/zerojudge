#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
int best_max;
vector<int> best_set;
int MAX_SUM;

void dfs(vector<int>& chosen, int cur_max, int next_min, const vector<int>& dp) {
    if (chosen.size() == M) {
        if (cur_max > best_max) {
            best_max = cur_max;
            best_set = chosen;
        }
        return;
    }
    int upper = min(100, cur_max + 1);
    for (int w = next_min; w <= upper; ++w) {
        chosen.push_back(w);
        vector<int> new_dp = dp;
        for (int i = w; i <= MAX_SUM; ++i) {
            if (new_dp[i - w] + 1 < new_dp[i]) {
                new_dp[i] = new_dp[i - w] + 1;
            }
        }
        int new_max = cur_max;
        while (new_max < MAX_SUM && new_dp[new_max + 1] <= N) {
            new_max++;
        }
        dfs(chosen, new_max, w + 1, new_dp);
        chosen.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        N = n;
        M = m;
        MAX_SUM = N * 100;
        best_max = -1;
        best_set.clear();
        
        if (M == 0) {
            cout << 0 << "\n\n";
            continue;
        }
        
        vector<int> chosen;
        chosen.push_back(1);
        vector<int> dp(MAX_SUM + 1, N + 1);
        dp[0] = 0;
        for (int i = 1; i <= MAX_SUM; ++i) {
            if (i <= N) dp[i] = i;
            else dp[i] = N + 1;
        }
        int cur_max = N;
        
        if (M == 1) {
            best_max = cur_max;
            best_set = chosen;
        } else {
            dfs(chosen, cur_max, 2, dp);
        }
        
        cout << best_max << "\n";
        for (size_t i = 0; i < best_set.size(); ++i) {
            if (i > 0) cout << " ";
            cout << best_set[i];
        }
        cout << "\n";
    }
    return 0;
}
