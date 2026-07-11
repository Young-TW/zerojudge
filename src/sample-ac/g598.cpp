#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstdio>

using namespace std;

const int MAXN = 20005;

int parent[MAXN];
int dist[MAXN];

int find(int i) {
    if (parent[i] == i) return i;
    int root = find(parent[i]);
    dist[i] ^= dist[parent[i]];
    parent[i] = root;
    return root;
}

bool unite(int u, int v) {
    int ru = find(u);
    int rv = find(v);
    if (ru == rv) {
        return dist[u] ^ dist[v] == 1;
    }
    parent[ru] = rv;
    dist[ru] = dist[u] ^ dist[v] ^ 1;
    return true;
}

char buf[1 << 20];
int p_idx = 0, len = 0;

inline char gc() {
    if (p_idx == len) {
        len = fread(buf, 1, sizeof(buf), stdin);
        p_idx = 0;
        if (len == 0) return EOF;
    }
    return buf[p_idx++];
}

inline int readInt() {
    char c = gc();
    while (c != '-' && (c < '0' || c > '9')) {
        if (c == EOF) return -1;
        c = gc();
    }
    int x = 0, sign = 1;
    if (c == '-') {
        sign = -1;
        c = gc();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return x * sign;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    while ((n = readInt()) != -1) {
        m = readInt();
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            dist[i] = 0;
        }
        
        bool original_bipartite = true;
        for (int i = 0; i < m; ++i) {
            int u = readInt();
            int v = readInt();
            if (!unite(u, v)) {
                original_bipartite = false;
            }
        }
        
        int p_count = readInt();
        int k = readInt();
        
        for (int i = 1; i <= p_count; ++i) {
            vector<pair<int, int>> edges(k);
            vector<int> nodes;
            for (int j = 0; j < k; ++j) {
                int u = readInt();
                int v = readInt();
                edges[j] = {u, v};
                nodes.push_back(u);
                nodes.push_back(v);
            }
            
            if (!original_bipartite) {
                cout << i << "\n";
                continue;
            }
            
            sort(nodes.begin(), nodes.end());
            nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
            int sz = nodes.size();
            
            auto get_id = [&](int node) {
                return lower_bound(nodes.begin(), nodes.end(), node) - nodes.begin();
            };
            
            vector<vector<pair<int, int>>> adj(sz);
            for (int j = 0; j < sz; ++j) {
                for (int l = j + 1; l < sz; ++l) {
                    int u = nodes[j], v = nodes[l];
                    int ru = find(u), rv = find(v);
                    if (ru == rv) {
                        int w = dist[u] ^ dist[v];
                        adj[j].push_back({l, w});
                        adj[l].push_back({j, w});
                    }
                }
            }
            for (int j = 0; j < k; ++j) {
                int u = get_id(edges[j].first);
                int v = get_id(edges[j].second);
                adj[u].push_back({v, 1});
                adj[v].push_back({u, 1});
            }
            
            vector<int> color(sz, -1);
            bool is_bipartite = true;
            for (int j = 0; j < sz; ++j) {
                if (color[j] == -1) {
                    color[j] = 0;
                    queue<int> q;
                    q.push(j);
                    while (!q.empty()) {
                        int u = q.front(); q.pop();
                        for (auto& edge : adj[u]) {
                            int v = edge.first, w = edge.second;
                            if (color[v] == -1) {
                                color[v] = color[u] ^ w;
                                q.push(v);
                            } else if (color[v] != (color[u] ^ w)) {
                                is_bipartite = false;
                                break;
                            }
                        }
                        if (!is_bipartite) break;
                    }
                }
                if (!is_bipartite) break;
            }
            if (!is_bipartite) {
                cout << i << "\n";
            }
        }
    }
    return 0;
}
