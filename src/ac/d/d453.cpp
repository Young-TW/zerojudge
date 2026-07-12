#include <iostream>
#include <string>
#include <queue>
#include <cstring>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N) {
        while (N--) {
            int n, m, sr, sc, er, ec;
            cin >> n >> m >> sr >> sc >> er >> ec;
            sr--; sc--; er--; ec--;

            string grid[105];
            for (int i = 0; i < n; ++i) {
                cin >> grid[i];
            }

            if (sr < 0 || sr >= n || sc < 0 || sc >= m || er < 0 || er >= n || ec < 0 || ec >= m) {
                cout << 0 << "\n";
                continue;
            }

            if (grid[sr][sc] == '1' || grid[er][ec] == '1') {
                cout << 0 << "\n";
                continue;
            }

            int dist[105][105];
            memset(dist, 0, sizeof(dist));

            queue<pair<int, int>> q;
            q.push({sr, sc});
            dist[sr][sc] = 1;

            int dr[] = {1, -1, 0, 0};
            int dc[] = {0, 0, 1, -1};

            int ans = 0;
            while (!q.empty()) {
                pair<int, int> curr = q.front();
                q.pop();
                int r = curr.first;
                int c = curr.second;

                if (r == er && c == ec) {
                    ans = dist[r][c];
                    break;
                }

                for (int i = 0; i < 4; ++i) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];

                    if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                        if (grid[nr][nc] == '0' && dist[nr][nc] == 0) {
                            dist[nr][nc] = dist[r][c] + 1;
                            q.push({nr, nc});
                        }
                    }
                }
            }

            cout << ans << "\n";
        }
    }

    return 0;
}
