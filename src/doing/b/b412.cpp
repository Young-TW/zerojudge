#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstring>

struct Change {
    int u, v, prev_size_u;
};

class RollbackDSU {
    std::vector<int> parent, sz;
    std::vector<Change> changes;
public:
    RollbackDSU(int n) : parent(n + 1), sz(n + 1) {
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
            sz[i] = 1;
        }
    }
    int find(int x) {
        while (parent[x] != x) x = parent[x];
        return x;
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            changes.push_back({-1, -1, -1});
            return;
        }
        if (sz[a] < sz[b]) std::swap(a, b);
        changes.push_back({a, b, sz[a]});
        parent[b] = a;
        sz[a] += sz[b];
    }
    int snapshot() const {
        return (int)changes.size();
    }
    void revert(int snap) {
        while ((int)changes.size() > snap) {
            Change ch = changes.back();
            changes.pop_back();
            if (ch.u == -1) continue;
            parent[ch.v] = ch.v;
            sz[ch.u] = ch.prev_size_u;
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    if (!(std::cin >> n >> m)) return 0;
    RollbackDSU dsu(n);
    std::vector<int> version_stack(m + 1, 0);
    version_stack[0] = 0;
    int ans = 0;
    for (int d = 1; d <= m; ++d) {
        int t_enc;
        std::cin >> t_enc;
        int t = t_enc ^ ans;
        if (t == 0) {
            int k_enc;
            std::cin >> k_enc;
            int k = k_enc ^ ans;
            dsu.revert(version_stack[k]);
            version_stack[d] = dsu.snapshot();
        } else if (t == 1) {
            int x_enc, y_enc;
            std::cin >> x_enc >> y_enc;
            int x = x_enc ^ ans;
            int y = y_enc ^ ans;
            dsu.revert(version_stack[d - 1]);
            dsu.unite(x, y);
            version_stack[d] = dsu.snapshot();
        } else if (t == 2) {
            int x_enc, y_enc;
            std::cin >> x_enc >> y_enc;
            int x = x_enc ^ ans;
            int y = y_enc ^ ans;
            dsu.revert(version_stack[d - 1]);
            ans = (dsu.find(x) == dsu.find(y)) ? 1 : 0;
            std::cout << ans << "\n";
            version_stack[d] = dsu.snapshot();
        }
    }
    return 0;
}
