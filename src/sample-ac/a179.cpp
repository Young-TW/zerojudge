#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const long long INF = (long long)4e18;

struct Dinic {
    struct Edge {
        int to;
        long long cap;
        int rev;
    };
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
            for (auto &e : graph[v]) {
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
        for (int &i = iter[v]; i < (int)graph[v].size(); i++) {
            Edge &e = graph[v][i];
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
            while ((f = dfs(s, t, INF)) > 0) {
                flow += f;
            }
        }
        return flow;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    while (cin >> N >> M) {
        int S = 0;
        int T = N + M + 1;
        int totalNodes = N + M + 2;
        Dinic dinic(totalNodes);

        long long totalProfit = 0;

        for (int i = 1; i <= N; i++) {
            long long p;
            cin >> p;
            dinic.add_edge(i, T, p);
        }

        for (int j = 1; j <= M; j++) {
            long long a, b, c;
            cin >> a >> b >> c;
            totalProfit += c;
            int userNode = N + j;
            dinic.add_edge(S, userNode, c);
            dinic.add_edge(userNode, (int)a, INF);
            dinic.add_edge(userNode, (int)b, INF);
        }

        long long minCut = dinic.max_flow(S, T);
        long long ans = totalProfit - minCut;
        cout << ans << "\n";
    }

    return 0;
}
