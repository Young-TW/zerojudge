#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MAXN = 100005;
const int LOG = 17;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;

int n, m;
LL p[MAXN];
vector<int> adj[MAXN];
int parent[MAXN], depth[MAXN];
LL down[MAXN][2];
LL total0[MAXN], total1[MAXN];
LL up[MAXN][2];
LL ans[MAXN][2];
int anc[LOG+1][MAXN];
LL f[LOG+1][MAXN][2][2];

LL add(LL a, LL b) {
    if (a >= INF/2 || b >= INF/2) return INF;
    return a + b;
}

LL sub(LL a, LL b) {
    if (a >= INF/2) return INF;
    return a - b;
}

int get_lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int k = 0; k <= LOG; ++k)
        if ((diff >> k) & 1) u = anc[k][u];
    if (u == v) return u;
    for (int k = LOG; k >= 0; --k) {
        if (anc[k][u] != anc[k][v]) {
            u = anc[k][u];
            v = anc[k][v];
        }
    }
    return parent[u];
}

int lift(int u, int steps) {
    for (int k = 0; k <= LOG; ++k)
        if ((steps >> k) & 1) u = anc[k][u];
    return u;
}

pair<LL, LL> jump(int u, int s_u, int target) {
    if (u == target) {
        LL res0 = (s_u == 0 ? down[u][0] : INF);
        LL res1 = (s_u == 1 ? down[u][1] : INF);
        return {res0, res1};
    }
    LL cur0 = (s_u == 0 ? down[u][0] : INF);
    LL cur1 = (s_u == 1 ? down[u][1] : INF);
    int cur = u;
    int d = depth[cur] - depth[target];
    for (int k = 0; k <= LOG; ++k) {
        if ((d >> k) & 1) {
            LL nxt0 = min(add(cur0, f[k][cur][0][0]), add(cur1, f[k][cur][1][0]));
            LL nxt1 = min(add(cur0, f[k][cur][0][1]), add(cur1, f[k][cur][1][1]));
            cur0 = nxt0;
            cur1 = nxt1;
            cur = anc[k][cur];
        }
    }
    return {cur0, cur1};
}

int main() {
    scanf("%d %d", &n, &m);
    char type_str[10];
    scanf("%s", type_str);
    for (int i = 1; i <= n; ++i) scanf("%lld", &p[i]);
    for (int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // BFS to get parent, depth and order
    queue<int> q;
    q.push(1);
    parent[1] = 0;
    depth[1] = 1;
    vector<int> order;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : adj[u]) {
            if (v != parent[u]) {
                parent[v] = u;
                depth[v] = depth[u] + 1;
                q.push(v);
            }
        }
    }

    // bottom-up DP (down)
    for (int i = order.size() - 1; i >= 0; --i) {
        int u = order[i];
        LL sum0 = 0, sum1 = 0;
        for (int v : adj[u]) {
            if (v == parent[u]) continue;
            sum0 += down[v][1];
            sum1 += min(down[v][0], down[v][1]);
        }
        down[u][0] = sum0;
        down[u][1] = p[u] + sum1;
        total0[u] = sum0;
        total1[u] = sum1;
    }

    // top-down DP (up and ans)
    up[1][0] = up[1][1] = 0;
    ans[1][0] = down[1][0];
    ans[1][1] = down[1][1];
    for (int u : order) {
        for (int v : adj[u]) {
            if (v == parent[u]) continue;
            LL contrib0 = down[v][1];
            LL contrib1 = min(down[v][0], down[v][1]);
            up[v][0] = sub(ans[u][1], contrib1);
            up[v][1] = min(sub(ans[u][0], contrib0), sub(ans[u][1], contrib1));
            ans[v][0] = add(down[v][0], up[v][0]);
            ans[v][1] = add(down[v][1], up[v][1]);
        }
    }

    // init f with INF
    memset(f, 0x3f, sizeof(f));

    // f[0][v] : from v to parent[v]
    for (int v = 2; v <= n; ++v) {
        int u = parent[v];
        LL other0 = total0[u] - down[v][1];
        LL other1 = p[u] + total1[u] - min(down[v][0], down[v][1]);
        f[0][v][0][0] = INF;
        f[0][v][0][1] = other1;
        f[0][v][1][0] = other0;
        f[0][v][1][1] = other1;
    }

    // anc[0]
    for (int i = 1; i <= n; ++i) anc[0][i] = parent[i];

    // anc and f for k>=1
    for (int k = 1; k <= LOG; ++k) {
        for (int i = 1; i <= n; ++i) {
            int mid = anc[k-1][i];
            if (mid != 0) {
                anc[k][i] = anc[k-1][mid];
            } else {
                anc[k][i] = 0;
            }
        }
    }
    for (int k = 1; k <= LOG; ++k) {
        for (int i = 1; i <= n; ++i) {
            int mid = anc[k-1][i];
            if (mid != 0 && anc[k-1][mid] != 0) {
                for (int a = 0; a < 2; ++a) {
                    for (int b = 0; b < 2; ++b) {
                        LL val = INF;
                        for (int t = 0; t < 2; ++t) {
                            val = min(val, add(f[k-1][i][a][t], f[k-1][mid][t][b]));
                        }
                        f[k][i][a][b] = val;
                    }
                }
            }
        }
    }

    // answer queries
    while (m--) {
        int a, x, b, y;
        scanf("%d %d %d %d", &a, &x, &b, &y);
        if (depth[a] > depth[b]) {
            swap(a, b);
            swap(x, y);
        }
        int l = get_lca(a, b);
        LL answer = INF;
        if (l == a) {
            auto vec = jump(b, y, a);
            LL res0 = vec.first, res1 = vec.second;
            if (x == 0) {
                answer = add(res0, a == 1 ? 0 : up[a][0]);
            } else {
                answer = add(res1, a == 1 ? 0 : up[a][1]);
            }
        } else {
            int la = lift(a, depth[a] - depth[l] - 1);
            int lb = lift(b, depth[b] - depth[l] - 1);
            auto vecA = jump(a, x, la);
            auto vecB = jump(b, y, lb);
            LL A0 = vecA.first, A1 = vecA.second;
            LL B0 = vecB.first, B1 = vecB.second;
            LL other0 = total0[l] - down[la][1] - down[lb][1];
            LL other1 = p[l] + total1[l] - min(down[la][0], down[la][1]) - min(down[lb][0], down[lb][1]);
            LL dp_l0 = add(other0, add(A1, B1));
            LL dp_l1 = add(other1, add(min(A0, A1), min(B0, B1)));
            LL ans0 = add(dp_l0, l == 1 ? 0 : up[l][0]);
            LL ans1 = add(dp_l1, l == 1 ? 0 : up[l][1]);
            answer = min(ans0, ans1);
        }
        if (answer >= INF/2) printf("-1\n");
        else printf("%lld\n", answer);
    }
    return 0;
}
