#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        vector<vector<pair<int,int>>> adj(N+1);
        for (int i = 0; i < N-1; i++) {
            int u, v, d;
            cin >> u >> v >> d;
            adj[u].push_back({v, d});
            adj[v].push_back({u, d});
        }
        vector<int> type(N+1);
        vector<int> commercial;
        for (int i = 1; i <= N; i++) {
            cin >> type[i];
            if (type[i] == 1) commercial.push_back(i);
        }
        if (commercial.empty()) {
            for (int i = 1; i <= N; i++) {
                if (type[i] == 0) cout << 0 << '\n';
            }
            continue;
        }
        int TotalCom = commercial.size();
        
        // BFS to root the tree at 1
        vector<int> parent(N+1, 0);
        vector<int> parentWeight(N+1, 0);
        vector<int> depth(N+1, 0);
        vector<vector<pair<int,int>>> children(N+1);
        vector<int> bfsOrder;
        bfsOrder.reserve(N);
        queue<int> q;
        q.push(1);
        parent[1] = 0;
        depth[1] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            bfsOrder.push_back(u);
            for (const auto& edge : adj[u]) {
                int v = edge.first;
                int w = edge.second;
                if (v == parent[u]) continue;
                parent[v] = u;
                parentWeight[v] = w;
                depth[v] = depth[u] + 1;
                children[u].push_back({v, w});
                q.push(v);
            }
        }
        
        // Compute subCom (commercial count in subtree)
        vector<int> subCom(N+1, 0);
        for (int i = 1; i <= N; i++) {
            if (type[i] == 1) subCom[i] = 1;
        }
        for (int i = N-1; i >= 0; i--) {
            int u = bfsOrder[i];
            for (const auto& edge : children[u]) {
                int v = edge.first;
                subCom[u] += subCom[v];
            }
        }
        
        // Determine inT and total weight W of minimal subtree T
        vector<char> inT(N+1, false);
        for (int i = 1; i <= N; i++) {
            if (type[i] == 1) inT[i] = true;
        }
        long long W = 0;
        vector<vector<pair<int,int>>> adjT(N+1);
        for (int v = 2; v <= N; v++) {
            int u = parent[v];
            int w = parentWeight[v];
            if (subCom[v] > 0 && TotalCom - subCom[v] > 0) {
                inT[u] = true;
                inT[v] = true;
                W += w;
                adjT[u].push_back({v, w});
                adjT[v].push_back({u, w});
            }
        }
        
        // Compute eccentricities for nodes in T
        vector<long long> ecc(N+1, 0);
        if (TotalCom == 1) {
            ecc[commercial[0]] = 0;
        } else {
            int start = -1;
            for (int i = 1; i <= N; i++) {
                if (inT[i]) { start = i; break; }
            }
            // Lambda to find farthest node and fill distances
            auto dfs_farthest = [&](int src, vector<long long>& dist) -> int {
                dist.assign(N+1, -1);
                stack<int> st;
                st.push(src);
                dist[src] = 0;
                int farthest = src;
                long long maxDist = 0;
                while (!st.empty()) {
                    int u = st.top(); st.pop();
                    if (dist[u] > maxDist) {
                        maxDist = dist[u];
                        farthest = u;
                    }
                    for (const auto& edge : adjT[u]) {
                        int v = edge.first;
                        int w = edge.second;
                        if (dist[v] == -1) {
                            dist[v] = dist[u] + w;
                            st.push(v);
                        }
                    }
                }
                return farthest;
            };
            vector<long long> distA, distB;
            int A = dfs_farthest(start, distA);
            int B = dfs_farthest(A, distA); // distA now holds distances from A
            dfs_farthest(B, distB); // distB holds distances from B
            for (int i = 1; i <= N; i++) {
                if (inT[i]) {
                    ecc[i] = max(distA[i], distB[i]);
                }
            }
        }
        
        // Compute downDist, downNode, best1, best2
        const long long INF = (1LL << 60);
        vector<long long> downDist(N+1, INF);
        vector<int> downNode(N+1, -1);
        vector<long long> best1Dist(N+1, INF), best2Dist(N+1, INF);
        vector<int> best1Node(N+1, -1), best2Node(N+1, -1);
        
        for (int i = 1; i <= N; i++) {
            if (inT[i]) {
                downDist[i] = 0;
                downNode[i] = i;
            }
        }
        
        // Process in reverse BFS order (post-order)
        for (int i = N-1; i >= 0; i--) {
            int u = bfsOrder[i];
            // Update downDist from children
            for (const auto& edge : children[u]) {
                int v = edge.first;
                int w = edge.second;
                if (downDist[v] != INF) {
                    long long cand = downDist[v] + w;
                    if (cand < downDist[u]) {
                        downDist[u] = cand;
                        downNode[u] = downNode[v];
                    }
                }
            }
            // Compute best1 and best2 for u (self + children)
            long long b1 = INF, b2 = INF;
            int n1 = -1, n2 = -1;
            auto consider = [&](long long dist, int node) {
                if (dist < b1) {
                    b2 = b1; n2 = n1;
                    b1 = dist; n1 = node;
                } else if (dist < b2) {
                    b2 = dist; n2 = node;
                }
            };
            if (inT[u]) consider(0, u);
            for (const auto& edge : children[u]) {
                int v = edge.first;
                int w = edge.second;
                if (downDist[v] != INF) {
                    consider(downDist[v] + w, downNode[v]);
                }
            }
            best1Dist[u] = b1; best1Node[u] = n1;
            best2Dist[u] = b2; best2Node[u] = n2;
        }
        
        // Compute upDist, upNode
        vector<long long> upDist(N+1, INF);
        vector<int> upNode(N+1, -1);
        upDist[1] = INF; upNode[1] = -1;
        
        // Process in BFS order (pre-order)
        for (int u : bfsOrder) {
            for (const auto& edge : children[u]) {
                int v = edge.first;
                int w = edge.second;
                // Best from u excluding v's subtree
                long long bestExclDist;
                int bestExclNode;
                if (downNode[v] != -1 && best1Node[u] == downNode[v]) {
                    bestExclDist = best2Dist[u];
                    bestExclNode = best2Node[u];
                } else {
                    bestExclDist = best1Dist[u];
                    bestExclNode = best1Node[u];
                }
                // Combine with upDist[u]
                long long candidateDist;
                int candidateNode;
                if (bestExclDist <= upDist[u]) {
                    candidateDist = bestExclDist;
                    candidateNode = bestExclNode;
                } else {
                    candidateDist = upDist[u];
                    candidateNode = upNode[u];
                }
                if (candidateDist != INF) {
                    upDist[v] = candidateDist + w;
                    upNode[v] = candidateNode;
                } else {
                    upDist[v] = INF;
                    upNode[v] = -1;
                }
            }
        }
        
        // Output answers for residential cities
        for (int i = 1; i <= N; i++) {
            if (type[i] == 0) {
                long long d;
                int r;
                if (downDist[i] <= upDist[i]) {
                    d = downDist[i];
                    r = downNode[i];
                } else {
                    d = upDist[i];
                    r = upNode[i];
                }
                long long ans = d + 2 * W - ecc[r];
                cout << ans << '\n';
            }
        }
    }
    return 0;
}
