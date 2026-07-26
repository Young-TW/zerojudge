#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<vector<int>> adj;
vector<vector<bool>> reach; // reach[u][v] = u can reach v

// Hopcroft-Karp on bipartite graph with L = {0..nL-1}, R = {0..nR-1}
// edges: adjL[u] = list of v in R
struct HopcroftKarp {
    int nL, nR;
    vector<vector<int>> adjL;
    vector<int> pairL, pairR, dist;
    
    HopcroftKarp(int nL, int nR) : nL(nL), nR(nR), adjL(nL), pairL(nL, -1), pairR(nR, -1), dist(nL) {}
    
    bool bfs() {
        queue<int> q;
        bool found = false;
        for (int u = 0; u < nL; u++) {
            if (pairL[u] == -1) { dist[u] = 0; q.push(u); }
            else dist[u] = -1;
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adjL[u]) {
                int pu = pairR[v];
                if (pu != -1 && dist[pu] == -1) {
                    dist[pu] = dist[u] + 1;
                    q.push(pu);
                }
                if (pu == -1) found = true;
            }
        }
        return found;
    }
    
    vector<int> ptr;
    bool dfs(int u) {
        for (int& i = ptr[u]; i < (int)adjL[u].size(); i++) {
            int v = adjL[u][i];
            int pu = pairR[v];
            if (pu == -1 || (dist[pu] == dist[u] + 1 && dfs(pu))) {
                pairL[u] = v;
                pairR[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }
    
    int solve() {
        int matching = 0;
        ptr.assign(nL, 0);
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            for (int u = 0; u < nL; u++)
                if (pairL[u] == -1 && dfs(u))
                    matching++;
        }
        return matching;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (cin >> N >> M) {
        adj.assign(N, vector<int>());
        for (int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            adj[u].push_back(v);
        }
        
        // Compute transitive closure
        reach.assign(N, vector<bool>(N, false));
        for (int u = 0; u < N; u++) {
            // BFS/DFS from u
            vector<bool> vis(N, false);
            queue<int> q;
            q.push(u);
            vis[u] = true;
            while (!q.empty()) {
                int x = q.front(); q.pop();
                for (int y : adj[x]) {
                    if (!vis[y]) {
                        vis[y] = true;
                        reach[u][y] = true;
                        q.push(y);
                    }
                }
            }
        }
        
        // Build full bipartite graph and find max matching
        auto maxMatching = [&](vector<int>& nodes) -> int {
            // nodes: subset of vertices to consider
            int n = nodes.size();
            // Map node to index
            vector<int> idx(N, -1);
            for (int i = 0; i < n; i++) idx[nodes[i]] = i;
            
            HopcroftKarp hk(n, n);
            for (int i = 0; i < n; i++) {
                int u = nodes[i];
                for (int j = 0; j < n; j++) {
                    int v = nodes[j];
                    if (u != v && reach[u][v]) {
                        hk.adjL[i].push_back(j);
                    }
                }
            }
            return hk.solve();
        };
        
        vector<int> allNodes(N);
        iota(allNodes.begin(), allNodes.end(), 0);
        int fullMatching = maxMatching(allNodes);
        int alpha = N - fullMatching;
        
        // For each v, check if v can be in max antichain
        string ans(N, '0');
        for (int v = 0; v < N; v++) {
            // S = {u : u != v, !reach[u][v], !reach[v][u]}
            vector<int> S;
            for (int u = 0; u < N; u++) {
                if (u == v) continue;
                if (reach[u][v] || reach[v][u]) continue;
                S.push_back(u);
            }
            int m = maxMatching(S);
            if ((int)S.size() - m == alpha - 1) {
                ans[v] = '1';
            }
        }
        
        cout << alpha << "\n" << ans << "\n";
    }
    
    return 0;
}
