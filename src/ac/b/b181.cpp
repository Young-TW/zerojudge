#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, w;
};

bool cmpByWeight(const Edge& a, const Edge& b) {
    if (a.w != b.w) return a.w < b.w;
    if (a.u != b.u) return a.u < b.u;
    return a.v < b.v;
}

bool cmpByName(const Edge& a, const Edge& b) {
    if (a.u != b.u) return a.u < b.u;
    return a.v < b.v;
}

vector<int> parent;

int find(int i) {
    while (parent[i] != i) {
        parent[i] = parent[parent[i]];
        i = parent[i];
    }
    return i;
}

void unite(int i, int j) {
    int ri = find(i), rj = find(j);
    if (ri != rj) parent[ri] = rj;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    while (cin >> n >> m) {
        vector<Edge> edges(m);
        parent.assign(n + 1, 0);
        for (int i = 1; i <= n; ++i) parent[i] = i;

        for (int i = 0; i < m; ++i) {
            string su, sv;
            int w;
            cin >> su >> sv >> w;
            int u = stoi(su.substr(1));
            int v = stoi(sv.substr(1));
            if (u > v) swap(u, v);
            edges[i] = {u, v, w};
        }

        sort(edges.begin(), edges.end(), cmpByWeight);

        vector<Edge> mst;
        int total_cost = 0;

        for (int i = 0; i < m; ++i) {
            if (find(edges[i].u) != find(edges[i].v)) {
                unite(edges[i].u, edges[i].v);
                mst.push_back(edges[i]);
                total_cost += edges[i].w;
            }
        }

        sort(mst.begin(), mst.end(), cmpByName);

        for (size_t i = 0; i < mst.size(); ++i) {
            cout << "(W" << mst[i].u << " W" << mst[i].v << ")";
            if (i < mst.size() - 1) cout << " ";
        }
        cout << "\n";
        cout << total_cost << "\n";
    }

    return 0;
}
