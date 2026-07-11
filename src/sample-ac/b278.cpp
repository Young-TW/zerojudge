#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 500005;

int n, T;
int op[MAXN];
int pos[MAXN];
long long val[MAXN];
int L[MAXN], R[MAXN];
int k_op[MAXN];
int par[MAXN];
vector<int> adj[MAXN];
long long ans[MAXN];
long long old_val[MAXN];

long long BIT[MAXN];
long long cur_val[MAXN];
int idx_arr[MAXN];
int stk_arr[MAXN];

inline void update(int x, long long delta) {
    for (int i = x; i <= n; i += i & (-i))
        BIT[i] += delta;
}

inline long long query(int x) {
    long long res = 0;
    for (int i = x; i > 0; i -= i & (-i))
        res += BIT[i];
    return res;
}

int main() {
    while (scanf("%d %d", &n, &T) == 2) {
        for (int i = 0; i <= T; ++i) {
            adj[i].clear();
            idx_arr[i] = 0;
        }
        for (int i = 0; i <= n; ++i) {
            BIT[i] = 0;
            cur_val[i] = 0;
        }

        for (int i = 1; i <= T; ++i) {
            scanf("%d", &op[i]);
            if (op[i] == 1) {
                scanf("%d %lld", &pos[i], &val[i]);
                par[i] = i - 1;
            } else if (op[i] == 2) {
                scanf("%d %d", &L[i], &R[i]);
                par[i] = i - 1;
            } else if (op[i] == 0) {
                scanf("%d", &k_op[i]);
                par[i] = i - k_op[i] - 1;
            }
            adj[par[i]].push_back(i);
        }

        int stk_top = 0;
        stk_arr[stk_top++] = 0;
        while (stk_top > 0) {
            int u = stk_arr[stk_top - 1];
            if (idx_arr[u] < adj[u].size()) {
                int v = adj[u][idx_arr[u]];
                idx_arr[u]++;
                if (op[v] == 1) {
                    int x = pos[v];
                    long long old_v = cur_val[x];
                    update(x, val[v] - old_v);
                    cur_val[x] = val[v];
                    old_val[v] = old_v;
                } else if (op[v] == 2) {
                    ans[v] = query(R[v]) - query(L[v] - 1);
                }
                stk_arr[stk_top++] = v;
            } else {
                if (u > 0 && op[u] == 1) {
                    int x = pos[u];
                    update(x, old_val[u] - cur_val[x]);
                    cur_val[x] = old_val[u];
                }
                stk_top--;
            }
        }

        for (int i = 1; i <= T; ++i) {
            if (op[i] == 2) {
                printf("%lld\n", ans[i]);
            }
        }
    }

    return 0;
}
