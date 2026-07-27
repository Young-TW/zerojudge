#include <bits/stdc++.h>
using namespace std;

struct EdgeInfo {
    int to;
    int idx;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    while (cin >> N >> M) {
        vector<long long> d(N + 1);
        for (int i = 1; i <= N; ++i) {
            long long h;
            cin >> h;
            d[i] = h - M;                 // surplus / deficit
        }

        int E = N - 1;
        vector<int> cost(E);
        vector<long long> profit(E);
        vector<vector<EdgeInfo>> adj(N + 1);

        for (int e = 0; e < E; ++e) {
            int u, v, c, l;
            cin >> u >> v >> c >> l;
            cost[e] = c;
            long long p = 2LL * min(l, 150) + max(0, l - 150);
            profit[e] = p;
            adj[u].push_back({v, e});
            adj[v].push_back({u, e});
        }

        long long answer = 0;

        function<long long(int,int)> dfs = [&](int u, int parent) -> long long {
            long long sum = d[u];
            for (const auto &ed : adj[u]) {
                int v = ed.to;
                int idx = ed.idx;
                if (v == parent) continue;
                long long childSum = dfs(v, u);          // sub[v]
                if (childSum != 0) {
                    answer += profit[idx] - llabs(childSum) * (long long)cost[idx];
                } else {
                    long long extra = profit[idx] - 2LL * cost[idx];
                    if (extra > 0) answer += extra;
                }
                sum += childSum;
            }
            return sum;
        };

        dfs(1, 0);
        cout << answer << '\n';
    }
    return 0;
}
