#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <utility>

using namespace std;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    while (cin >> N >> M) {
        vector<string> grid(N);
        for (int i = 0; i < N; ++i) {
            cin >> grid[i];
        }

        int max_size = 0;
        int min_size = 1e9;
        int count = 0;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (grid[i][j] == 'W') {
                    count++;
                    int current_size = 0;
                    queue<pair<int, int>> q;
                    q.push({i, j});
                    grid[i][j] = '#';

                    while (!q.empty()) {
                        pair<int, int> curr = q.front();
                        q.pop();
                        current_size++;

                        for (int k = 0; k < 4; ++k) {
                            int nx = curr.first + dx[k];
                            int ny = curr.second + dy[k];

                            if (nx >= 0 && nx < N && ny >= 0 && ny < M &&
                                grid[nx][ny] == 'W') {
                                grid[nx][ny] = '#';
                                q.push({nx, ny});
                            }
                        }
                    }

                    if (current_size > max_size) {
                        max_size = current_size;
                    }
                    if (current_size < min_size) {
                        min_size = current_size;
                    }
                }
            }
        }

        if (count == 0) {
            cout << "0 0 0\n";
        } else {
            cout << max_size << " " << min_size << " " << count << "\n";
        }
    }

    return 0;
}
