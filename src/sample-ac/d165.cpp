#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    while (cin >> N >> M) {
        vector<vector<int>> grid(N, vector<int>(M));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cin >> grid[i][j];
            }
        }
        
        int count = 0;
        int max_sum = 0;
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (grid[i][j] > 0) {
                    count++;
                    int current_sum = 0;
                    queue<pair<int, int>> q;
                    q.push({i, j});
                    current_sum += grid[i][j];
                    grid[i][j] = 0;
                    
                    while (!q.empty()) {
                        pair<int, int> curr = q.front();
                        q.pop();
                        for (int k = 0; k < 4; ++k) {
                            int nx = curr.first + dx[k];
                            int ny = curr.second + dy[k];
                            if (nx >= 0 && nx < N && ny >= 0 && ny < M && grid[nx][ny] > 0) {
                                current_sum += grid[nx][ny];
                                grid[nx][ny] = 0;
                                q.push({nx, ny});
                            }
                        }
                    }
                    if (current_sum > max_sum) {
                        max_sum = current_sum;
                    }
                }
            }
        }
        cout << count << "\n" << max_sum << "\n";
    }
    return 0;
}
