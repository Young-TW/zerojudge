#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <utility>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    while (cin >> N >> M) {
        vector<string> grid(N);
        for (int i = 0; i < N; ++i) {
            cin >> grid[i];
        }

        int dist[15][15];
        memset(dist, -1, sizeof(dist));

        queue<pair<int, int>> q;
        
        if (grid[0][0] == '.') {
            dist[0][0] = 0;
            q.push({0, 0});
        }

        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};

        while (!q.empty()) {
            pair<int, int> curr = q.front();
            q.pop();
            int x = curr.first;
            int y = curr.second;

            if (x == N - 1 && y == M - 1) {
                break;
            }

            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (nx >= 0 && nx < N && ny >= 0 && ny < M && grid[nx][ny] == '.' && dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }

        cout << dist[N - 1][M - 1] << "\n";
    }

    return 0;
}
