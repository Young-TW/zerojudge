#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        int N;
        scanf("%d", &N);
        vector<int> f(N + 1);
        vector<int> indeg(N + 1, 0);
        for (int i = 0; i < N; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            f[u] = v;
            indeg[v]++;
        }
        // Kahn's topological sort to peel off non-cycle nodes
        vector<int> order;
        order.reserve(N);
        queue<int> q;
        vector<int> deg = indeg;
        for (int i = 1; i <= N; i++) if (deg[i] == 0) q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            order.push_back(u);
            int v = f[u];
            if (--deg[v] == 0) q.push(v);
        }
        // Remaining nodes with deg > 0 are in cycles
        vector<int> ans(N + 1, 0);
        vector<char> vis(N + 1, 0);
        for (int i = 1; i <= N; i++) {
            if (deg[i] > 0 && !vis[i]) {
                int cur = i;
                int len = 0;
                while (!vis[cur]) {
                    vis[cur] = 1;
                    cur = f[cur];
                    len++;
                }
                // assign cycle length to all members
                cur = i;
                for (int k = 0; k < len; k++) {
                    ans[cur] = len;
                    cur = f[cur];
                }
            }
        }
        // Process non-cycle nodes in reverse removal order
        for (int idx = (int)order.size() - 1; idx >= 0; idx--) {
            int u = order[idx];
            ans[u] = ans[f[u]] + 1;
        }
        int best = -1, bestu = -1;
        for (int i = 1; i <= N; i++) {
            if (ans[i] > best) {
                best = ans[i];
                bestu = i;
            }
        }
        printf("Case %d: %d\n", t, bestu);
    }
    return 0;
}
