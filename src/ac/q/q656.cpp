#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N, D;
    while (cin >> N >> D) {
        vector<long long> profit(N + 1, 0);          // 1‑based
        for (long long i = 2; i <= N - 1; ++i) {
            long long x;
            cin >> x;
            profit[i] = x;
        }

        vector<long long> dp(N + 1, 0);
        deque<pair<long long, long long>> dq;        // (index, dp)

        dp[1] = 0;
        dq.emplace_back(1, dp[1]);

        for (long long i = 2; i <= N; ++i) {
            // remove indices that are farther than D
            while (!dq.empty() && dq.front().first < i - D)
                dq.pop_front();

            long long best = dq.front().second;      // maximum dp in window
            dp[i] = best + profit[i];                // profit[N] = 0

            // keep deque decreasing by dp value
            while (!dq.empty() && dq.back().second <= dp[i])
                dq.pop_back();
            dq.emplace_back(i, dp[i]);
        }

        cout << dp[N] << '\n';
    }
    return 0;
}
