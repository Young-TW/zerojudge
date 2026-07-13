#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

int get_pixel(const vector<vector<vector<int>>>& img, int x, int y, int c, int curr_W, int curr_H) {
    if (x < 0 || x >= curr_W || y < 0 || y >= curr_H) return 0;
    return img[y][x][c];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    while (cin >> N) {
        int W, H;
        if (!(cin >> W >> H)) break;

        vector<vector<vector<int>>> img(H, vector<vector<int>>(W, vector<int>(3)));
        for (int y = 0; y < H; ++y) {
            for (int x = 0; x < W; ++x) {
                cin >> img[y][x][0] >> img[y][x][1] >> img[y][x][2];
            }
        }

        vector<vector<int>> energy(H, vector<int>(W));
        vector<vector<int>> dp(H, vector<int>(W));
        vector<vector<int>> trace(H, vector<int>(W));
        vector<int> seam(H);

        int curr_W = W;
        for (int i = 0; i < N; ++i) {
            for (int y = 0; y < H; ++y) {
                for (int x = 0; x < curr_W; ++x) {
                    int total_energy = 0;
                    for (int c = 0; c < 3; ++c) {
                        int p00 = get_pixel(img, x-1, y-1, c, curr_W, H);
                        int p01 = get_pixel(img, x,   y-1, c, curr_W, H);
                        int p02 = get_pixel(img, x+1, y-1, c, curr_W, H);
                        int p10 = get_pixel(img, x-1, y,   c, curr_W, H);
                        int p12 = get_pixel(img, x+1, y,   c, curr_W, H);
                        int p20 = get_pixel(img, x-1, y+1, c, curr_W, H);
                        int p21 = get_pixel(img, x,   y+1, c, curr_W, H);
                        int p22 = get_pixel(img, x+1, y+1, c, curr_W, H);

                        int sx = -p00 + p02 - 2*p10 + 2*p12 - p20 + p22;
                        int sy = -p00 - 2*p01 - p02 + p20 + 2*p21 + p22;
                        total_energy += abs(sx) + abs(sy);
                    }
                    energy[y][x] = total_energy;
                }
            }

            for (int y = 0; y < H; ++y) {
                for (int x = 0; x < curr_W; ++x) {
                    if (y == 0) {
                        dp[y][x] = energy[y][x];
                        trace[y][x] = -1;
                    } else {
                        int min_prev = dp[y-1][x];
                        int best_prev_x = x;
                        if (x > 0 && dp[y-1][x-1] <= min_prev) {
                            min_prev = dp[y-1][x-1];
                            best_prev_x = x-1;
                        }
                        if (x < curr_W - 1 && dp[y-1][x+1] < min_prev) {
                            min_prev = dp[y-1][x+1];
                            best_prev_x = x+1;
                        }
                        dp[y][x] = energy[y][x] + min_prev;
                        trace[y][x] = best_prev_x;
                    }
                }
            }

            int min_val = dp[H-1][0];
            int best_x = 0;
            for (int x = 1; x < curr_W; ++x) {
                if (dp[H-1][x] < min_val) {
                    min_val = dp[H-1][x];
                    best_x = x;
                }
            }

            int curr_x = best_x;
            for (int y = H-1; y >= 0; --y) {
                seam[y] = curr_x;
                curr_x = trace[y][curr_x];
            }

            for (int y = 0; y < H; ++y) {
                int seam_x = seam[y];
                for (int x = seam_x; x < curr_W - 1; ++x) {
                    img[y][x][0] = img[y][x+1][0];
                    img[y][x][1] = img[y][x+1][1];
                    img[y][x][2] = img[y][x+1][2];
                }
            }
            curr_W--;
        }

        cout << curr_W << " " << H << "\n";
        for (int y = 0; y < H; ++y) {
            for (int x = 0; x < curr_W; ++x) {
                cout << img[y][x][0] << " " << img[y][x][1] << " " << img[y][x][2];
                if (x == curr_W - 1) cout << "\n";
                else cout << " ";
            }
        }
    }

    return 0;
}
