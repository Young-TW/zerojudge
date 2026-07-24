#include <bits/stdc++.h>
using namespace std;

struct PairHash {
    size_t operator()(const pair<int,int>& p) const noexcept {
        return (static_cast<size_t>(p.first) << 16) ^ static_cast<size_t>(p.second);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while ( (cin >> n >> m) ) {
        // mapping (line id, station number) -> vertex index
        unordered_map<pair<int,int>, int, PairHash> id;
        vector<pair<int,int>> rev;               // for debugging, not needed
        int vertexCnt = 0;

        struct Edge { int u, v, w; };
        vector<Edge> edges;

        // read lines
        for (int li = 0; li < n; ++li) {
            int lineId, k;
            cin >> lineId >> k;
            vector<int> s(k+1);
            for (int p = 1; p <= k; ++p) cin >> s[p];
            // create vertices
            for (int p = 1; p <= k; ++p) {
                pair<int,int> key = {lineId, p};
                if (!id.count(key)) {
                    id[key] = vertexCnt++;
                    rev.emplace_back(lineId, p);
                }
            }
            // edges between consecutive stations
            for (int p = 2; p <= k; ++p) {
                int travel = s[p];
                int w = travel + 1;
                int u = id[{lineId, p-1}];
                int v = id[{lineId, p}];
                edges.push_back({u, v, w});
            }
        }

        // read transfers
        for (int i = 0; i < m; ++i) {
            int li, pi, lj, pj;
            cin >> li >> pi >> lj >> pj;
            int u = id[{li, pi}];
            int v = id[{lj, pj}];
            edges.push_back({u, v, 0});
        }

        const int INF = 1e9;
        vector<vector<int>> dist(vertexCnt, vector<int>(vertexCnt, INF));
        for (int v = 0; v < vertexCnt; ++v) dist[v][v] = 0;
        for (auto &e : edges) {
            if (e.w < dist[e.u][e.v]) {
                dist[e.u][e.v] = dist[e.v][e.u] = e.w;
            }
        }

        // Floyd‑Warshall
        for (int k = 0; k < vertexCnt; ++k) {
            for (int i = 0; i < vertexCnt; ++i) {
                if (dist[i][k] == INF) continue;
                for (int j = 0; j < vertexCnt; ++j) {
                    if (dist[k][j] == INF) continue;
                    int nd = dist[i][k] + dist[k][j];
                    if (nd < dist[i][j]) dist[i][j] = nd;
                }
            }
        }

        // five queries
        for (int q = 0; q < 5; ++q) {
            int hh, mm, li, pi, lj, pj;
            cin >> hh >> mm >> li >> pi >> lj >> pj;
            int src = id[{li, pi}];
            int dst = id[{lj, pj}];
            cout << dist[src][dst] << "\n";
        }
    }
    return 0;
}
