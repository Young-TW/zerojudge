#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 10005;
vector<int> adj[MAXN];
int marbles[MAXN];
bool has_parent[MAXN];
int order[MAXN];
int sz[MAXN];
long long sum[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n && n) {
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
            has_parent[i] = false;
        }
        
        for (int i = 0; i < n; i++) {
            int v, m, d;
            cin >> v >> m >> d;
            marbles[v] = m;
            for (int j = 0; j < d; j++) {
                int c;
                cin >> c;
                adj[v].push_back(c);
                has_parent[c] = true;
            }
        }
        
        int root = -1;
        for (int i = 1; i <= n; i++) {
            if (!has_parent[i]) {
                root = i;
                break;
            }
        }
        
        int order_cnt = 0;
        queue<int> q;
        q.push(root);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order[order_cnt++] = u;
            for (size_t i = 0; i < adj[u].size(); i++) {
                q.push(adj[u][i]);
            }
        }
        
        long long ans = 0;
        for (int i = order_cnt - 1; i >= 0; i--) {
            int u = order[i];
            sz[u] = 1;
            sum[u] = marbles[u];
            for (size_t j = 0; j < adj[u].size(); j++) {
                int v = adj[u][j];
                sz[u] += sz[v];
                sum[u] += sum[v];
            }
            if (has_parent[u]) {
                long long diff = sum[u] - sz[u];
                if (diff < 0) diff = -diff;
                ans += diff;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
