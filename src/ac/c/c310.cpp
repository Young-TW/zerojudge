#include <iostream>
#include <vector>

using namespace std;

const int N = 50005;
int bit[N];
int in[N], out[N];
int parent[N];
vector<int> adj[N];
int ptr[N];
int stk[N];

void add(int idx, int val, int n) {
    for (; idx <= n; idx += idx & -idx)
        bit[idx] += val;
}

int sum(int idx) {
    int res = 0;
    for (; idx > 0; idx -= idx & -idx)
        res += bit[idx];
    return res;
}

int range_sum(int l, int r) {
    return sum(r) - sum(l - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
            bit[i] = 0;
        }
        for (int i = 0; i < n - 1; i++) {
            int x, y;
            cin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        int timer = 0;
        int top = 0;
        for (int i = 1; i <= n; i++) ptr[i] = 0;
        parent[1] = 0;
        stk[top++] = 1;
        in[1] = ++timer;
        while (top > 0) {
            int u = stk[top - 1];
            if (ptr[u] < adj[u].size()) {
                int v = adj[u][ptr[u]++];
                if (v != parent[u]) {
                    parent[v] = u;
                    in[v] = ++timer;
                    stk[top++] = v;
                }
            } else {
                out[u] = timer;
                top--;
            }
        }
        for (int i = 1; i <= n; i++) {
            add(i, 1, n);
        }
        int q;
        cin >> q;
        while (q--) {
            int c, x;
            cin >> c >> x;
            if (c == 1) {
                int val = range_sum(in[x], in[x]);
                if (val == 1) {
                    add(in[x], -1, n);
                } else {
                    add(in[x], 1, n);
                }
            } else {
                cout << range_sum(in[x], out[x]) << "\n";
            }
        }
    }
    return 0;
}
