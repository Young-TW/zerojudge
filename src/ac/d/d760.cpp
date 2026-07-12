#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    long long cap;
    int rev;
};

class Dinic {
public:
    vector<vector<Edge>> graph;
    vector<int> level, iter;
    int n;

    Dinic(int n) : n(n), graph(n), level(n), iter(n) {}

    void add_edge(int from, int to, long long cap) {
        graph[from].push_back({to, cap, (int)graph[to].size()});
        graph[to].push_back({from, 0, (int)graph[from].size() - 1});
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (const auto& e : graph[v]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] >= 0;
    }

    long long dfs(int v, int t, long long f) {
        if (v == t) return f;
        for (int& i = iter[v]; i < (int)graph[v].size(); i++) {
            Edge& e = graph[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
                long long d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    graph[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    long long max_flow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {
            fill(iter.begin(), iter.end(), 0);
            long long f;
            while ((f = dfs(s, t, 1e18)) > 0) {
                flow += f;
            }
        }
        return flow;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        int S = 0, T = 2 * N + 1;
        Dinic dinic(2 * N + 2);
        
        for (int i = 1; i <= N; ++i) {
            long long cap;
            cin >> cap;
            dinic.add_edge(i, i + N, cap);
        }
        
        int M;
        cin >> M;
        for (int k = 0; k < M; ++k) {
            int u, v;
            long long c;
            cin >> u >> v >> c;
            dinic.add_edge(u + N, v, c);
        }
        
        int B, D;
        cin >> B >> D;
        for (int k = 0; k < B; ++k) {
            int u;
            cin >> u;
            dinic.add_edge(S, u, 1e18);
        }
        for (int k = 0; k < D; ++k) {
            int u;
            cin >> u;
            dinic.add_edge(u + N, T, 1e18);
        }
        
        cout << dinic.max_flow(S, T) << "\n";
    }
    
    return 0;
}
