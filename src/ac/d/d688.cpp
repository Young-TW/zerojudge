#include <iostream>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    while (cin >> n >> m && (n || m)) {
        int adj[20];
        memset(adj, 0, sizeof(adj));
        
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u; --v;
            adj[u] |= (1 << v);
            adj[v] |= (1 << u);
        }
        
        long long ans = 0;
        for (int S = 1; S < (1 << n); ++S) {
            int v = __builtin_ctz(S);
            int reach = 1 << v;
            int old_reach = 0;
            
            while (reach != old_reach) {
                old_reach = reach;
                int next = 0;
                int temp = reach;
                while (temp) {
                    int u = __builtin_ctz(temp);
                    temp &= temp - 1;
                    next |= adj[u];
                }
                reach |= (next & S);
            }
            
            if (reach == S) {
                ++ans;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
