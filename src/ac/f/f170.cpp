#include <iostream>
#include <queue>
#include <utility>

using namespace std;

const int MAXN = 1005;
int grid[MAXN][MAXN];
int vis[MAXN][MAXN];
int vis_token = 0;

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    while (cin >> N) {
        int start_H, start_L;
        cin >> start_H >> start_L;
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> grid[i][j];
            }
        }

        vis_token++;
        queue<pair<int, int>> q;
        q.push({start_H, start_L});
        vis[start_H][start_L] = vis_token;
        int ans = 1;

        while (!q.empty()) {
            pair<int, int> curr = q.front();
            q.pop();
            int r = curr.first;
            int c = curr.second;

            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
                    if (vis[nr][nc] != vis_token) {
                        int diff = grid[r][c] - grid[nr][nc];
                        if (diff < 0) diff = -diff;
                        if (diff <= 2) {
                            vis[nr][nc] = vis_token;
                            ans++;
                            q.push({nr, nc});
                        }
                    }
                }
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
