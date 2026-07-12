#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

struct Dinic {
    struct Edge { int to, rev; long long cap; };
    int N;
    vector<vector<Edge>> G;
    vector<int> level, prog;
    Dinic(int N) : N(N), G(N), level(N), prog(N) {}
    void add_edge(int fr, int to, long long cap) {
        Edge a = {to, (int)G[to].size(), cap};
        Edge b = {fr, (int)G[fr].size(), 0};
        G[fr].push_back(a);
        G[to].push_back(b);
    }
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while(!q.empty()) {
            int v = q.front(); q.pop();
            for(const auto &e : G[v]) {
                if(e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] >= 0;
    }
    long long dfs(int v, int t, long long f) {
        if(v == t) return f;
        for(int &i = prog[v]; i < (int)G[v].size(); i++) {
            Edge &e = G[v][i];
            if(e.cap > 0 && level[v] < level[e.to]) {
                long long d = dfs(e.to, t, min(f, e.cap));
                if(d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    long long max_flow(int s, int t) {
        long long flow = 0;
        while(bfs(s,t)) {
            fill(prog.begin(), prog.end(), 0);
            long long f;
            while((f = dfs(s,t,LLONG_MAX)) > 0) {
                flow += f;
            }
        }
        return flow;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int R, C;
    while(cin >> R >> C) {
        vector<vector<int>> val(R+1);
        vector<vector<int>> id(R+1);
        int N = 0;
        for(int r = 1; r <= R; r++) {
            int cols = (r % 2 == 1) ? C : C+1;
            val[r].resize(cols+1);
            id[r].resize(cols+1, -1);
            for(int c = 1; c <= cols; c++) {
                cin >> val[r][c];
                id[r][c] = N++;
            }
        }
        int V = 2 + 2*N;
        Dinic dinic(V);
        const long long INF = (long long)4e18;
        // Internal edges (vertex capacities)
        for(int r = 1; r <= R; r++) {
            int cols = (r % 2 == 1) ? C : C+1;
            for(int c = 1; c <= cols; c++) {
                int u = id[r][c];
                int u_in = 2 + u*2;
                int u_out = 2 + u*2 + 1;
                dinic.add_edge(u_in, u_out, val[r][c]);
            }
        }
        // Adjacency edges (infinite capacity)
        for(int r = 1; r <= R; r++) {
            int cols = (r % 2 == 1) ? C : C+1;
            for(int c = 1; c <= cols; c++) {
                int u = id[r][c];
                int u_out = 2 + u*2 + 1;
                // left
                if(c > 1) {
                    int v = id[r][c-1];
                    int v_in = 2 + v*2;
                    dinic.add_edge(u_out, v_in, INF);
                }
                // right
                if(c < cols) {
                    int v = id[r][c+1];
                    int v_in = 2 + v*2;
                    dinic.add_edge(u_out, v_in, INF);
                }
                // up and down
                if(r % 2 == 1) { // odd row
                    // up
                    if(r > 1) {
                        int v = id[r-1][c];
                        if(v != -1) {
                            int v_in = 2 + v*2;
                            dinic.add_edge(u_out, v_in, INF);
                        }
                        v = id[r-1][c+1];
                        if(v != -1) {
                            int v_in = 2 + v*2;
                            dinic.add_edge(u_out, v_in, INF);
                        }
                    }
                    // down
                    if(r < R) {
                        int v = id[r+1][c];
                        if(v != -1) {
                            int v_in = 2 + v*2;
                            dinic.add_edge(u_out, v_in, INF);
                        }
                        v = id[r+1][c+1];
                        if(v != -1) {
                            int v_in = 2 + v*2;
                            dinic.add_edge(u_out, v_in, INF);
                        }
                    }
                } else { // even row
                    // up
                    if(r > 1) {
                        if(c-1 >= 1) {
                            int v = id[r-1][c-1];
                            if(v != -1) {
                                int v_in = 2 + v*2;
                                dinic.add_edge(u_out, v_in, INF);
                            }
                        }
                        if(c <= C) {
                            int v = id[r-1][c];
                            if(v != -1) {
                                int v_in = 2 + v*2;
                                dinic.add_edge(u_out, v_in, INF);
                            }
                        }
                    }
                    // down
                    if(r < R) {
                        if(c-1 >= 1) {
                            int v = id[r+1][c-1];
                            if(v != -1) {
                                int v_in = 2 + v*2;
                                dinic.add_edge(u_out, v_in, INF);
                            }
                        }
                        if(c <= C) {
                            int v = id[r+1][c];
                            if(v != -1) {
                                int v_in = 2 + v*2;
                                dinic.add_edge(u_out, v_in, INF);
                            }
                        }
                    }
                }
            }
        }
        // Source and sink
        int source = 0, sink = 1;
        // Top row (always odd, C columns)
        for(int c = 1; c <= C; c++) {
            int u = id[1][c];
            int u_in = 2 + u*2;
            dinic.add_edge(source, u_in, INF);
        }
        // Bottom row
        int bottom_cols = (R % 2 == 1) ? C : C+1;
        for(int c = 1; c <= bottom_cols; c++) {
            int u = id[R][c];
            int u_out = 2 + u*2 + 1;
            dinic.add_edge(u_out, sink, INF);
        }
        long long ans = dinic.max_flow(source, sink);
        cout << ans << '\n';
    }
    return 0;
}
