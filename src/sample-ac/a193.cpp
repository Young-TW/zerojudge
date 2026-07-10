#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef __int128 lll;

const ll INF = (ll)4e18;

// Min-cost max-flow via successive shortest paths with Dijkstra + Johnson potentials.
struct MCMF {
    struct Edge { int to, rev; ll cap, cost; };
    vector<vector<Edge>> g;
    int n;
    MCMF(int n): g(n), n(n) {}
    void addEdge(int from, int to, ll cap, ll cost) {
        g[from].push_back({to, (int)g[to].size(), cap, cost});
        g[to].push_back({from, (int)g[from].size()-1, 0, -cost});
    }
    pair<ll,lll> mincost(int s, int t) {
        ll flow = 0; lll cost = 0;
        vector<ll> h(n, 0); // potentials; valid initially since all original costs >= 0
        while (true) {
            vector<ll> dist(n, INF);
            vector<int> pv(n, -1), pe(n, -1);
            dist[s] = 0;
            priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
            pq.push({0, s});
            while (!pq.empty()) {
                pair<ll,int> top = pq.top(); pq.pop();
                ll d = top.first; int v = top.second;
                if (d > dist[v]) continue;
                for (int i = 0; i < (int)g[v].size(); i++) {
                    Edge& e = g[v][i];
                    if (e.cap > 0) {
                        ll nd = d + e.cost + h[v] - h[e.to];
                        if (nd < dist[e.to]) {
                            dist[e.to] = nd;
                            pv[e.to] = v;
                            pe[e.to] = i;
                            pq.push({nd, e.to});
                        }
                    }
                }
            }
            if (dist[t] == INF) break;
            for (int v = 0; v < n; v++)
                if (dist[v] < INF) h[v] += dist[v];
            ll d = INF;
            for (int v = t; v != s; v = pv[v])
                d = min(d, g[pv[v]][pe[v]].cap);
            flow += d;
            cost += (lll)d * (lll)h[t];
            for (int v = t; v != s; v = pv[v]) {
                Edge& e = g[pv[v]][pe[v]];
                e.cap -= d;
                g[v][e.rev].cap += d;
            }
        }
        return {flow, cost};
    }
};

static void print128(lll x) {
    if (x == 0) { putchar('0'); return; }
    char buf[48]; int n = 0;
    while (x > 0) { buf[n++] = (char)('0' + (int)(x % 10)); x /= 10; }
    while (n--) putchar(buf[n]);
}

int main() {
    int N, M;
    while (scanf("%d %d", &N, &M) == 2) {
        // Construction (lower-bound min-cost circulation):
        //   Day edge (i-1)->i : lower bound A_i, cap INF, cost 0
        //   Volunteer edge T_j -> (S_j-1) : cap INF, cost C_j  (recruit = back-flow)
        //   Balance B(v)=L_out-L_in; B>0 => sink (v->ST, cap B); B<0 => source (SS->v, cap -B)
        int SS = N + 1, ST = N + 2;
        MCMF mcf(N + 3);
        vector<ll> b(N + 1, 0);
        for (int i = 1; i <= N; i++) {
            ll A;
            scanf("%lld", &A);
            mcf.addEdge(i - 1, i, INF, 0);
            b[i - 1] += A; // L_out of (i-1)
            b[i]     -= A; // L_in  of i
        }
        for (int j = 0; j < M; j++) {
            int S, T; ll C;
            scanf("%d %d %lld", &S, &T, &C);
            mcf.addEdge(T, S - 1, INF, C);
        }
        for (int v = 0; v <= N; v++) {
            if (b[v] > 0)      mcf.addEdge(v, ST, b[v], 0);
            else if (b[v] < 0) mcf.addEdge(SS, v, -b[v], 0);
        }
        pair<ll,lll> res = mcf.mincost(SS, ST);
        print128(res.second);
        putchar('\n');
    }
    return 0;
}
