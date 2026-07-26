#include <bits/stdc++.h>
using namespace std;

const int INF_NEG = -1e9;          // sufficiently small

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K, D;
    while (cin >> N >> K >> D) {
        vector<int> a(N + 1);
        for (int i = 1; i <= N; ++i) cin >> a[i];

        int maxPossible = N * (N + 1) / 2;
        int C = min(D, maxPossible);

        // dp[r][c] : r = 0..K-1, c = 0..C
        vector< vector<int> > dp(K, vector<int>(C + 1, INF_NEG));
        dp[0][0] = 0;

        // to avoid scanning the whole C range each time,
        // we keep for each r a list of reachable costs.
        vector< vector<int> > reachable(K);
        reachable[0].push_back(0);

        for (int idx = 1; idx <= N; ++idx) {
            // new tables
            vector< vector<int> > ndp(K, vector<int>(C + 1, INF_NEG));
            vector< vector<int> > nreach(K);

            for (int r = 0; r < K; ++r) {
                for (int c : reachable[r]) {
                    int cur = dp[r][c];
                    if (cur == INF_NEG) continue;

                    // 1) skip
                    if (ndp[r][c] < cur) {
                        ndp[r][c] = cur;
                        if (ndp[r][c] == cur) nreach[r].push_back(c);
                    }

                    // 2) take without closing
                    if (r + 1 < K) {
                        if (ndp[r + 1][c] < cur + a[idx]) {
                            ndp[r + 1][c] = cur + a[idx];
                            if (ndp[r + 1][c] == cur + a[idx]) nreach[r + 1].push_back(c);
                        }
                    }

                    // 3) take and close box
                    int nc = c + idx;
                    if (nc <= C) {
                        if (ndp[0][nc] < cur + a[idx]) {
                            ndp[0][nc] = cur + a[idx];
                            if (ndp[0][nc] == cur + a[idx]) nreach[0].push_back(nc);
                        }
                    }
                }
            }

            // remove duplicates in reachable lists
            for (int r = 0; r < K; ++r) {
                auto &vec = nreach[r];
                sort(vec.begin(), vec.end());
                vec.erase(unique(vec.begin(), vec.end()), vec.end());
            }

            dp.swap(ndp);
            reachable.swap(nreach);
        }

        int answer = 0;
        for (int c = 0; c <= C; ++c) {
            if (dp[0][c] > answer) answer = dp[0][c];
        }
        cout << answer << '\n';
    }
    return 0;
}
