#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, Q;
    while (cin >> n >> m >> Q) {
        vector<string> maze(n);
        for (int i = 0; i < n; ++i) {
            cin >> maze[i];
        }

        int V = n * m;
        vector<int> dep(V, -1);
        vector<int> fa(V, -1);
        vector<int> sz(V, 1);
        vector<int> son(V, -1);
        vector<int> top(V);
        vector<int> order;
        order.reserve(V);

        int root = -1;
        for (int i = 0; i < n && root == -1; ++i) {
            for (int j = 0; j < m && root == -1; ++j) {
                if (maze[i][j] == '.') {
                    root = i * m + j;
                }
            }
        }

        if (root != -1) {
            queue<int> q;
            q.push(root);
            dep[root] = 0;
            fa[root] = root;

            int dr[] = {-1, 1, 0, 0};
            int dc[] = {0, 0, -1, 1};

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                order.push_back(u);

                int r = u / m;
                int c = u % m;

                for (int i = 0; i < 4; ++i) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if (nr >= 0 && nr < n && nc >= 0 && nc < m && maze[nr][nc] == '.') {
                        int v = nr * m + nc;
                        if (dep[v] == -1) {
                            dep[v] = dep[u] + 1;
                            fa[v] = u;
                            q.push(v);
                        }
                    }
                }
            }

            for (int i = order.size() - 1; i >= 0; --i) {
                int u = order[i];
                if (fa[u] != u) {
                    sz[fa[u]] += sz[u];
                    if (son[fa[u]] == -1 || sz[u] > sz[son[fa[u]]]) {
                        son[fa[u]] = u;
                    }
                }
            }

            top[root] = root;
            for (int i = 0; i < order.size(); ++i) {
                int u = order[i];
                if (u == root) continue;
                if (u == son[fa[u]]) {
                    top[u] = top[fa[u]];
                } else {
                    top[u] = u;
                }
            }
        }

        long long total_cost = 0;

        for (int i = 0; i < Q; ++i) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            int u = x1 * m + y1;
            int v = x2 * m + y2;

            if (u == v) {
                continue;
            }

            int lca_u = u, lca_v = v;
            while (top[lca_u] != top[lca_v]) {
                if (dep[top[lca_u]] > dep[top[lca_v]]) {
                    swap(lca_u, lca_v);
                }
                lca_v = fa[top[lca_v]];
            }
            int lca = (dep[lca_u] < dep[lca_v]) ? lca_u : lca_v;

            total_cost += (dep[u] + dep[v] - 2 * dep[lca]);
        }

        cout << total_cost << "\n";
    }

    return 0;
}
