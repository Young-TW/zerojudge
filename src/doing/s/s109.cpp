#include <iostream>
#include <vector>
#include <bitset>
#include <array>
#include <algorithm>
#include <utility>

using namespace std;

constexpr int MAXC = 1000;
constexpr int LOG = 18;  // 2^17 = 131072, 2^18 = 262144 > 200000

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, C, Q;
    while (cin >> N >> C >> Q) {
        vector<vector<int>> adj(N + 1);
        for (int i = 0; i < N - 1; ++i) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        vector<int> color(N + 1);
        for (int i = 1; i <= N; ++i) cin >> color[i];

        vector<int> in(N + 1), out(N + 1), depth(N + 1);
        vector<array<int, LOG>> up(N + 1);
        vector<bitset<MAXC>> base(N + 1);
        int timer = 0;

        // Iterative DFS to avoid recursion depth issues
        vector<int> stk_node, stk_idx;
        stk_node.reserve(N);
        stk_idx.reserve(N);
        stk_node.push_back(1);
        stk_idx.push_back(0);
        up[1][0] = 0;
        for (int k = 1; k < LOG; ++k) up[1][k] = 0;
        depth[1] = 0;
        base[1].reset();
        base[1].set(color[1] - 1);
        in[1] = ++timer;

        while (!stk_node.empty()) {
            int u = stk_node.back();
            int &i = stk_idx.back();
            if (i < (int)adj[u].size()) {
                int v = adj[u][i++];
                if (v == up[u][0]) continue;
                up[v][0] = u;
                for (int k = 1; k < LOG; ++k)
                    up[v][k] = up[up[v][k - 1]][k - 1];
                depth[v] = depth[u] + 1;
                base[v] = base[u];
                base[v].flip(color[v] - 1);
                in[v] = ++timer;
                stk_node.push_back(v);
                stk_idx.push_back(0);
            } else {
                out[u] = timer;
                stk_node.pop_back();
                stk_idx.pop_back();
            }
        }

        // Fenwick Tree (BIT) for range XOR update, point query
        vector<bitset<MAXC>> bit(N + 2);
        auto bit_update = [&](int idx, const bitset<MAXC> &val) {
            for (int i = idx; i <= N; i += i & -i)
                bit[i] ^= val;
        };
        auto bit_query = [&](int idx) {
            bitset<MAXC> res;
            for (int i = idx; i > 0; i -= i & -i)
                res ^= bit[i];
            return res;
        };
        auto range_update = [&](int l, int r, const bitset<MAXC> &val) {
            bit_update(l, val);
            if (r + 1 <= N) bit_update(r + 1, val);
        };

        // LCA with binary lifting
        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);
            int diff = depth[u] - depth[v];
            for (int k = 0; k < LOG; ++k)
                if (diff & (1 << k)) u = up[u][k];
            if (u == v) return u;
            for (int k = LOG - 1; k >= 0; --k) {
                if (up[u][k] != up[v][k]) {
                    u = up[u][k];
                    v = up[v][k];
                }
            }
            return up[u][0];
        };

        vector<int> cur_color = color;
        vector<bitset<MAXC>> color_bit(C + 1);
        for (int c = 1; c <= C; ++c) {
            color_bit[c].reset();
            color_bit[c].set(c - 1);
        }

        for (int i = 0; i < Q; ++i) {
            char type;
            cin >> type;
            if (type == 'U') {
                int x, c;
                cin >> x >> c;
                int old = cur_color[x];
                if (old != c) {
                    bitset<MAXC> delta = color_bit[old] ^ color_bit[c];
                    range_update(in[x], out[x], delta);
                    cur_color[x] = c;
                }
            } else if (type == 'Q') {
                int u, v;
                cin >> u >> v;
                int w = lca(u, v);
                bitset<MAXC> bu = base[u] ^ bit_query(in[u]);
                bitset<MAXC> bv = base[v] ^ bit_query(in[v]);
                bitset<MAXC> path = bu ^ bv ^ color_bit[cur_color[w]];
                cout << path.count() << '\n';
            }
        }
    }
    return 0;
}
