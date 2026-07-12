#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 1e9;

struct Edge {
    int to, cap, rev;
};

class Dinic {
public:
    vector<vector<Edge>> g;
    vector<int> level, iter;
    int n;
    
    Dinic(int n) : n(n), g(n), level(n), iter(n) {}
    
    void add_edge(int from, int to, int cap) {
        g[from].push_back({to, cap, (int)g[to].size()});
        g[to].push_back({from, cap, (int)g[from].size()-1});
    }
    
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (size_t i = 0; i < g[v].size(); i++) {
                Edge& e = g[v][i];
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] >= 0;
    }
    
    int dfs(int v, int t, int f) {
        if (v == t) return f;
        for (int& i = iter[v]; i < (int)g[v].size(); i++) {
            Edge& e = g[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
                int d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    g[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    
    int max_flow(int s, int t) {
        int flow = 0;
        while (bfs(s, t)) {
            fill(iter.begin(), iter.end(), 0);
            int f;
            while ((f = dfs(s, t, INF)) > 0) {
                flow += f;
            }
        }
        return flow;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    int caseNo = 1;
    while (cin >> n && n) {
        int s, t, c;
        cin >> s >> t >> c;
        s--; t--;
        Dinic dinic(n);
        for (int i = 0; i < c; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            u--; v--;
            dinic.add_edge(u, v, w);
        }
        int flow = dinic.max_flow(s, t);
        cout << "Network " << caseNo++ << "\n";
        cout << "The bandwidth is " << flow << ".\n\n";
    }
    return 0;
}
