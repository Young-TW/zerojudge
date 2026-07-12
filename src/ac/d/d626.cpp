#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        vector<string> grid(n);
        for (int i = 0; i < n; ++i) {
            cin >> grid[i];
        }

        int r, c;
        cin >> r >> c;

        if (r >= 0 && r < n && c >= 0 && c < n && grid[r][c] == '-') {
            queue<pair<int, int>> q;
            grid[r][c] = '+';
            q.push({r, c});

            int dr[] = {-1, 1, 0, 0};
            int dc[] = {0, 0, -1, 1};

            while (!q.empty()) {
                pair<int, int> curr = q.front();
                q.pop();
                int cr = curr.first;
                int cc = curr.second;

                for (int i = 0; i < 4; ++i) {
                    int nr = cr + dr[i];
                    int nc = cc + dc[i];

                    if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                        if (grid[nr][nc] == '-') {
                            grid[nr][nc] = '+';
                            q.push({nr, nc});
                        }
                    }
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            cout << grid[i] << "\n";
        }
    }

    return 0;
}
