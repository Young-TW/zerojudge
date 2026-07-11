#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int M, N;
    while (cin >> M >> N) {
        if (M == 0) break;
        vector<string> grid(M);
        for (int i = 0; i < M; ++i) {
            cin >> grid[i];
        }
        vector<vector<bool>> visited(M, vector<bool>(N, false));
        int component_count = 0;
        int max_size = 0;
        int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] != '0' && !visited[i][j]) {
                    component_count++;
                    int size = 0;
                    char faction = grid[i][j];
                    queue<pair<int,int>> q;
                    q.push(make_pair(i, j));
                    visited[i][j] = true;
                    while (!q.empty()) {
                        pair<int,int> p = q.front();
                        q.pop();
                        int x = p.first;
                        int y = p.second;
                        size++;
                        for (int dir = 0; dir < 8; ++dir) {
                            int nx = x + dx[dir];
                            int ny = y + dy[dir];
                            if (nx >= 0 && nx < M && ny >= 0 && ny < N && !visited[nx][ny] && grid[nx][ny] == faction) {
                                visited[nx][ny] = true;
                                q.push(make_pair(nx, ny));
                            }
                        }
                    }
                    if (size > max_size) max_size = size;
                }
            }
        }
        if (component_count > max_size) {
            cout << "choas\n";
        } else {
            cout << "peace\n";
        }
    }
    return 0;
}
