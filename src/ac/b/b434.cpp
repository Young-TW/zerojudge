#include <iostream>

using namespace std;

int img[256][256][3];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int W, H;
    while (cin >> W >> H) {
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
                    int dx = (j + 1 < W) ? (img[i][j+1][k] - img[i][j][k]) : 0;
                    int dy = (i + 1 < H) ? (img[i+1][j][k] - img[i][j][k]) : 0;
                    int adx = dx < 0 ? -dx : dx;
                    int ady = dy < 0 ? -dy : dy;
                    int grad = (adx + ady + 1) / 2;
                    cout << grad << " \n"[k == 2 && j == W - 1];
                }
            }
        }
    }
    
    return 0;
}
