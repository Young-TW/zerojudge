#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

struct Cell {
    int h, x, y;
    bool operator>(const Cell& other) const {
        return h > other.h;
    }
};

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    while (cin >> M >> N) {
        vector<vector<int>> grid(M, vector<int>(N));
        vector<vector<bool>> visited(M, vector<bool>(N, false));
        priority_queue<Cell, vector<Cell>, greater<Cell>> pq;

        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> grid[i][j];
            }
        }

        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i == 0 || i == M - 1 || j == 0 || j == N - 1) {
                    pq.push({grid[i][j], i, j});
                    visited[i][j] = true;
                }
            }
        }

        long long total_water = 0;

        while (!pq.empty()) {
            Cell curr = pq.top();
            pq.pop();

            for (int k = 0; k < 4; ++k) {
                int nx = curr.x + dx[k];
                int ny = curr.y + dy[k];

                if (nx >= 0 && nx < M && ny >= 0 && ny < N && !visited[nx][ny]) {
                    visited[nx][ny] = true;
                    if (grid[nx][ny] < curr.h) {
                        total_water += (curr.h - grid[nx][ny]);
                        pq.push({curr.h, nx, ny});
                    } else {
                        pq.push({grid[nx][ny], nx, ny});
                    }
                }
            }
        }

        cout << total_water << "\n";
    }

    return 0;
}
