#include <iostream>
#include <vector>
#include <deque>
#include <array>
#include <tuple>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max() / 4;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m) {
        int b, e;
        cin >> b >> e;
        int k;
        cin >> k;

        vector<vector<char>> blocked(n, vector<char>(m, 0));
        for (int i = 0; i < k; ++i) {
            int x, y;
            cin >> x >> y;
            if (0 <= x && x < n && 0 <= y && y < m)
                blocked[x][y] = 1;
        }

        // direction: 0 = down, 1 = left, 2 = right
        const int dr[3] = {1, 0, 0};
        const int dc[3] = {0, -1, 1};

        vector<vector<array<int, 3>>> dist(n,
                                            vector<array<int, 3>>(m));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                dist[i][j].fill(INF);

        deque<tuple<int, int, int>> dq;
        if (!blocked[0][b]) {
            dist[0][b][0] = 0;               // start, facing down
            dq.emplace_back(0, b, 0);
        }

        while (!dq.empty()) {
            auto [r, c, d] = dq.front();
            dq.pop_front();
            int cur = dist[r][c][d];

            // move straight (cost 0)
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && !blocked[nr][nc]) {
                if (cur < dist[nr][nc][d]) {
                    dist[nr][nc][d] = cur;
                    dq.emplace_front(nr, nc, d);
                }
            }

            // turn (cost 1)
            if (d == 0) { // down -> left or right
                for (int nd = 1; nd <= 2; ++nd) {
                    if (cur + 1 < dist[r][c][nd]) {
                        dist[r][c][nd] = cur + 1;
                        dq.emplace_back(r, c, nd);
                    }
                }
            } else { // left or right -> down
                if (cur + 1 < dist[r][c][0]) {
                    dist[r][c][0] = cur + 1;
                    dq.emplace_back(r, c, 0);
                }
            }
        }

        int ans = INF;
        for (int d = 0; d < 3; ++d)
            ans = min(ans, dist[n - 1][e][d]);

        if (ans == INF) ans = -1;   // unreachable (should not happen)
        cout << ans << '\n';
    }
    return 0;
}
