#include <bits/stdc++.h>
using namespace std;

/*
   a820  小精靈吃數字

   在 (寬 W) x (高 H) 的方格地圖上，小精靈從邊緣某方格的某個角進入，
   往該角在該格的對角方向 (45 度) 前進，沿路吃掉經過每一格的數字
   (路徑重疊時重複計算)。碰到地圖邊界依反射定律反彈；碰到四個角時原路反彈。
   經過三次反彈後 (下一次碰到邊界即) 離開地圖。

   輸入：
     第一行 W H (第一數=每列的行數=寬=欄數，第二數=列數=高)
     接著 H 行，每行 W 個整數 (第一列由左到右)
     最後一行 X Y A：進入方格座標 (X=欄 1..W, Y=列 1..H) 與進入角
        A=1 右上角(往左下)、2 左上角(往右下)、3 左下角(往右上)、4 右下角(往左上)

   用格點座標模擬：格點 (px,py)，px∈[0,W], py∈[0,H]，
   方向 (vx,vy)∈{-1,+1}^2。每一步從一個格點走到相鄰格點，
   所經過的方格 = (row = vy>0?py:py-1, col = vx>0?px:px-1)。
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int W, H;
    while (cin >> W >> H) {
        vector<vector<long long>> g(H, vector<long long>(W));
        for (int i = 0; i < H; ++i)
            for (int j = 0; j < W; ++j)
                cin >> g[i][j];

        long long X, Y; int A;
        cin >> X >> Y >> A;

        int ccol = (int)X - 1, crow = (int)Y - 1;
        int px, py, vx, vy;
        if (A == 1)      { px = ccol + 1; py = crow;     vx = -1; vy =  1; } // 右上角 -> 左下
        else if (A == 2) { px = ccol;     py = crow;     vx =  1; vy =  1; } // 左上角 -> 右下
        else if (A == 3) { px = ccol;     py = crow + 1; vx =  1; vy = -1; } // 左下角 -> 右上
        else             { px = ccol + 1; py = crow + 1; vx = -1; vy = -1; } // 右下角 -> 左上

        long long total = 0;
        int bounces = 0;
        while (true) {
            int col = (vx > 0) ? px : px - 1;
            int row = (vy > 0) ? py : py - 1;
            total += g[row][col];

            px += vx; py += vy;

            bool hitV = (px == 0 || px == W);
            bool hitH = (py == 0 || py == H);
            if (hitV || hitH) {
                if (bounces >= 3) break;   // 第四次碰邊 = 離開地圖
                if (hitV) vx = -vx;
                if (hitH) vy = -vy;
                ++bounces;
            }
        }

        cout << total << '\n';
    }
    return 0;
}
