#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int M, N;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int dfs(int x, int y, char land, const vector<string>& grid, vector<vector<bool>>& visited) {
    if (x < 0 || x >= M) return 0;
    if (visited[x][y] || grid[x][y] != land) return 0;
    
    visited[x][y] = true;
    int count = 1;
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = (y + dy[i] + N) % N;
        count += dfs(nx, ny, land, grid, visited);
    }
    return count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while (cin >> M >> N) {
        vector<string> grid(M);
        for (int i = 0; i < M; ++i) {
            cin >> grid[i];
        }
        int X, Y;
        cin >> X >> Y;
        
        char land = grid[X][Y];
        vector<vector<bool>> visited(M, vector<bool>(N, false));
        
        dfs(X, Y, land, grid, visited);
        
        int max_continent = 0;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (!visited[i][j] && grid[i][j] == land) {
                    int size = dfs(i, j, land, grid, visited);
                    if (size > max_continent) {
                        max_continent = size;
                    }
                }
            }
        }
        cout << max_continent << "\n";
    }
    return 0;
}
