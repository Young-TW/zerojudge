#include <iostream>
#include <vector>
#include <string>

using namespace std;

int m, n;
int dx[] = {1, -1, 0, 0, 1, 1, -1, -1};
int dy[] = {0, 0, 1, -1, 1, -1, 1, -1};

void dfs(int x, int y, vector<string>& grid) {
    if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != '@') {
        return;
    }
    grid[x][y] = '*';
    for (int i = 0; i < 8; ++i) {
        dfs(x + dx[i], y + dy[i], grid);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while (cin >> m >> n && (m || n)) {
        vector<string> grid(m);
        for (int i = 0; i < m; ++i) {
            cin >> grid[i];
        }
        
        int count = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '@') {
                    count++;
                    dfs(i, j, grid);
                }
            }
        }
        cout << count << "\n";
    }
    return 0;
}
