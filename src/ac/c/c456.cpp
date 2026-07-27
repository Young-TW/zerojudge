#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, sz;
    DSU(int n = 0) { init(n); }
    void init(int n) {
        p.resize(n);
        sz.assign(n, 1);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        while (p[x] != x) { p[x] = p[p[x]]; x = p[x]; }
        return x;
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        return true;
    }
    int size(int x) { return sz[find(x)]; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M) {
        vector<vector<int>> adj(N);
        for (int i = 0; i < M; ++i) {
            int x, y;
            cin >> x >> y;
            --x; --y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        
        // Compute core numbers
        vector<int> deg(N);
        for (int i = 0; i < N; ++i) deg[i] = (int)adj[i].size();
        
        vector<int> core(N, 0);
        vector<char> removed(N, 0);
        using P = pair<int,int>;
        priority_queue<P, vector<P>, greater<P>> pq;
        for (int i = 0; i < N; ++i) pq.emplace(deg[i], i);
        
        while (!pq.empty()) {
            auto [d, v] = pq.top(); pq.pop();
            if (removed[v]) continue;
            if (d != deg[v]) continue;  // outdated entry
            core[v] = d;
            removed[v] = 1;
            for (int u : adj[v]) {
                if (!removed[u] && deg[u] > d) {
                    deg[u]--;
                    pq.emplace(deg[u], u);
                }
            }
        }
        
        // Group vertices by core number
        int maxCore = 0;
        for (int v = 0; v < N; ++v) maxCore = max(maxCore, core[v]);
        vector<vector<int>> bucket(maxCore + 1);
        for (int v = 0; v < N; ++v) bucket[core[v]].push_back(v);
        
        // DSU sweep from high k to low k
        DSU dsu(N);
        vector<char> active(N, 0);
        long long answer = 0;
        int curMaxComp = 0;
        
        for (int k = maxCore; k >= 0; --k) {
            for (int v : bucket[k]) {
                active[v] = 1;
                curMaxComp = max(curMaxComp, 1);
                for (int u : adj[v]) {
                    if (active[u]) {
                        dsu.unite(v, u);
                    }
                }
                curMaxComp = max(curMaxComp, dsu.size(v));
            }
            answer = max(answer, 1LL * k * curMaxComp);
        }
        
        cout << answer << '\n';
    }
    return 0;
}
