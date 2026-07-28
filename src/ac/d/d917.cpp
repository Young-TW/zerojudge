#include <bits/stdc++.h>
using namespace std;

int longestPath(int n, const vector<vector<int>>& adj,
                const vector<int>& indegOrig)
{
    vector<int> indeg = indegOrig;
    vector<int> dp(n, 0);
    queue<int> q;
    for (int i = 0; i < n; ++i)
        if (indeg[i] == 0) q.push(i);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dp[v] < dp[u] + 1) dp[v] = dp[u] + 1;
            if (--indeg[v] == 0) q.push(v);
        }
    }
    return *max_element(dp.begin(), dp.end());   // longest path length (edges)
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        int w;  cin >> w;
        int m = n * (n - 1) / 2;
        vector<vector<int>> adjX(n), adjY(n);
        vector<int> indegX(n, 0), indegY(n, 0);
        for (int k = 0; k < m; ++k) {
            int i, j, p;
            cin >> i >> j >> p;
            --i; --j;                     // zero based
            if (p == 0) {                 // i right of j : edge j -> i in X
                adjX[j].push_back(i);
                ++indegX[i];
            } else {                      // i above j : edge j -> i in Y
                adjY[j].push_back(i);
                ++indegY[i];
            }
        }
        int dx = longestPath(n, adjX, indegX);
        int dy = longestPath(n, adjY, indegY);
        long long ans = 1LL * w * w * (dx + 1) * (dy + 1);
        cout << ans << '\n';
    }
    return 0;
}
