#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cstring>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (!(cin >> T)) return 0;

    while (T--) {
        int M, N;
        cin >> M >> N;
        vector<string> grid(M);
        for (int i = 0; i < M; ++i) {
            cin >> grid[i];
        }

        bool blocked[105][105];
        memset(blocked, false, sizeof(blocked));

        int start_r = -1, start_c = -1;
        int end_r = -1, end_c = -1;

        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] == 'A') {
                    start_r = i;
                    start_c = j;
                } else if (grid[i][j] == 'B') {
                    end_r = i;
                    end_c = j;
                } else if (grid[i][j] == 'Z') {
                    blocked[i][j] = true;
                }
            }
        }

        int kz_dr[] = {-2, -2, -1, -1, 1, 1, 2, 2};
        int kz_dc[] = {-1, 1, -2, 2, -2, 2, -1, 1};

        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] == 'Z') {
                    for (int k = 0; k < 8; ++k) {
                        int ni = i + kz_dr[k];
                        int nj = j + kz_dc[k];
                        if (ni >= 0 && ni < M && nj >= 0 && nj < N) {
                            if (grid[ni][nj] != 'A' && grid[ni][nj] != 'B') {
                                blocked[ni][nj] = true;
                            }
                        }
                    }
                }
            }
        }

        int king_dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int king_dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

        int dist[105][105];
        memset(dist, -1, sizeof(dist));
        dist[start_r][start_c] = 0;

        queue<pair<int, int>> q;
        q.push({start_r, start_c});

        int ans = -1;

        while (!q.empty()) {
            pair<int, int> curr = q.front();
            q.pop();
            int r = curr.first;
            int c = curr.second;

            if (r == end_r && c == end_c) {
                ans = dist[r][c];
                break;
            }

            for (int k = 0; k < 8; ++k) {
                int nr = r + king_dr[k];
                int nc = c + king_dc[k];
                if (nr >= 0 && nr < M && nc >= 0 && nc < N) {
                    if (dist[nr][nc] == -1 && !blocked[nr][nc]) {
                        dist[nr][nc] = dist[r][c] + 1;
                        q.push({nr, nc});
                    }
                }
            }
        }

        if (ans != -1) {
            cout << "Minimal possible length of a trip is " << ans << "\n";
        } else {
            cout << "King Peter, you can't go now!\n";
        }
    }

    return 0;
}
