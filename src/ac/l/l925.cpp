#include <bits/stdc++.h>
using namespace std;

int min_vertex_cover_bitmask(int n, const vector<int>& edge_masks) {
    int ans = n;
    int total = 1 << n;
    for (int mask = 0; mask < total; ++mask) {
        bool ok = true;
        for (int em : edge_masks) {
            if ((mask & em) == 0) {
                ok = false;
                break;
            }
        }
        if (ok) {
            int cnt = __builtin_popcount(mask);
            if (cnt < ans) ans = cnt;
        }
    }
    return ans;
}

int n_global;
vector<int> U_global, V_global;
vector<vector<int>> inc_edges_global;
int best_global;

int maximal_matching(const vector<char>& covered) {
    vector<char> used(n_global, 0);
    int match = 0;
    for (size_t i = 0; i < covered.size(); ++i) {
        if (covered[i]) continue;
        int u = U_global[i], v = V_global[i];
        if (!used[u] && !used[v]) {
            used[u] = used[v] = 1;
            match++;
        }
    }
    return match;
}

void dfs(int cnt, vector<char>& covered) {
    int e = -1;
    for (size_t i = 0; i < covered.size(); ++i) {
        if (!covered[i]) {
            e = i;
            break;
        }
    }
    if (e == -1) {
        if (cnt < best_global) best_global = cnt;
        return;
    }
    int lb = maximal_matching(covered);
    if (cnt + lb >= best_global) return;
    int u = U_global[e];
    {
        vector<char> new_covered = covered;
        for (int ei : inc_edges_global[u]) {
            new_covered[ei] = 1;
        }
        dfs(cnt + 1, new_covered);
    }
    int v = V_global[e];
    {
        vector<char> new_covered = covered;
        for (int ei : inc_edges_global[v]) {
            new_covered[ei] = 1;
        }
        dfs(cnt + 1, new_covered);
    }
}

int min_vertex_cover_branch(int n, const vector<pair<int,int>>& edges) {
    n_global = n;
    int m = edges.size();
    U_global.resize(m);
    V_global.resize(m);
    inc_edges_global.assign(n, vector<int>());
    for (int i = 0; i < m; ++i) {
        int u = edges[i].first;
        int v = edges[i].second;
        U_global[i] = u;
        V_global[i] = v;
        inc_edges_global[u].push_back(i);
        inc_edges_global[v].push_back(i);
    }
    best_global = n;
    vector<char> covered(m, 0);
    dfs(0, covered);
    return best_global;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        vector<pair<int,int>> edges;
        edges.reserve(m);
        vector<int> edge_masks;
        edge_masks.reserve(m);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u; --v;
            edges.emplace_back(u, v);
            edge_masks.push_back((1 << u) | (1 << v));
        }
        int ans;
        if (n <= 20) {
            ans = min_vertex_cover_bitmask(n, edge_masks);
        } else {
            ans = min_vertex_cover_branch(n, edges);
        }
        cout << ans << "\n";
    }
    return 0;
}
