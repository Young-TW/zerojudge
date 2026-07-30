#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int gcd(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

struct Operation {
    char type; // 'n' for news, 's' for sim
    int x, y;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    while (cin >> N >> M) {
        vector<Operation> ops;
        ops.reserve(M);
        vector<int> parent(N + 1, 0);
        vector<int> add_time(N + 1, 0);
        const int INF = M + 1;
        for (int i = 1; i <= N; ++i) add_time[i] = INF;

        for (int i = 1; i <= M; ++i) {
            string type;
            cin >> type;
            int x, y;
            cin >> x >> y;
            if (type[0] == 'n') { // news
                ops.push_back({'n', x, y});
                parent[x] = y;
                add_time[x] = i;
            } else { // sim
                ops.push_back({'s', x, y});
            }
        }

        // Build children adjacency list
        vector<vector<int>> children(N + 1);
        for (int i = 1; i <= N; ++i) {
            if (parent[i] != 0) {
                children[parent[i]].push_back(i);
            }
        }

        // Compute LOG for binary lifting
        int LOG = 1;
        while ((1 << LOG) <= N) LOG++;

        vector<int> depth(N + 1, 0);
        vector<vector<int>> up(LOG, vector<int>(N + 1, 0));

        // DFS from roots to compute depth and up[0]
        vector<int> stack;
        for (int i = 1; i <= N; ++i) {
            if (parent[i] == 0) { // root
                depth[i] = 1;
                up[0][i] = 0;
                stack.push_back(i);
                while (!stack.empty()) {
                    int u = stack.back();
                    stack.pop_back();
                    for (int v : children[u]) {
                        depth[v] = depth[u] + 1;
                        up[0][v] = u;
                        stack.push_back(v);
                    }
                }
            }
        }

        // Build binary lifting table
        for (int k = 1; k < LOG; ++k) {
            for (int v = 1; v <= N; ++v) {
                int mid = up[k - 1][v];
                up[k][v] = (mid == 0) ? 0 : up[k - 1][mid];
            }
        }

        // Lambda to find active root at time t
        auto get_root = [&](int x, int t) -> int {
            if (add_time[x] > t) return x;
            int u = x;
            for (int k = LOG - 1; k >= 0; --k) {
                int v = up[k][u];
                if (v != 0 && add_time[v] <= t) {
                    u = v;
                }
            }
            return parent[u];
        };

        // Lambda for LCA in final tree
        auto lca = [&](int x, int y) -> int {
            if (depth[x] < depth[y]) swap(x, y);
            int diff = depth[x] - depth[y];
            for (int k = 0; diff; ++k) {
                if (diff & 1) x = up[k][x];
                diff >>= 1;
            }
            if (x == y) return x;
            for (int k = LOG - 1; k >= 0; --k) {
                if (up[k][x] != up[k][y]) {
                    x = up[k][x];
                    y = up[k][y];
                }
            }
            return up[0][x];
        };

        // Process operations in order
        for (int i = 0; i < M; ++i) {
            const Operation& op = ops[i];
            if (op.type == 's') {
                int t = i + 1; // 1-based time
                int x = op.x, y = op.y;
                int rx = get_root(x, t);
                int ry = get_root(y, t);
                if (rx != ry) {
                    cout << -1 << '\n';
                } else {
                    int z = lca(x, y);
                    int dx = depth[x], dy = depth[y], dz = depth[z], dr = depth[rx];
                    int num = 2 * (dz - dr + 1);
                    int den = (dx - dr + 1) + (dy - dr + 1);
                    int g = gcd(num, den);
                    cout << num / g << '/' << den / g << '\n';
                }
            }
        }
    }
    return 0;
}
