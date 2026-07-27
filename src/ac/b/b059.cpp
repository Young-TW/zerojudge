#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int N = 100;
    const int dx[4] = { -1, 0, 1, 0 };
    const int dy[4] = {  0,-1, 0, 1 };
    const int rdx[8] = { -3,-3,-1, 1, 3, 3, 1,-1 };
    const int rdy[8] = {  1,-1,-3,-3,-1, 1, 3, 3 };

    int n;
    while (cin >> n) {
        vector<vector<char>> blocked(N, vector<char>(N, 0));
        for (int i = 0; i < n; ++i) {
            int x, y; cin >> x >> y;
            blocked[x][y] = 1;
        }
        int sx, sy, ex, ey;
        cin >> sx >> sy;
        cin >> ex >> ey;

        vector<vector<char>> visited(N, vector<char>(N, 0));
        queue<pair<int,int>> q;
        q.emplace(sx, sy);
        visited[sx][sy] = 1;

        int dist = 0;
        bool found = false;

        while (!q.empty() && !found) {
            int sz = q.size();
            while (sz-- && !found) {
                auto cur = q.front(); q.pop();
                int x = cur.first, y = cur.second;
                if (x == ex && y == ey) {
                    found = true;
                    break;
                }
                for (int i = 0; i < 4; ++i) {
                    int ax = x + dx[i];
                    int ay = y + dy[i];
                    if (ax < 0 || ax >= N || ay < 0 || ay >= N) continue;
                    if (blocked[ax][ay]) continue;          // orthogonal cell blocked
                    for (int j = 2*i; j < 2*i + 2; ++j) {
                        int nx = x + rdx[j];
                        int ny = y + rdy[j];
                        if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
                        if (blocked[nx][ny]) continue;
                        if (!visited[nx][ny]) {
                            visited[nx][ny] = 1;
                            q.emplace(nx, ny);
                        }
                    }
                }
            }
            if (!found) ++dist;
        }

        if (found) cout << dist << '\n';
        else       cout << "impossible\n";
    }
    return 0;
}
