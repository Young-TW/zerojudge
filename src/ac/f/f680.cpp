#include <iostream>

using namespace std;

int N;
int grid[105][105];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void dfs(int i, int j, int color) {
    if (i < 0 || i >= N || j < 0 || j >= N) return;
    if (grid[i][j] != color) return;
    grid[i][j] = 0;
    for (int k = 0; k < 4; k++) {
        dfs(i + dx[k], j + dy[k], color);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> N) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> grid[i][j];
            }
        }
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] != 0) {
                    cnt++;
                    dfs(i, j, grid[i][j]);
                }
            }
        }
        cout << cnt << "\n";
    }
    return 0;
}
