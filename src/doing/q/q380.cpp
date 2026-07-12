#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int main() {
    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> grid(n, vector<int>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> grid[i][j];
            }
        }
        
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        int islands = 0;
        int count2 = 0;
        
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        
        // Count connected components of 1s (4-connectivity)
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    islands++;
                    queue<pair<int,int>> q;
                    q.push({i, j});
                    visited[i][j] = true;
                    while (!q.empty()) {
                        int x = q.front().first;
                        int y = q.front().second;
                        q.pop();
                        for (int d = 0; d < 4; d++) {
                            int nx = x + dx[d], ny = y + dy[d];
                            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 1 && !visited[nx][ny]) {
                                visited[nx][ny] = true;
                                q.push({nx, ny});
                            }
                        }
                    }
                }
            }
        }
        
        // Count 2s and check if each connected component of 2s is adjacent to at least one 1
        vector<vector<bool>> visited2(n, vector<bool>(m, false));
        bool valid = true;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 2) {
                    count2++;
                    if (!visited2[i][j]) {
                        bool hasAdjacent1 = false;
                        queue<pair<int,int>> q;
                        q.push({i, j});
                        visited2[i][j] = true;
                        while (!q.empty()) {
                            int x = q.front().first;
                            int y = q.front().second;
                            q.pop();
                            for (int d = 0; d < 4; d++) {
                                int nx = x + dx[d], ny = y + dy[d];
                                if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                                    if (grid[nx][ny] == 1) {
                                        hasAdjacent1 = true;
                                    }
                                    if (grid[nx][ny] == 2 && !visited2[nx][ny]) {
                                        visited2[nx][ny] = true;
                                        q.push({nx, ny});
                                    }
                                }
                            }
                        }
                        if (!hasAdjacent1) {
                            valid = false;
                        }
                    }
                }
            }
        }
        
        if (!valid) {
            cout << -1 << endl;
        } else {
            cout << islands + count2 << endl;
        }
    }
    return 0;
}
