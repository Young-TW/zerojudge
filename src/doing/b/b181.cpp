#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

struct Edge {
    string u, v;
    int w;
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

map<string, string> parent;

string find(const string& i) {
    if (parent[i] == i) return i;
    return parent[i] = find(parent[i]);
}

void unite(const string& i, const string& j) {
    string root_i = find(i);
    string root_j = find(j);
    if (root_i != root_j) {
        parent[root_i] = root_j;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    while (cin >> n >> m) {
        vector<Edge> edges(m);
        parent.clear();
        
        for (int i = 0; i < m; ++i) {
            string u, v;
            int w;
            cin >> u >> v >> w;
            if (u > v) swap(u, v);
            edges[i] = {u, v, w};
            parent[u] = u;
            parent[v] = v;
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
            cout << "(" << mst[i].u << " " << mst[i].v << ")";
            if (i < mst.size() - 1) cout << " ";
        }
        cout << "\n";
        cout << total_cost << "\n";
    }
    
    return 0;
}
