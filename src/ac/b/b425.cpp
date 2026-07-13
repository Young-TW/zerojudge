#include <iostream>

using namespace std;

int img[256][256][3];
int new_img[256][256][3];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int X, Y, R;
    while (cin >> X >> Y >> R) {
        int W, H;
        if (!(cin >> W >> H)) break;

        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                cin >> img[i][j][0] >> img[i][j][1] >> img[i][j][2];
                new_img[i][j][0] = img[i][j][0];
                new_img[i][j][1] = img[i][j][1];
                new_img[i][j][2] = img[i][j][2];
            }
        }

        if (R >= 0) {
            long long R2 = (long long)R * R;
            for (int y = 0; y < H; ++y) {
                for (int x = 0; x < W; ++x) {
                    long long dx = x - X;
                    long long dy = y - Y;
                    if (dx * dx + dy * dy <= R2) {
                        long long sumR = 0, sumG = 0, sumB = 0, count = 0;
                        for (int ny = y - 5; ny <= y + 5; ++ny) {
                            for (int nx = x - 5; nx <= x + 5; ++nx) {
                                if (nx >= 0 && nx < W && ny >= 0 && ny < H) {
                                    sumR += img[ny][nx][0];
                                    sumG += img[ny][nx][1];
                                    sumB += img[ny][nx][2];
                                    count++;
                                }
                            }
                        }
                        if (count > 0) {
                            new_img[y][x][0] = (sumR + count / 2) / count;
                            new_img[y][x][1] = (sumG + count / 2) / count;
                            new_img[y][x][2] = (sumB + count / 2) / count;
                        }
                    }
                }
            }
        }

        cout << W << " " << H << "\n";
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                cout << new_img[i][j][0] << " " << new_img[i][j][1] << " " << new_img[i][j][2];
                if (j < W - 1) cout << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}
