#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    while (cin >> N >> M) {
        vector<vector<int>> adj(N), radj(N);
        adj.reserve(N);
        radj.reserve(N);
        for (int i = 0; i < M; ++i) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            adj[a].push_back(b);
            radj[b].push_back(a);
        }

        /* ---------- first pass : order ---------- */
        vector<char> visited(N, 0);
        vector<int> order;
        order.reserve(N);
        vector<pair<int, size_t>> stack;
        for (int s = 0; s < N; ++s) if (!visited[s]) {
            stack.emplace_back(s, 0);
            visited[s] = 1;
            while (!stack.empty()) {
                int u = stack.back().first;
                size_t &idx = stack.back().second;
                if (idx < adj[u].size()) {
                    int v = adj[u][idx++];
                    if (!visited[v]) {
                        visited[v] = 1;
                        stack.emplace_back(v, 0);
                    }
                } else {
                    order.push_back(u);
                    stack.pop_back();
                }
            }
        }

        /* ---------- second pass : components ---------- */
        vector<int> comp(N, -1);
        int compCnt = 0;
        vector<int> st;
        for (int i = (int)order.size() - 1; i >= 0; --i) {
            int s = order[i];
            if (comp[s] != -1) continue;
            st.clear();
            st.push_back(s);
            comp[s] = compCnt;
            while (!st.empty()) {
                int u = st.back(); st.pop_back();
                for (int v : radj[u]) if (comp[v] == -1) {
                    comp[v] = compCnt;
                    st.push_back(v);
                }
            }
            ++compCnt;
        }

        if (compCnt == 1) {
            cout << "Yes\n";
            continue;
        }

        /* ---------- build condensation DAG (dedup) ---------- */
        vector<pair<int,int>> edges;
        edges.reserve(M);
        for (int u = 0; u < N; ++u) {
            int cu = comp[u];
            for (int v : adj[u]) {
                int cv = comp[v];
                if (cu != cv) edges.emplace_back(cu, cv);
            }
        }
        sort(edges.begin(), edges.end());
        edges.erase(unique(edges.begin(), edges.end()), edges.end());

        vector<vector<int>> cadj(compCnt);
        vector<int> indeg(compCnt, 0);
        for (auto &e : edges) {
            cadj[e.first].push_back(e.second);
            ++indeg[e.second];
        }

        int start = comp[0];               // vertex 1 -> index 0
        if (indeg[start] != 0) {
            cout << "No\n";
            continue;
        }

        queue<int> q;
        for (int i = 0; i < compCnt; ++i)
            if (indeg[i] == 0) q.push(i);

        bool ok = true;
        int processed = 0;
        while (!q.empty()) {
            if ((int)q.size() != 1) { ok = false; break; }
            int u = q.front(); q.pop();
            ++processed;
            for (int v : cadj[u]) {
                if (--indeg[v] == 0) q.push(v);
            }
        }
        if (ok && processed == compCnt) cout << "Yes\n";
        else                               cout << "No\n";
    }
    return 0;
}
