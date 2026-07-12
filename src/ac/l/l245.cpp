#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

struct Edge {
    int u, v, w;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    while (cin >> N >> M) {
        vector<Edge> edges(M + 1);
        int max_w = 0;
        for (int i = 1; i <= M; ++i) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
            if (edges[i].w > max_w) {
                max_w = edges[i].w;
            }
        }
        
        auto check = [&](int W) {
            vector<vector<int>> adj(N + 1);
            vector<int> in_deg(N + 1, 0);
            for (int i = 1; i <= M; ++i) {
                if (edges[i].w > W) {
                    adj[edges[i].u].push_back(edges[i].v);
                    in_deg[edges[i].v]++;
                }
            }
            queue<int> q;
            for (int i = 1; i <= N; ++i) {
                if (in_deg[i] == 0) q.push(i);
            }
            int cnt = 0;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                cnt++;
                for (int v : adj[u]) {
                    if (--in_deg[v] == 0) q.push(v);
                }
            }
            return cnt == N;
        };
        
        int l = 0, r = max_w;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (check(mid)) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        int W = l;
        
        vector<vector<int>> adj(N + 1);
        vector<int> in_deg(N + 1, 0);
        for (int i = 1; i <= M; ++i) {
            if (edges[i].w > W) {
                adj[edges[i].u].push_back(edges[i].v);
                in_deg[edges[i].v]++;
            }
        }
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int i = 1; i <= N; ++i) {
            if (in_deg[i] == 0) pq.push(i);
        }
        vector<int> topo(N + 1, 0);
        int time = 1;
        while (!pq.empty()) {
            int u = pq.top(); pq.pop();
            topo[u] = time++;
            for (int v : adj[u]) {
                if (--in_deg[v] == 0) pq.push(v);
            }
        }
        for (int i = 1; i <= N; ++i) {
            if (topo[i] == 0) topo[i] = time++;
        }
        
        vector<int> ans;
        for (int i = 1; i <= M; ++i) {
            if (edges[i].w <= W && topo[edges[i].u] > topo[edges[i].v]) {
                ans.push_back(i);
            }
        }
        
        cout << W << " " << ans.size() << "\n";
        for (int x : ans) {
            cout << x << "\n";
        }
    }
    return 0;
}
