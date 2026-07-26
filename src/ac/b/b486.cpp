#include <bits/stdc++.h>
using namespace std;

struct Op {
    char type;          // 'n' = news, 's' = sim
    int x, y;
};

int mygcd(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    while (cin >> N >> M) {
        vector<Op> ops;
        ops.reserve(M);
        vector<int> parent(N + 1, 0);
        vector<int> etime(N + 1, 0);          // time when edge becomes known
        const int INF = M + 5;
        for (int i = 1; i <= N; ++i) etime[i] = INF;

        for (int i = 1; i <= M; ++i) {
            string s; int x, y;
            cin >> s >> x >> y;
            if (s[0] == 'n') {                // news
                ops.push_back({'n', x, y});
                parent[x] = y;
                etime[x] = i;                 // edge (y -> x) appears now
            } else {                          // sim
                ops.push_back({'s', x, y});
            }
        }

        /* ---------- binary lifting tables ---------- */
        int LOG = 1;
        while ((1 << LOG) <= N) ++LOG;
        vector<vector<int>> up(LOG, vector<int>(N + 1, 0));
        vector<vector<int>> mx(LOG, vector<int>(N + 1, INF));

        for (int v = 1; v <= N; ++v) {
            up[0][v] = parent[v];
            mx[0][v] = etime[v];
        }
        for (int k = 1; k < LOG; ++k) {
            for (int v = 1; v <= N; ++v) {
                int mid = up[k - 1][v];
                if (mid != 0) {
                    up[k][v] = up[k - 1][mid];
                    mx[k][v] = max(mx[k - 1][v], mx[k - 1][mid]);
                } else {
                    up[k][v] = 0;
                    mx[k][v] = mx[k - 1][v];
                }
            }
        }

        auto climb = [&](int v, int t) -> pair<int,int> {
            int cur = v;
            int cnt = 0;
            for (int k = LOG - 1; k >= 0; --k) {
                if (up[k][cur] != 0 && mx[k][cur] <= t) {
                    cur = up[k][cur];
                    cnt += (1 << k);
                }
            }
            return {cur, cnt};          // cnt = number of edges climbed
        };

        auto lift_by = [&](int v, int steps) -> int {
            int cur = v;
            for (int k = 0; steps; ++k) {
                if (steps & 1) cur = up[k][cur];
                steps >>= 1;
            }
            return cur;
        };

        for (int idx = 0; idx < M; ++idx) {
            const Op &op = ops[idx];
            if (op.type == 's') {
                int t = idx + 1;                 // current time (1‑based)
                int x = op.x, y = op.y;

                auto cx = climb(x, t);
                auto cy = climb(y, t);
                int rootx = cx.first;
                int rooty = cy.first;

                if (rootx != rooty) {
                    cout << -1 << '\n';
                    continue;
                }

                int dx = cx.second + 1;          // active depth of x
                int dy = cy.second + 1;          // active depth of y

                int u = x, v = y;
                if (dx > dy) {
                    u = lift_by(u, dx - dy);
                } else if (dy > dx) {
                    v = lift_by(v, dy - dx);
                }

                int lca;
                if (u == v) {
                    lca = u;
                } else {
                    for (int k = LOG - 1; k >= 0; --k) {
                        if (up[k][u] != 0 && up[k][u] != up[k][v]) {
                            u = up[k][u];
                            v = up[k][v];
                        }
                    }
                    lca = up[0][u];
                }

                int dl = climb(lca, t).second + 1;   // depth of LCA

                long long num = 2LL * dl;
                long long den = (long long)dx + dy;
                long long g = mygcd((int)num, (int)den);
                cout << (num / g) << '/' << (den / g) << '\n';
            }
        }
    }
    return 0;
}
