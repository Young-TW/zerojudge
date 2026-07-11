#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int M, N;
    while (cin >> M >> N) {
        vector<string> grid(N + 2, string(M + 2, '0'));
        for (int i = 1; i <= N; ++i) {
            string row;
            cin >> row;
            for (int j = 1; j <= M; ++j) {
                grid[i][j] = row[j - 1];
            }
        }

        auto get_degree = [&](int x, int y) {
            int deg = 0;
            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (grid[ny][nx] == '*') {
                    deg++;
                }
            }
            return deg;
        };

        int start_x = -1, start_y = -1;
        for (int y = 1; y <= N; ++y) {
            for (int x = 1; x <= M; ++x) {
                if (grid[y][x] == '*') {
                    int deg = get_degree(x, y);
                    if (deg == 1) {
                        if (start_x == -1 || x < start_x || (x == start_x && y < start_y)) {
                            start_x = x;
                            start_y = y;
                        }
                    }
                }
            }
        }

        if (start_x == -1) {
            for (int y = 1; y <= N; ++y) {
                for (int x = 1; x <= M; ++x) {
                    if (grid[y][x] == '*') {
                        start_x = x;
                        start_y = y;
                        break;
                    }
                }
                if (start_x != -1) break;
            }
        }

        vector<pair<int, int>> path;
        vector<vector<bool>> visited(N + 2, vector<bool>(M + 2, false));
        int curr_x = start_x, curr_y = start_y;

        while (true) {
            visited[curr_y][curr_x] = true;
            path.push_back({curr_x, curr_y});

            int next_x = -1, next_y = -1;
            for (int i = 0; i < 4; ++i) {
                int nx = curr_x + dx[i];
                int ny = curr_y + dy[i];
                if (grid[ny][nx] == '*' && !visited[ny][nx]) {
                    next_x = nx;
                    next_y = ny;
                    break;
                }
            }

            if (next_x == -1) break;

            curr_x = next_x;
            curr_y = next_y;
        }

        vector<pair<int, int>> result;
        result.push_back(path[0]);
        for (size_t i = 1; i + 1 < path.size(); ++i) {
            int x0 = path[i - 1].first, y0 = path[i - 1].second;
            int x1 = path[i].first, y1 = path[i].second;
            int x2 = path[i + 1].first, y2 = path[i + 1].second;
            if (x0 != x2 && y0 != y2) {
                result.push_back(path[i]);
            }
        }
        if (path.size() > 1) {
            result.push_back(path.back());
        }

        for (auto p : result) {
            cout << p.first << " " << p.second << "\n";
        }
    }
    return 0;
}
