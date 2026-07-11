#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    while (cin >> n >> m) {
        vector<string> grid(n);
        for (int i = 0; i < n; ++i) {
            cin >> grid[i];
        }

        int dirs[128][4] = {0};
        dirs['F'][1] = dirs['F'][2] = 1;
        dirs['H'][1] = dirs['H'][3] = 1;
        dirs['7'][2] = dirs['7'][3] = 1;
        dirs['I'][0] = dirs['I'][2] = 1;
        dirs['X'][0] = dirs['X'][1] = dirs['X'][2] = dirs['X'][3] = 1;
        dirs['L'][0] = dirs['L'][1] = 1;
        dirs['J'][0] = dirs['J'][3] = 1;

        vector<vector<bool>> visited(n, vector<bool>(m, false));
        int max_size = 0;

        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] != '0' && !visited[i][j]) {
                    int current_size = 0;
                    queue<pair<int, int>> q;
                    q.push({i, j});
                    visited[i][j] = true;

                    while (!q.empty()) {
                        pair<int, int> curr = q.front();
                        q.pop();
                        current_size++;

                        int r = curr.first;
                        int c = curr.second;
                        char ch = grid[r][c];

                        for (int d = 0; d < 4; ++d) {
                            if (dirs[ch][d]) {
                                int nr = r + dr[d];
                                int nc = c + dc[d];
                                if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                                    char nch = grid[nr][nc];
                                    if (nch != '0' && !visited[nr][nc] && dirs[nch][(d + 2) % 4]) {
                                        visited[nr][nc] = true;
                                        q.push({nr, nc});
                                    }
                                }
                            }
                        }
                    }
                    if (current_size > max_size) {
                        max_size = current_size;
                    }
                }
            }
        }
        cout << max_size << "\n";
    }
    return 0;
}
