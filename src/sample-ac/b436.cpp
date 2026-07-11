#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int W, H;
    while (cin >> W >> H) {
        vector<vector<vector<int>>> img(H, vector<vector<int>>(W, vector<int>(3)));
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                for (int k = 0; k < 3; ++k) {
                    cin >> img[i][j][k];
                }
            }
        }

        cout << W << " " << H << "\n";

        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                for (int k = 0; k < 3; ++k) {
                    int y_up = max(0, i - 1);
                    int y_down = min(H - 1, i + 1);
                    int x_left = max(0, j - 1);
                    int x_right = min(W - 1, j + 1);

                    int p00 = img[y_up][x_left][k];
                    int p01 = img[y_up][j][k];
                    int p02 = img[y_up][x_right][k];
                    int p10 = img[i][x_left][k];
                    int p12 = img[i][x_right][k];
                    int p20 = img[y_down][x_left][k];
                    int p21 = img[y_down][j][k];
                    int p22 = img[y_down][x_right][k];

                    int sx = -p00 + p02 - 2 * p10 + 2 * p12 - p20 + p22;
                    int sy = -p00 - 2 * p01 - p02 + p20 + 2 * p21 + p22;

                    int grad = abs(sx) + abs(sy);
                    int val = (grad + 4) / 8;

                    cout << val;
                    if (k < 2) cout << " ";
                }
                if (j < W - 1) cout << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}
