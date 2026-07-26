#include <iostream>
#include <vector>
#include <queue>
#include <bitset>

using namespace std;

const int MAXN = 10005;
vector<int> adj[MAXN];
vector<int> radj[MAXN];
int in_deg[MAXN];
int topo[MAXN];
bitset<MAXN> desc[MAXN];
bitset<MAXN> anc[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    while (cin >> N >> M) {
        for (int i = 1; i <= N; ++i) {
            adj[i].clear();
            radj[i].clear();
            in_deg[i] = 0;
            desc[i].reset();
            anc[i].reset();
        }
        for (int i = 0; i < M; ++i) {
            int a, b;
            cin >> a >> b;
            // a 在 b 下面，即 Pos(a) > Pos(b)
            // b 在 a 上面
            adj[b].push_back(a);
            radj[a].push_back(b);
            in_deg[a]++;
        }
        queue<int> q;
        for (int i = 1; i <= N; ++i) {
            if (in_deg[i] == 0) q.push(i);
        }
        int topo_cnt = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            topo[topo_cnt++] = u;
            for (int v : adj[u]) {
                if (--in_deg[v] == 0) q.push(v);
            }
        }
        
        // 計算後代
        for (int i = topo_cnt - 1; i >= 0; --i) {
            int u = topo[i];
            desc[u].set(u);
            for (int v : adj[u]) {
                desc[u] |= desc[v];
            }
        }
        
        // 計算祖先
        for (int i = 0; i < topo_cnt; ++i) {
            int u = topo[i];
            anc[u].set(u);
            for (int v : radj[u]) {
                anc[u] |= anc[v];
            }
        }
        
        for (int i = 1; i <= N; ++i) {
            int min_pos = anc[i].count();
            int max_pos = N - (int)desc[i].count() + 1;
            cout << min_pos << " " << max_pos << "\n";
        }
    }
    return 0;
}
