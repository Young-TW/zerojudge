#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int m;
int grid[8][8];
bool used[105];
bool visited[8][8];
int max_len;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void dfs(int x, int y, int len) {
    if (len > max_len) {
        max_len = len;
    }
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < m && ny >= 0 && ny < m && !visited[nx][ny] && !used[grid[nx][ny]]) {
            visited[nx][ny] = true;
            used[grid[nx][ny]] = true;
            dfs(nx, ny, len + 1);
            visited[nx][ny] = false;
            used[grid[nx][ny]] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        for (int t = 0; t < n; ++t) {
            cin >> m;
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < m; ++j) {
                    cin >> grid[i][j];
                }
            }
            memset(used, false, sizeof(used));
            memset(visited, false, sizeof(visited));
            max_len = 0;
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < m; ++j) {
                    visited[i][j] = true;
                    used[grid[i][j]] = true;
                    dfs(i, j, 1);
                    visited[i][j] = false;
                    used[grid[i][j]] = false;
                }
            }
            cout << max_len << "\n";
        }
    }
    return 0;
}
