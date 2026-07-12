#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 1e9;

struct Edge {
    int to, cap, rev;
};

class Dinic {
public:
    vector<vector<Edge>> graph;
    vector<int> level;
    vector<int> iter;
    int n;

    Dinic(int n) : n(n), graph(n), level(n), iter(n) {}

    void add_edge(int from, int to, int cap) {
        graph[from].push_back({to, cap, (int)graph[to].size()});
        graph[to].push_back({from, 0, (int)graph[from].size() - 1});
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (const Edge& e : graph[v]) {
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
        for (int& i = iter[v]; i < graph[v].size(); ++i) {
            Edge& e = graph[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
                int d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    graph[e.to][e.rev].cap += d;
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
    
    int N;
    while (cin >> N && N) {
        vector<int> cntM(10, 0);
        vector<int> cntF(10, 0);
        for (int i = 0; i < N; ++i) {
            int score;
            cin >> score;
            cntM[score]++;
        }
        for (int i = 0; i < N; ++i) {
            int score;
            cin >> score;
            cntF[score]++;
        }
        
        Dinic dinic(20);
        int S = 0, T = 19;
        for (int i = 1; i <= 9; ++i) {
            dinic.add_edge(S, i, cntM[i]);
            dinic.add_edge(i + 9, T, cntF[i]);
            for (int j = 1; j <= 9; ++j) {
                if (i + j > 10) {
                    dinic.add_edge(i, j + 9, INF);
                }
            }
        }
        
        int ans = dinic.max_flow(S, T);
        cout << ans << " " << ans * 200 << "\n";
    }
    
    return 0;
}
