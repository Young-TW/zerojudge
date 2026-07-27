#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<string> rows(n);
        for (int i = 0; i < n; ++i) cin >> rows[i];
        int start, target, s;
        cin >> start >> target >> s;

        // adjacency matrix (1‑based)
        vector<vector<int>> adj(n + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                adj[i][j] = rows[i - 1][j - 1] - '0';

        /* ---------- 1. number of walks ---------- */
        int L = s + 1;                     // number of edges
        vector<unsigned long long> cur(n + 1, 0), nxt(n + 1, 0);
        cur[start] = 1;
        for (int step = 1; step <= L; ++step) {
            fill(nxt.begin(), nxt.end(), 0ULL);
            for (int u = 1; u <= n; ++u) if (cur[u]) {
                unsigned long long ways = cur[u];
                for (int v = 1; v <= n; ++v) if (adj[u][v]) {
                    nxt[v] += ways;
                }
            }
            cur.swap(nxt);
        }
        unsigned long long answer = cur[target];

        /* ---------- 2. reachability (Floyd‑Warshall) ---------- */
        vector<vector<bool>> reach(n + 1, vector<bool>(n + 1, false));
        for (int u = 1; u <= n; ++u) {
            reach[u][u] = true;               // zero‑length path
            for (int v = 1; v <= n; ++v)
                if (adj[u][v]) reach[u][v] = true;
        }
        for (int k = 1; k <= n; ++k)
            for (int i = 1; i <= n; ++i)
                if (reach[i][k])
                    for (int j = 1; j <= n; ++j)
                        if (reach[k][j]) reach[i][j] = true;

        int a = 0, b = 0;
        bool found = false;
        for (int i = 1; i <= n && !found; ++i)
            for (int j = i + 1; j <= n; ++j)
                if (!reach[i][j]) {
                    a = i; b = j; found = true; break;
                }
        if (!found) { a = 0; b = 0; }

        /* ---------- output ---------- */
        cout << answer << "\n" << a << "\n" << b << "\n";
    }
    return 0;
}
