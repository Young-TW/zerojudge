#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Island {
    int w, n, e, s, a;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int X, Y;
    while (cin >> X >> Y) {
        vector<vector<int>> grid(Y, vector<int>(X));
        for (int i = 0; i < Y; ++i) {
            for (int j = 0; j < X; ++j) {
                cin >> grid[i][j];
            }
        }

        vector<vector<bool>> visited(Y, vector<bool>(X, false));
        int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

        vector<Island> islands;

        for (int i = 0; i < Y; ++i) {
            for (int j = 0; j < X; ++j) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    int min_x = j, max_x = j;
                    int min_y = i, max_y = i;
                    int area = 0;

                    queue<pair<int, int>> q;
                    q.push({i, j});
                    visited[i][j] = true;

                    while (!q.empty()) {
                        auto curr = q.front();
                        q.pop();
                        int cy = curr.first;
                        int cx = curr.second;
                        
                        area++;
                        min_x = min(min_x, cx);
                        max_x = max(max_x, cx);
                        min_y = min(min_y, cy);
                        max_y = max(max_y, cy);

                        for (int k = 0; k < 8; ++k) {
                            int ny = cy + dy[k];
                            int nx = cx + dx[k];
                            if (ny >= 0 && ny < Y && nx >= 0 && nx < X) {
                                if (grid[ny][nx] == 1 && !visited[ny][nx]) {
                                    visited[ny][nx] = true;
                                    q.push({ny, nx});
                                }
                            }
                        }
                    }
                    islands.push_back({min_x, min_y, max_x, max_y, area});
                }
            }
        }

        sort(islands.begin(), islands.end(), [](const Island& i1, const Island& i2) {
            if (i1.n != i2.n) return i1.n < i2.n;
            return i1.w < i2.w;
        });

        for (const auto& isle : islands) {
            cout << isle.w << " " << isle.n << " " << isle.e << " " << isle.s << " " << isle.a << "\n";
        }
    }

    return 0;
}
