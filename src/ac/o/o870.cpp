#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int H, W;
    if (!(cin >> H >> W)) return 0;

    vector<string> grid(H);
    for (int i = 0; i < H; ++i) {
        cin >> grid[i];
    }

    int T;
    cin >> T;

    vector<vector<int>> dist(H, vector<int>(W, -1));
    queue<pair<int, int>> q;

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (grid[i][j] == '-') {
                dist[i][j] = 0;
                q.push({i, j});
            }
        }
    }

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();
        int r = curr.first;
        int c = curr.second;

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < H && nc >= 0 && nc < W) {
                if (grid[nr][nc] == '*' && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
    }

    vector<long long> counts(T, 0);

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (grid[i][j] == '*' && dist[i][j] > 0) {
                int type = (dist[i][j] - 1) % T;
                counts[type]++;
            }
        }
    }

    for (int i = 0; i < T; ++i) {
        if (i > 0) cout << " ";
        cout << counts[i];
    }
    cout << "\n";

    return 0;
}
