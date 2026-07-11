#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct State {
    int x, y, step;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    while (cin >> N >> M) {
        vector<vector<int>> grid(N, vector<int>(M));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cin >> grid[i][j];
            }
        }

        vector<vector<bool>> visited(N, vector<bool>(M, false));
        queue<State> q;
        vector<int> ans;

        if (grid[0][0] != 2) {
            q.push({0, 0, 0});
            visited[0][0] = true;
            if (grid[0][0] == 1) {
                ans.push_back(0);
            }
        }

        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};

        while (!q.empty()) {
            State curr = q.front();
            q.pop();

            for (int i = 0; i < 4; ++i) {
                int nx = curr.x + dx[i];
                int ny = curr.y + dy[i];

                if (nx >= 0 && nx < N && ny >= 0 && ny < M && !visited[nx][ny] && grid[nx][ny] != 2) {
                    visited[nx][ny] = true;
                    q.push({nx, ny, curr.step + 1});
                    if (grid[nx][ny] == 1) {
                        ans.push_back(curr.step + 1);
                    }
                }
            }
        }

        if (ans.empty()) {
            cout << "嘉油！\n";
        } else {
            sort(ans.begin(), ans.end());
            for (size_t i = 0; i < ans.size(); ++i) {
                cout << ans[i] << "\n";
            }
        }
    }

    return 0;
}
