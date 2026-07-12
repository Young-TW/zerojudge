#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int M, N;
long long total_paths = 0;
bool visited[12][12];

int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

void dfs(int r, int c, int count) {
    if (count == M * N) {
        total_paths++;
        return;
    }

    for (int i = 0; i < 4; ++i) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        if (nr >= 1 && nr <= M && nc >= 1 && nc <= N && !visited[nr][nc]) {
            visited[nr][nc] = true;
            dfs(nr, nc, count + 1);
            visited[nr][nc] = false;
        }
    }
}

int main() {
    while (cin >> M >> N) {
        total_paths = 0;
        memset(visited, 0, sizeof(visited));

        // 由於路徑可以反向，我們只計算從特定起點出發的路徑，然後除以 2
        // 但更簡單的方法是：固定起點為 (1,1)，計算所有哈密頓路徑，然後乘以 2 (因為起終點可互換)
        // 然而題目說 (1,4)->...->(1,1) 和 (1,1)->...->(1,4) 算是同一個合法路徑
        // 所以我們應該只計算一次。我們可以固定起點為 (1,1)，然後計算所有可能的路徑。
        // 但是起點不一定是 (1,1)。題目要求的是所有可能的合法路徑總數。
        // 關鍵在於：每條無向路徑會被計算兩次（一次從 A 到 B，一次從 B 到 A）。
        // 所以我們可以枚舉所有起點，進行 DFS，最後將結果除以 2。

        // 為了效率，我們可以只從 (1,1) 開始，但這會漏掉那些不以 (1,1) 為端點的路徑嗎？
        // 不，哈密頓路徑的端點可以是任意點。
        // 正確做法：枚舉所有格子作為起點，進行 DFS，最後總數除以 2。

        for (int i = 1; i <= M; ++i) {
            for (int j = 1; j <= N; ++j) {
                memset(visited, 0, sizeof(visited));
                visited[i][j] = true;
                dfs(i, j, 1);
            }
        }

        cout << total_paths / 2 << endl;
    }
    return 0;
}
