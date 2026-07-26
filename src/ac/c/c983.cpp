#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev;
    int cap;
    long long cost;
    Edge(int _to, int _rev, int _cap, long long _cost)
        : to(_to), rev(_rev), cap(_cap), cost(_cost) {}
};

struct MinCostFlow {
    int N;
    vector<vector<Edge>> G;
    MinCostFlow(int n) : N(n), G(n) {}

    void addEdge(int s, int t, int cap, long long cost) {
        Edge a(t, (int)G[t].size(), cap, cost);
        Edge b(s, (int)G[s].size(), 0, -cost);
        G[s].push_back(a);
        G[t].push_back(b);
    }

    // returns (flow, cost)
    pair<int,long long> minCostMaxFlow(int s, int t, int maxf) {
        const long long INF = (1LL<<60);
        long long cost = 0;
        int flow = 0;
        vector<long long> h(N,0);          // potentials
        vector<long long> dist(N);
        vector<int> prevv(N), preve(N);

        while (flow < maxf) {
            // Dijkstra with potentials
            fill(dist.begin(), dist.end(), INF);
            dist[s] = 0;
            using P = pair<long long,int>;
            priority_queue<P, vector<P>, greater<P>> pq;
            pq.emplace(0,s);
            while (!pq.empty()) {
                auto [d,v] = pq.top(); pq.pop();
                if (d != dist[v]) continue;
                for (int i=0;i<(int)G[v].size();++i) {
                    Edge &e = G[v][i];
                    if (e.cap==0) continue;
                    long long nd = d + e.cost + h[v] - h[e.to];
                    if (dist[e.to] > nd) {
                        dist[e.to] = nd;
                        prevv[e.to] = v;
                        preve[e.to] = i;
                        pq.emplace(nd, e.to);
                    }
                }
            }
            if (dist[t] == INF) break;               // no path
            // real shortest path cost
            long long realCost = dist[t] + h[t] - h[s];
            if (realCost >= 0) break;                // no negative‑cost augmenting path

            for (int v=0; v<N; ++v) if (dist[v] < INF) h[v] += dist[v];

            int d = maxf - flow;
            for (int v=t; v!=s; v=prevv[v]) {
                d = min(d, G[prevv[v]][preve[v]].cap);
            }
            flow += d;
            cost += (long long)d * realCost;
            for (int v=t; v!=s; v=prevv[v]) {
                Edge &e = G[prevv[v]][preve[v]];
                e.cap -= d;
                G[v][e.rev].cap += d;
            }
        }
        return {flow, cost};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N;
        long long M;
        int K;
        cin >> N >> M >> K;
        vector<long long> t(N);
        vector<int> p(N);
        for (int i=0;i<N;++i) cin >> t[i];
        long long total = 0;
        for (int i=0;i<N;++i) {
            cin >> p[i];
            total += p[i];
        }

        int cap = K - 1;               // allowed concurrent alarms
        if (cap <= 0) {                // K == 1  → must switch off all
            cout << total << "\n";
            continue;
        }

        // coordinate compression
        vector<long long> xs;
        xs.reserve(2*N);
        for (int i=0;i<N;++i) {
            xs.push_back(t[i]);
            xs.push_back(t[i] + M);
        }
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        int L = (int)xs.size();

        auto idx = [&](long long x)->int{
            return (int)(lower_bound(xs.begin(), xs.end(), x) - xs.begin());
        };

        MinCostFlow mcf(L);
        // time line edges
        for (int i=0;i<L-1;++i) {
            mcf.addEdge(i, i+1, cap, 0);
        }
        // alarm edges
        for (int i=0;i<N;++i) {
            int u = idx(t[i]);
            int v = idx(t[i] + M);
            mcf.addEdge(u, v, 1, - (long long)p[i]);
        }

        int source = 0, sink = L-1;
        auto res = mcf.minCostMaxFlow(source, sink, cap);
        long long answer = total + res.second;   // res.second ≤ 0
        cout << answer << "\n";
    }
    return 0;
}
