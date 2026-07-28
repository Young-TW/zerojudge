#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <functional>
#include <utility>
using namespace std;

struct Edge {
    int to, rev, cap;
};

struct UndEdge {
    int u, v;
    int flow_fr, flow_idx;
};

struct DSU {
    vector<int> p;
    DSU(int n) {
        p.resize(n+1);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a != b) p[a] = b;
    }
};

int addEdge(vector<vector<Edge> >& g, int fr, int to, int cap) {
    Edge a{to, (int)g[to].size(), cap};
    Edge b{fr, (int)g[fr].size(), 0};
    g[fr].push_back(a);
    g[to].push_back(b);
    return (int)g[fr].size() - 1;
}

int maxflow(vector<vector<Edge> >& g, int s, int t) {
    int n = g.size();
    vector<int> level(n), it(n);
    auto bfs = [&]() -> bool {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0; q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto& e : g[v]) {
                if (e.cap && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] >= 0;
    };
    function<int(int,int)> dfs;
    dfs = [&](int v, int f) -> int {
        if (v == t) return f;
        for (int& i = it[v]; i < (int)g[v].size(); ++i) {
            Edge& e = g[v][i];
            if (e.cap && level[v] < level[e.to]) {
                int ret = dfs(e.to, min(f, e.cap));
                if (ret) {
                    e.cap -= ret;
                    g[e.to][e.rev].cap += ret;
                    return ret;
                }
            }
        }
        return 0;
    };
    int flow = 0;
    while (bfs()) {
        fill(it.begin(), it.end(), 0);
        int f;
        while ((f = dfs(s, 1000000000)) > 0) flow += f;
    }
    return flow;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<pair<int,int> > dirEdges;
        vector<UndEdge> undEdges;
        vector<int> outD(n+1,0), inD(n+1,0);
        vector<int> undeg(n+1,0);
        DSU dsu(n);
        for (int i=0; i<m; ++i) {
            int u, v; char tp;
            cin >> u >> v >> tp;
            dsu.unite(u, v);
            if (tp == 'D') {
                dirEdges.emplace_back(u, v);
                outD[u]++; inD[v]++;
            } else {
                undEdges.push_back({u, v, 0, 0});
                undeg[u]++; undeg[v]++;
            }
        }

        bool ok = true;
        for (int v=1; v<=n; ++v) {
            if (outD[v] + inD[v] + undeg[v] == 0) continue;
            if (dsu.find(v) != dsu.find(1)) { ok = false; break; }
        }
        if (!ok) {
            cout << "Game Over\n";
            continue;
        }

        vector<int> outAll = outD;
        vector<int> inAll = inD;
        for (auto& e : undEdges) {
            outAll[e.u]++;
            inAll[e.v]++;
        }
        vector<int> bal(n+1, 0);
        for (int v=1; v<=n; ++v) {
            bal[v] = outAll[v] - inAll[v];
            if (bal[v] % 2 != 0) { ok = false; break; }
        }
        if (!ok) {
            cout << "Game Over\n";
            continue;
        }

        int S = 0, T = n+1;
        vector<vector<Edge> > g(n+2);
        int total_needed = 0;
        for (int v=1; v<=n; ++v) {
            int d = bal[v] / 2;
            if (d > 0) {
                addEdge(g, S, v, d);
                total_needed += d;
            } else if (d < 0) {
                addEdge(g, v, T, -d);
            }
        }
        for (int i=0; i<(int)undEdges.size(); ++i) {
            auto& e = undEdges[i];
            int idx = addEdge(g, e.u, e.v, 1);
            e.flow_fr = e.u;
            e.flow_idx = idx;
        }

        int flow = maxflow(g, S, T);
        if (flow != total_needed) {
            cout << "Game Over\n";
            continue;
        }

        vector<pair<int,int> > allDir = dirEdges;
        for (auto& e : undEdges) {
            int cap = g[e.flow_fr][e.flow_idx].cap;
            if (cap == 0) {
                allDir.emplace_back(e.v, e.u);
            } else {
                allDir.emplace_back(e.u, e.v);
            }
        }

        vector<vector<int> > adj(n+1);
        for (auto& e : allDir) {
            adj[e.first].push_back(e.second);
        }
        vector<int> circuit;
        stack<int> st;
        st.push(1);
        vector<int> it(n+1, 0);
        while (!st.empty()) {
            int v = st.top();
            if (it[v] < (int)adj[v].size()) {
                int to = adj[v][it[v]++];
                st.push(to);
            } else {
                circuit.push_back(v);
                st.pop();
            }
        }
        reverse(circuit.begin(), circuit.end());

        if ((int)circuit.size() != m + 1) {
            cout << "Game Over\n";
            continue;
        }

        for (int i=0; i<(int)circuit.size(); ++i) {
            if (i) cout << ' ';
            cout << circuit[i];
        }
        cout << '\n';
    }
    return 0;
}
