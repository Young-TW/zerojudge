#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int MAXV = 26;
    const int INF = 1e9;

    int m;
    while (cin >> m) {
        vector<int> adj[MAXV];
        for (int i = 0; i < m; ++i) {
            string s;
            cin >> s;
            if (s.size() < 2) { --i; continue; }          // safety
            int u = s[0] - 'A';
            int v = s[1] - 'A';
            adj[u].push_back(v);
        }

        int best = INF;

        for (int start = 0; start < MAXV; ++start) {
            // BFS from 'start'
            vector<int> dist(MAXV, INF);
            queue<int> q;
            dist[start] = 0;
            q.push(start);

            while (!q.empty()) {
                int cur = q.front(); q.pop();
                for (int nxt : adj[cur]) {
                    if (nxt == start) {
                        // found a cycle
                        best = min(best, dist[cur] + 1);
                    } else if (dist[nxt] == INF) {
                        dist[nxt] = dist[cur] + 1;
                        q.push(nxt);
                    }
                }
            }
        }

        if (best == INF) cout << 0 << '\n';
        else             cout << best << '\n';
    }
    return 0;
}
