#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct State {
    int total;
    int cnt[4];
};

bool is_better(const State& a, const State& b) {
    if (a.total != b.total) return a.total < b.total;
    for (int i = 0; i < 4; ++i) {
        if (a.cnt[i] != b.cnt[i]) return a.cnt[i] < b.cnt[i];
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int c1;
    while (cin >> c1) {
        if (c1 == 0) break;
        int c2, c3, c4, target;
        cin >> c2 >> c3 >> c4 >> target;
        int coins[4] = {c1, c2, c3, c4};
        
        const int INF = 1e9;
        vector<State> dp(target + 1);
        for (int i = 0; i <= target; ++i) {
            dp[i].total = INF;
            for (int j = 0; j < 4; ++j) dp[i].cnt[j] = 0;
        }
        dp[0].total = 0;
        
        for (int i = 1; i <= target; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (i >= coins[j] && dp[i - coins[j]].total != INF) {
                    State cur = dp[i - coins[j]];
                    cur.total++;
                    cur.cnt[j]++;
                    if (is_better(cur, dp[i])) {
                        dp[i] = cur;
                    }
                }
            }
        }
        
        if (dp[target].total == INF) {
            cout << 0 << "\n";
        } else {
            cout << dp[target].total << " " << dp[target].cnt[0] << " " << dp[target].cnt[1] << " " << dp[target].cnt[2] << " " << dp[target].cnt[3] << "\n";
        }
    }
    
    return 0;
}
