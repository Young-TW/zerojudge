#include <iostream>
#include <vector>
using namespace std;

int main() {
    int M, N, k, r, c;
    while (cin >> M >> N >> k >> r >> c) {
        vector<vector<int>> grid(M, vector<int>(N));
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> grid[i][j];
            }
        }

        // 方向：0:右，1:下，2:左，3:上
        int dir = 0;
        int dr[] = {0, 1, 0, -1};
        int dc[] = {1, 0, -1, 0};

        long long score = 0;
        int gems_collected = 0;

        // 模擬過程
        while (true) {
            // 檢查當前格子寶石數量
            if (grid[r][c] == 0) {
                break;
            }

            // 撿起一顆寶石
            score += grid[r][c];
            grid[r][c]--;
            gems_collected++;

            // 若 score 是 k 的倍數，向右轉 90 度
            if (score % k == 0) {
                dir = (dir + 1) % 4;
            }

            // 檢查前方是否為牆壁或邊界，若是則持續右轉
            while (true) {
                int nr = r + dr[dir];
                int nc = c + dc[dir];
                
                // 檢查是否超出邊界或碰到牆壁
                if (nr < 0 || nr >= M || nc < 0 || nc >= N || grid[nr][nc] == -1) {
                    dir = (dir + 1) % 4;
                } else {
                    break;
                }
            }

            // 移動到下一個格子
            r += dr[dir];
            c += dc[dir];
        }

        cout << gems_collected << endl;
    }
    return 0;
}
