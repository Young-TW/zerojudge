#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v;
    long long w;
};

int parent[1005];

int find_set(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find_set(parent[i]);
}

void union_set(int i, int j) {
    int root_i = find_set(i);
    int root_j = find_set(j);
    if (root_i != root_j) {
        parent[root_i] = root_j;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    while (cin >> n >> m && (n || m)) {
        vector<Edge> edges(m);
        for (int i = 0; i < m; ++i) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
        }
        
        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.w < b.w;
        });
        
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
        
        vector<long long> ans;
        for (int i = 0; i < m; ++i) {
            int u = edges[i].u;
            int v = edges[i].v;
            if (find_set(u) == find_set(v)) {
                ans.push_back(edges[i].w);
            } else {
                union_set(u, v);
            }
        }
        
        if (ans.empty()) {
            cout << "forest\n";
        } else {
            bool first = true;
            for (long long w : ans) {
                if (!first) cout << " ";
                cout << w;
                first = false;
            }
            cout << "\n";
        }
    }
    
    return 0;
}
