#include <iostream>

using namespace std;

bool is_clique[1 << 22];
int adj[22];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    while (cin >> N >> M) {
        for (int i = 0; i < N; ++i) {
            adj[i] = 0;
        }
        
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            adj[u] |= (1 << v);
            adj[v] |= (1 << u);
        }
        
        int max_clique = 0;
        is_clique[0] = true;
        
        for (int mask = 1; mask < (1 << N); ++mask) {
            int v = __builtin_ctz(mask);
            int prev = mask ^ (1 << v);
            
            if (is_clique[prev] && (prev & ~adj[v]) == 0) {
                is_clique[mask] = true;
                int cnt = __builtin_popcount(mask);
                if (cnt > max_clique) {
                    max_clique = cnt;
                }
            } else {
                is_clique[mask] = false;
            }
        }
        
        cout << max_clique << "\n";
    }
    
    return 0;
}
