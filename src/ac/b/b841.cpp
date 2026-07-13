#include <iostream>
#include <cstring>

using namespace std;

int H, W;
int grid[7][7];
int match[7][7];
bool visited[7][7];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

bool dfs(int r, int c) {
    for (int i = 0; i < 4; ++i) {
        int nr = r + dx[i];
        int nc = c + dy[i];
        if (nr >= 0 && nr < H && nc >= 0 && nc < W) {
            if (grid[r][c] == grid[nr][nc] && !visited[nr][nc]) {
                visited[nr][nc] = true;
                if (match[nr][nc] == -1 || dfs(match[nr][nc] / W, match[nr][nc] % W)) {
                    match[nr][nc] = r * W + c;
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> H >> W) {
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                cin >> grid[i][j];
            }
        }
        memset(match, -1, sizeof(match));
        int ans = 0;
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                if ((i + j) % 2 == 0) {
                    memset(visited, false, sizeof(visited));
                    if (dfs(i, j)) {
                        ans++;
                    }
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
