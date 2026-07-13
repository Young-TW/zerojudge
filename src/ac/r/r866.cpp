#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> g(n, vector<int>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> g[i][j];
            }
        }

        vector<vector<char>> vis(n, vector<char>(m, 0));
        int best = 0;
        const int dx[4] = {1, -1, 0, 0};
        const int dy[4] = {0, 0, 1, -1};

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (g[i][j] == 1 && !vis[i][j]) {
                    int cnt = 0;
                    queue<pair<int,int>> q;
                    q.push(make_pair(i, j));
                    vis[i][j] = 1;
                    while (!q.empty()) {
                        int x = q.front().first;
                        int y = q.front().second;
                        q.pop();
                        cnt++;
                        for (int d = 0; d < 4; d++) {
                            int nx = x + dx[d];
                            int ny = y + dy[d];
                            if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                                g[nx][ny] == 1 && !vis[nx][ny]) {
                                vis[nx][ny] = 1;
                                q.push(make_pair(nx, ny));
                            }
                        }
                    }
                    if (cnt > best) best = cnt;
                }
            }
        }

        cout << best << "\n";
    }

    return 0;
}
