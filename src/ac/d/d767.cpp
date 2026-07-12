#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 30005;
const int LOG = 17;

int up[MAXN][LOG];
int dep[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, Q;
    while (cin >> N >> Q) {
        memset(up, 0, sizeof(up));
        memset(dep, 0, sizeof(dep));
        
        for (int i = 1; i <= N; ++i) {
            int v;
            while (cin >> v) {
                if (v == 0) break;
                up[v][0] = i;
                dep[v] = dep[i] + 1;
                for (int j = 1; j < LOG; ++j) {
                    up[v][j] = up[up[v][j-1]][j-1];
                }
            }
        }
        
        while (Q--) {
            int a, b;
            cin >> a >> b;
            int u = a, v = b;
            if (dep[u] < dep[v]) swap(u, v);
            int diff = dep[u] - dep[v];
            for (int j = 0; j < LOG; ++j) {
                if ((diff >> j) & 1) {
                    u = up[u][j];
                }
            }
            if (u != v) {
                for (int j = LOG - 1; j >= 0; --j) {
                    if (up[u][j] != up[v][j]) {
                        u = up[u][j];
                        v = up[v][j];
                    }
                }
                u = up[u][0];
            }
            int lca = u;
            int dist = dep[a] + dep[b] - 2 * dep[lca];
            cout << lca << " " << dist << "\n";
        }
    }
    
    return 0;
}
