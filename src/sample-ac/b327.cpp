#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 40000;
vector<int> adj[MAXN];
int in_time[MAXN], out_time[MAXN];
int timer = 0;
int N;

long long bit[MAXN];

void add(int idx, long long val) {
    for (; idx <= N + 1; idx += idx & -idx)
        bit[idx] += val;
}

long long query(int idx) {
    long long res = 0;
    for (; idx > 0; idx -= idx & -idx)
        res += bit[idx];
    return res;
}

void range_add(int l, int r, long long val) {
    add(l, val);
    add(r + 1, -val);
}

void dfs(int u, int p) {
    in_time[u] = ++timer;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    out_time[u] = timer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> N) {
        for (int i = 0; i < N; ++i) {
            adj[i].clear();
        }
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        timer = 0;
        if (N > 0) {
            dfs(0, -1);
        }
        for (int i = 0; i <= N + 1; ++i) {
            bit[i] = 0;
        }
        int Q;
        cin >> Q;
        while (Q--) {
            int x;
            long long k;
            cin >> x >> k;
            if (N > 0) {
                range_add(in_time[x], out_time[x], k);
                cout << query(in_time[x]) << "\n";
            } else {
                cout << k << "\n";
            }
        }
        cout << "\n";
    }
    return 0;
}
