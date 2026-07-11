#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int S;
    int case_num = 1;
    while (cin >> S) {
        int N, M;
        if (!(cin >> N >> M)) break;
        
        vector<vector<int>> grid(N, vector<int>(M));
        vector<vector<int>> time(N, vector<int>(M, 0));
        queue<pair<int, int>> q;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cin >> grid[i][j];
            }
        }

        for (int j = 0; j < M; ++j) {
            if (grid[0][j] == 1) {
                time[0][j] = 1;
                q.push(make_pair(0, j));
                break;
            }
        }

        int dr[4] = {1, 0, 0, -1};
        int dc[4] = {0, 1, -1, 0};
        int num_dirs = (S == 1) ? 4 : 3;

        while (!q.empty()) {
            pair<int, int> curr = q.front();
            q.pop();
            int r = curr.first;
            int c = curr.second;

            for (int i = 0; i < num_dirs; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                    if (grid[nr][nc] == 1 && time[nr][nc] == 0) {
                        time[nr][nc] = time[r][c] + 1;
                        q.push(make_pair(nr, nc));
                    }
                }
            }
        }

        cout << "Case " << case_num++ << ":\n";
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cout << time[i][j] << (j == M - 1 ? "" : " ");
            }
            cout << "\n";
        }
    }

    return 0;
}
