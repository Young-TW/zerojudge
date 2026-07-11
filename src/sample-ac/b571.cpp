#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

struct State {
    int x, y, t;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m) {
        vector<string> grid(n);
        int startX = -1, startY = -1;
        for (int i = 0; i < n; ++i) {
            cin >> grid[i];
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 'X') {
                    startX = i;
                    startY = j;
                }
            }
        }

        vector<vector<vector<bool>>> visited(n, vector<vector<bool>>(m, vector<bool>(3, false)));
        queue<State> q;
        
        auto can_move = [](char c, int t_mod) {
            if (c == '#') return false;
            if (c == 'A' && t_mod == 0) return false;
            if (c == 'B' && t_mod == 1) return false;
            if (c == 'C' && t_mod == 2) return false;
            return true;
        };

        if (can_move(grid[startX][startY], 0)) {
            q.push({startX, startY, 0});
            visited[startX][startY][0] = true;
        }

        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        int ans = -1;

        while (!q.empty()) {
            State curr = q.front();
            q.pop();

            if (grid[curr.x][curr.y] == 'Y') {
                ans = curr.t;
                break;
            }

            int next_t = curr.t + 1;
            int next_t_mod = next_t % 3;

            for (int i = 0; i < 4; ++i) {
                int nx = curr.x + dx[i];
                int ny = curr.y + dy[i];

                if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                    if (!visited[nx][ny][next_t_mod] && can_move(grid[nx][ny], next_t_mod)) {
                        visited[nx][ny][next_t_mod] = true;
                        q.push({nx, ny, next_t});
                    }
                }
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
