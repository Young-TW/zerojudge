#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n) {
        vector<string> grid(n);
        for (int i = 0; i < n; ++i) {
            cin >> grid[i];
        }

        queue<pair<int, int>> q;
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 'O') {
                    bool is_safe = false;
                    for (int k = 0; k < 4; ++k) {
                        int ni = i + dr[k];
                        int nj = j + dc[k];
                        if (ni >= 0 && ni < n && nj >= 0 && nj < n && grid[ni][nj] == 'R') {
                            is_safe = true;
                            break;
                        }
                    }
                    if (is_safe) {
                        grid[i][j] = 'S';
                    } else {
                        grid[i][j] = 'U';
                        q.push({i, j});
                    }
                }
            }
        }

        while (!q.empty()) {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();

            for (int k = 0; k < 4; ++k) {
                int nr = r + dr[k];
                int nc = c + dc[k];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 'S') {
                    grid[nr][nc] = 'U';
                    q.push({nr, nc});
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 'S') {
                    ans++;
                }
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
