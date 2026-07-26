#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
const int64 INF64 = (int64)4e18;          // larger than any possible answer

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while ( (cin >> N) ) {
        const int64 total = 1LL * N * N * N;
        vector<int64> val(total);
        for (int64 i = 0; i < total; ++i) {
            cin >> val[i];
        }

        // helper to convert 3D coordinates to linear index
        auto idx = [N](int x, int y, int z) -> int {
            return (x * N + y) * N + z;
        };

        vector<int64> dist(total, INF64);
        const int start = 0;
        const int target = (int)(total - 1);
        dist[start] = val[start];

        using Node = pair<int64,int>;               // (distance, vertex)
        priority_queue<Node, vector<Node>, greater<Node>> pq;
        pq.emplace(dist[start], start);

        const int dx[6] = { 1,-1, 0, 0, 0, 0 };
        const int dy[6] = { 0, 0, 1,-1, 0, 0 };
        const int dz[6] = { 0, 0, 0, 0, 1,-1 };

        while (!pq.empty()) {
            auto cur = pq.top(); pq.pop();
            int64 d = cur.first;
            int v = cur.second;
            if (d != dist[v]) continue;          // outdated entry
            if (v == target) break;              // optimal distance found

            int x = v / (N * N);
            int y = (v / N) % N;
            int z = v % N;

            for (int dir = 0; dir < 6; ++dir) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                int nz = z + dz[dir];
                if (nx < 0 || nx >= N || ny < 0 || ny >= N || nz < 0 || nz >= N)
                    continue;
                int nv = idx(nx, ny, nz);
                int64 nd = d + val[nv];
                if (nd < dist[nv]) {
                    dist[nv] = nd;
                    pq.emplace(nd, nv);
                }
            }
        }

        cout << dist[target] << '\n';
    }
    return 0;
}
