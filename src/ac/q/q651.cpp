#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <functional>

using namespace std;

struct Edge {
    int u, v, w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        vector<Edge> edges;
        edges.reserve(m);
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            edges.push_back({u, v, w});
        }
        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.w > b.w;
        });
        vector<int> parent(n + 1);
        for (int i = 1; i <= n; ++i) parent[i] = i;
        function<int(int)> find = [&](int x) {
            return parent[x] == x ? x : parent[x] = find(parent[x]);
        };
        int cnt = 0;
        int ans = 0;
        for (const auto& e : edges) {
            int fu = find(e.u);
            int fv = find(e.v);
            if (fu != fv) {
                parent[fu] = fv;
                cnt++;
                ans = e.w;
                if (cnt == n - 1) break;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
