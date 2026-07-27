#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, sz;
    int maxComp;
    DSU(int n = 0) { init(n); }
    void init(int n) {
        p.resize(n + 1);
        sz.assign(n + 1, 1);
        for (int i = 1; i <= n; ++i) p[i] = i;
        maxComp = n ? 1 : 0;
    }
    int find(int x) {
        while (p[x] != x) {
            p[x] = p[p[x]];
            x = p[x];
        }
        return x;
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        if (sz[a] > maxComp) maxComp = sz[a];
    }
};

struct Meteor {
    int t;
    int id;          // edge index (1‑based)
    bool operator<(const Meteor& o) const { return t < o.t; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int INF_TIME = 2000000000;   // larger than any possible t

    int N, E, R, M;
    while (cin >> N >> E >> R >> M) {
        vector<pair<int,int>> edges(E + 1);
        for (int i = 1; i <= E; ++i) {
            int a, b; cin >> a >> b;
            edges[i] = {a, b};
        }

        vector<Meteor> meteors(R);
        vector<int> destroy_time(E + 1, INF_TIME);
        for (int i = 0; i < R; ++i) {
            int t, p; cin >> t >> p;
            meteors[i] = {t, p};
            destroy_time[p] = t;
        }
        sort(meteors.begin(), meteors.end());   // by time ascending

        DSU dsu(N);
        for (int id = 1; id <= E; ++id) {
            if (destroy_time[id] == INF_TIME) {
                dsu.unite(edges[id].first, edges[id].second);
            }
        }

        vector<int> maxSize(R + 1);
        maxSize[R] = dsu.maxComp;                // after all deletions

        for (int i = R - 1; i >= 0; --i) {
            int eid = meteors[i].id;
            dsu.unite(edges[eid].first, edges[eid].second);
            maxSize[i] = dsu.maxComp;
        }

        vector<int> times(R);
        for (int i = 0; i < R; ++i) times[i] = meteors[i].t;

        for (int i = 0; i < M; ++i) {
            int c; cin >> c;
            int low = 0, high = R + 1;           // high is exclusive
            while (low < high) {
                int mid = (low + high) >> 1;
                if (maxSize[mid] < c) high = mid;
                else low = mid + 1;
            }
            int idx = low;                       // first position where maxSize < c
            if (idx == 0) {
                cout << -1 << '\n';
            } else if (idx == R + 1) {
                cout << "INF\n";
            } else {
                cout << times[idx - 1] << '\n';
            }
        }
    }
    return 0;
}
