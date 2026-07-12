#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <utility>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    while (std::cin >> n >> m) {
        std::vector<std::string> grid(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> grid[i];
        }
        std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
        int count_at = 0, count_hash = 0;
        int dx[4] = {0, 0, 1, -1};
        int dy[4] = {1, -1, 0, 0};
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (!visited[i][j] && (grid[i][j] == '@' || grid[i][j] == '#')) {
                    char symbol = grid[i][j];
                    if (symbol == '@') count_at++;
                    else count_hash++;
                    std::queue<std::pair<int,int>> q;
                    q.push(std::make_pair(i, j));
                    visited[i][j] = true;
                    while (!q.empty()) {
                        int x = q.front().first;
                        int y = q.front().second;
                        q.pop();
                        for (int dir = 0; dir < 4; ++dir) {
                            int nx = x + dx[dir];
                            int ny = y + dy[dir];
                            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny] && grid[nx][ny] == symbol) {
                                visited[nx][ny] = true;
                                q.push(std::make_pair(nx, ny));
                            }
                        }
                    }
                }
            }
        }
        if (count_at > count_hash) {
            std::cout << "Dave\n";
        } else if (count_hash > count_at) {
            std::cout << "Charlie\n";
        } else {
            std::cout << "Draw\n";
        }
    }
    return 0;
}
