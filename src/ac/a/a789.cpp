// a789. Diffusion Limited Aggregation (DLA)
// 自寫解答 (self-written; no external source copied)
//
// 每組測資:11x11 高度陣列,接著多個 (x,y) 雨滴起點,讀到 -1 -1 結束該組。
// 座標 (0,0) 為左上角,x 為 column(往右),y 為 row(往下) => h[y][x]。
//
// 流動規則(依題目字面):
//   水滴流向周圍 8 格中「更低且最低」的那一格。
//   若沒有更低的格,或那個最低格已經流過(visited),則停止。
// 也就是:先鎖定唯一的「最低下坡目標」,只有兩種停止情形——沒有下坡、或該
// 目標已被流過。並非「跳過已流過的、改找次低」。
//
// 平手處理:當多個鄰格同為最低高度時,搜尋順序決定選誰。採用討論區確認可
// AC 的順序:dx={-1,0,1,1,1,0,-1,-1}, dy={-1,-1,-1,0,1,1,1,0}
// (以「嚴格較小才更新」實作 => 平手時取順序在前者)。
//
// 複雜度:每滴水每步高度嚴格下降 => 至多 121 步,遠低於 TLE 門檻。
#include <bits/stdc++.h>
using namespace std;
const int N = 11;
const int DX[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
const int DY[8] = {-1, -1, -1, 0, 1, 1, 1, 0};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int h[N][N];
    while (cin >> h[0][0]) {                 // 讀下一組高度陣列;EOF 結束
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) {
                if (i == 0 && j == 0) continue;
                cin >> h[i][j];
            }
        bool vis[N][N] = {};
        int x, y;
        while (cin >> x >> y) {
            if (x == -1 && y == -1) break;
            int cx = x, cy = y;
            vis[cy][cx] = true;              // 標記起點
            while (true) {
                int bestH = INT_MAX, bx = -1, by = -1;
                for (int d = 0; d < 8; ++d) {
                    int nx = cx + DX[d], ny = cy + DY[d];
                    if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
                    if (h[ny][nx] < h[cy][cx] && h[ny][nx] < bestH) {
                        bestH = h[ny][nx];   // 嚴格較小才更新 => 平手取順序在前
                        bx = nx; by = ny;
                    }
                }
                if (bx < 0) break;           // 沒有更低的鄰格
                if (vis[by][bx]) break;      // 最低目標已流過 => 停止
                cx = bx; cy = by;
                vis[cy][cx] = true;
            }
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) putchar(vis[i][j] ? '*' : '.');
            putchar('\n');
        }
    }
    return 0;
}
