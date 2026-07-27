#include <bits/stdc++.h>
using namespace std;

struct State {
    int x, y, d;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int M, N;
    while (cin >> M >> N) {
        int P, Q;
        if (!(cin >> P >> Q)) break;
        int tx, ty;
        cin >> tx >> ty;

        vector<vector<char>> blocked(M, vector<char>(N, 0));
        for (int i = 0; i < P; ++i) {
            int x, y; cin >> x >> y;
            blocked[x][y] = 1;
        }
        vector<vector<char>> noLeft(M, vector<char>(N, 0));
        for (int i = 0; i < Q; ++i) {
            int x, y; cin >> x >> y;
            noLeft[x][y] = 1;
        }

        if (tx == 0 && ty == 0) {
            cout << 0 << "\n";
            continue;
        }

        const int INF = -1;
        static int dist[500][500][4];
        for (int i = 0; i < M; ++i)
            for (int j = 0; j < N; ++j)
                for (int d = 0; d < 4; ++d)
                    dist[i][j][d] = INF;

        const int dx[4] = {0, 1, 0, -1};   // N,E,S,W
        const int dy[4] = {1, 0, -1, 0};

        auto inside = [&](int x, int y) {
            return x >= 0 && x < M && y >= 0 && y < N;
        };
        auto opposite = [&](int d) { return (d + 2) & 3; };
        auto leftTurn = [&](int d) { return (d + 3) & 3; };

        queue<State> q;
        // first step from (0,0)
        for (int d = 0; d < 4; ++d) {
            int nx = 0 + dx[d];
            int ny = 0 + dy[d];
            if (inside(nx, ny) && !blocked[nx][ny]) {
                dist[nx][ny][d] = 1;
                q.push({nx, ny, d});
            }
        }

        int answer = -1;
        while (!q.empty()) {
            State cur = q.front(); q.pop();
            int cd = dist[cur.x][cur.y][cur.d];
            if (cur.x == tx && cur.y == ty) {
                answer = cd;
                break;
            }
            for (int nd = 0; nd < 4; ++nd) {
                if (nd == opposite(cur.d)) continue;               // no reverse
                if (noLeft[cur.x][cur.y] && nd == leftTurn(cur.d)) continue; // no left turn
                int nx = cur.x + dx[nd];
                int ny = cur.y + dy[nd];
                if (!inside(nx, ny) || blocked[nx][ny]) continue;
                if (dist[nx][ny][nd] == INF) {
                    dist[nx][ny][nd] = cd + 1;
                    q.push({nx, ny, nd});
                }
            }
        }
        cout << answer << "\n";
    }
    return 0;
}
