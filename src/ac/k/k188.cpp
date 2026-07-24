#include <bits/stdc++.h>
using namespace std;

struct DSU_Biconnected {
    vector<int> dsu_2ecc;   // representative of 2‑vertex‑connected component
    vector<int> dsu_cc;     // representative of connected component
    vector<int> dsu_cc_size;
    vector<int> parent;     // parent in the auxiliary forest
    vector<int> last_visit;
    int lca_iteration;

    DSU_Biconnected(int n = 0) { init(n); }

    void init(int n) {
        dsu_2ecc.resize(n);
        dsu_cc.resize(n);
        dsu_cc_size.assign(n, 1);
        parent.assign(n, -1);
        last_visit.assign(n, 0);
        iota(dsu_2ecc.begin(), dsu_2ecc.end(), 0);
        iota(dsu_cc.begin(), dsu_cc.end(), 0);
        lca_iteration = 0;
    }

    int find_2ecc(int v) {
        if (v == -1) return -1;
        if (dsu_2ecc[v] == v) return v;
        return dsu_2ecc[v] = find_2ecc(dsu_2ecc[v]);
    }

    int find_cc(int v) {
        v = find_2ecc(v);
        if (dsu_cc[v] == v) return v;
        return dsu_cc[v] = find_cc(dsu_cc[v]);
    }

    void make_root(int v) {
        v = find_2ecc(v);
        int root = v, child = -1;
        while (v != -1) {
            int p = find_2ecc(parent[v]);
            parent[v] = child;
            int cc = find_cc(v);
            dsu_cc[v] = root;
            child = v;
            v = p;
        }
        dsu_cc_size[root] = dsu_cc_size[child];
    }

    void merge_path(int a, int b) {
        ++lca_iteration;
        vector<int> path_a, path_b;
        int lca = -1;
        while (lca == -1) {
            if (a != -1) {
                a = find_2ecc(a);
                path_a.push_back(a);
                if (last_visit[a] == lca_iteration) {
                    lca = a;
                    break;
                }
                last_visit[a] = lca_iteration;
                a = parent[a];
            }
            if (b != -1) {
                b = find_2ecc(b);
                path_b.push_back(b);
                if (last_visit[b] == lca_iteration) {
                    lca = b;
                    break;
                }
                last_visit[b] = lca_iteration;
                b = parent[b];
            }
        }
        for (int v : path_a) {
            dsu_2ecc[v] = lca;
            if (v == lca) break;
        }
        for (int v : path_b) {
            dsu_2ecc[v] = lca;
            if (v == lca) break;
        }
    }

    void add_edge(int a, int b) {
        a = find_2ecc(a);
        b = find_2ecc(b);
        if (a == b) return;                     // already in same biconnected component
        int ca = find_cc(a);
        int cb = find_cc(b);
        if (ca != cb) {                          // different connected components
            // union by size
            if (dsu_cc_size[ca] > dsu_cc_size[cb]) {
                swap(a, b);
                swap(ca, cb);
            }
            make_root(a);
            parent[a] = b;
            dsu_cc[a] = b;
            dsu_cc_size[cb] += dsu_cc_size[a];
        } else {                                 // same connected component -> creates a cycle
            merge_path(a, b);
        }
    }

    bool same_2ecc(int a, int b) {
        return find_2ecc(a) == find_2ecc(b);
    }
};

struct Edge {
    int u, v;
    int w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        --edges[i].u; --edges[i].v;
    }
    sort(edges.begin(), edges.end(),
         [](const Edge& a, const Edge& b) { return a.w < b.w; });

    int q;
    cin >> q;
    vector<pair<int,int>> query(q);
    for (int i = 0; i < q; ++i) {
        cin >> query[i].first >> query[i].second;
        --query[i].first; --query[i].second;
    }

    // parallel binary search on edge index
    vector<int> lo(q, 0), hi(q, m);   // hi == m  => answer does not exist
    vector<int> mid(q);
    vector<vector<int>> bucket(m);   // bucket[mid] = list of query ids

    bool changed = true;
    while (changed) {
        changed = false;
        // clear buckets
        for (int i = 0; i < m; ++i) bucket[i].clear();

        for (int i = 0; i < q; ++i) {
            if (lo[i] < hi[i]) {
                changed = true;
                mid[i] = (lo[i] + hi[i]) >> 1;
                bucket[mid[i]].push_back(i);
            }
        }
        if (!changed) break;

        DSU_Biconnected dsu(n);
        for (int idx = 0; idx < m; ++idx) {
            dsu.add_edge(edges[idx].u, edges[idx].v);
            for (int id : bucket[idx]) {
                if (dsu.same_2ecc(query[id].first, query[id].second))
                    hi[id] = mid[id];
                else
                    lo[id] = mid[id] + 1;
            }
        }
    }

    // output answers
    for (int i = 0; i < q; ++i) {
        if (lo[i] >= m) {
            cout << -1 << '\n';
        } else {
            cout << edges[lo[i]].w << '\n';
        }
    }
    return 0;
}
