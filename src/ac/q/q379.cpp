#include <bits/stdc++.h>
using namespace std;

struct EdgeInfo {
    int u, v;
    long long w0;          // initial weight
};

struct Update {
    int idx;               // edge index in edges[]
    long long inc;         // increment
};

struct DSU {
    vector<int> p, r;
    DSU(int n = 0) { init(n); }
    void init(int n) {
        p.resize(n);
        r.assign(n, 0);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) ++r[a];
        return true;
    }
};

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M, Q;
    while (cin >> N >> M >> Q) {
        vector<EdgeInfo> edges(M);
        unordered_map<long long, int> mp;
        mp.reserve(M * 2);
        for (int i = 0; i < M; ++i) {
            int s, t; ll c;
            cin >> s >> t >> c;
            edges[i] = {s, t, c};
            long long key = ( (long long) s << 32 ) | (unsigned int) t;
            mp[key] = i;
        }

        vector<Update> ups(Q);
        for (int i = 0; i < Q; ++i) {
            int qs, qt; ll qc;
            cin >> qs >> qt >> qc;
            long long key = ( (long long) qs << 32 ) | (unsigned int) qt;
            int idx = mp[key];
            ups[i] = {idx, qc};
        }

        ll K;  cin >> K;

        // auxiliary array for current weights
        vector<ll> curW(M);

        auto mstWeight = [&](int t)->ll{
            // copy initial weights
            for (int i = 0; i < M; ++i) curW[i] = edges[i].w0;
            // apply first t updates
            for (int i = 0; i < t; ++i) {
                curW[ ups[i].idx ] += ups[i].inc;
            }
            // build vector for Kruskal
            struct Item { ll w; int u, v; };
            static vector<Item> vec;
            vec.clear();
            vec.reserve(M);
            for (int i = 0; i < M; ++i) {
                vec.push_back({curW[i], edges[i].u, edges[i].v});
            }
            sort(vec.begin(), vec.end(),
                 [](const Item& a, const Item& b){ return a.w < b.w; });

            DSU dsu(N);
            ll total = 0;
            int taken = 0;
            for (const auto& e : vec) {
                if (dsu.unite(e.u, e.v)) {
                    total += e.w;
                    if (++taken == N-1) break;
                }
            }
            return total;
        };

        ll initWeight = mstWeight(0);
        if (initWeight > K) {
            cout << 0 << '\n';
            continue;
        }
        ll finalWeight = mstWeight(Q);
        if (finalWeight <= K) {
            cout << -1 << '\n';
            continue;
        }

        int lo = 1, hi = Q;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (mstWeight(mid) > K) hi = mid;
            else lo = mid + 1;
        }
        cout << lo << '\n';
    }
    return 0;
}
