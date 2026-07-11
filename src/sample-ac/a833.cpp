#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    while (cin >> n >> m) {
        vector<int> head(n + m + 1, -1);
        vector<int> to(2 * m + 1);
        vector<int> nxt(2 * m + 1);
        int edge_cnt = 0;
        
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            if (w == 1) {
                to[edge_cnt] = v;
                nxt[edge_cnt] = head[u];
                head[u] = edge_cnt++;
            } else {
                int mid = n + i + 1;
                to[edge_cnt] = mid;
                nxt[edge_cnt] = head[u];
                head[u] = edge_cnt++;
                
                to[edge_cnt] = v;
                nxt[edge_cnt] = head[mid];
                head[mid] = edge_cnt++;
            }
        }
        
        vector<int> dist(n + m + 1, -1);
        queue<int> q;
        q.push(1);
        dist[1] = 0;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = head[u]; i != -1; i = nxt[i]) {
                int v = to[i];
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        
        cout << dist[n] << "\n";
    }
    
    return 0;
}
