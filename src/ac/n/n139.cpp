#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int X, Y;
int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

int bfs(int startX, int startY, int endX, int endY, const vector<vector<int>>& grid) {
    if (startX == endX && startY == endY) return 0;
    vector<vector<int>> dist(Y, vector<int>(X, -1));
    queue<pair<int, int>> q;
    q.push({startX, startY});
    dist[startY][startX] = 0;
    
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        
        for (int i = 0; i < 8; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < X && ny >= 0 && ny < Y && grid[ny][nx] == 0 && dist[ny][nx] == -1) {
                dist[ny][nx] = dist[y][x] + 1;
                if (nx == endX && ny == endY) {
                    return dist[ny][nx];
                }
                q.push({nx, ny});
            }
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while (cin >> X >> Y) {
        int N;
        if (!(cin >> N)) break;
        vector<pair<int, int>> points(N);
        for (int i = 0; i < N; ++i) {
            cin >> points[i].first >> points[i].second;
        }
        
        vector<vector<int>> grid(Y, vector<int>(X));
        for (int i = 0; i < Y; ++i) {
            for (int j = 0; j < X; ++j) {
                cin >> grid[i][j];
            }
        }
        
        int total_steps = 0;
        for (int i = 0; i < N - 1; ++i) {
            total_steps += bfs(points[i].first, points[i].second, points[i+1].first, points[i+1].second, grid);
        }
        
        cout << total_steps << "\n";
    }
    
    return 0;
}
