#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, r, c;
    while (cin >> n >> m >> r >> c) {
        vector<string> grid(n);
        for (int i = 0; i < n; ++i) cin >> grid[i];

        vector<vector<int>> cnt(n, vector<int>(m, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == '*') continue;
                int s = 0;
                for (int di = -1; di <= 1; ++di) {
                    for (int dj = -1; dj <= 1; ++dj) {
                        if (di == 0 && dj == 0) continue;
                        int ni = i + di, nj = j + dj;
                        if (ni >= 0 && ni < n && nj >= 0 && nj < m && grid[ni][nj] == '*') ++s;
                    }
                }
                cnt[i][j] = s;
            }
        }

        vector<string> out(n, string(m, '#'));
        vector<vector<char>> vis(n, vector<char>(m, 0));
        queue<pair<int,int>> q;

        if (grid[r-1][c-1] == '*') {
            out[r-1][c-1] = '*';
        } else {
            q.push({r-1, c-1});
            vis[r-1][c-1] = 1;
        }

        const int dx[] = {-1,-1,-1,0,0,1,1,1};
        const int dy[] = {-1,0,1,-1,1,-1,0,1};

        while (!q.empty()) {
            auto pr = q.front(); q.pop();
            int x = pr.first, y = pr.second;
            if (cnt[x][y] == 0) {
                out[x][y] = '_';
                for (int k = 0; k < 8; ++k) {
                    int nx = x + dx[k], ny = y + dy[k];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny] && grid[nx][ny] != '*') {
                        vis[nx][ny] = 1;
                        q.push({nx, ny});
                    }
                }
            } else {
                out[x][y] = char('0' + cnt[x][y]);
            }
        }

        for (int i = 0; i < n; ++i) cout << out[i] << "\n";
    }
    return 0;
}
