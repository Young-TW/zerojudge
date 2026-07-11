#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> grid(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> grid[i][j];
            }
        }

        int count = 0;
        int max_area = 0;

        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 1) {
                    count++;
                    int area = 0;
                    queue<pair<int, int>> q;
                    q.push({i, j});
                    grid[i][j] = 0;

                    while (!q.empty()) {
                        pair<int, int> curr = q.front();
                        q.pop();
                        area++;

                        for (int k = 0; k < 4; ++k) {
                            int nx = curr.first + dx[k];
                            int ny = curr.second + dy[k];

                            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 1) {
                                grid[nx][ny] = 0;
                                q.push({nx, ny});
                            }
                        }
                    }
                    if (area > max_area) {
                        max_area = area;
                    }
                }
            }
        }

        cout << count << "\n";
        cout << max_area << "\n";
    }

    return 0;
}
