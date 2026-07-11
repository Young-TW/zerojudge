#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int X, Y;
    double OPACITY;

    while (cin >> X >> Y >> OPACITY) {
        int W1, H1;
        if (!(cin >> W1 >> H1)) break;
        vector<int> fg(W1 * H1 * 3);
        for (int i = 0; i < W1 * H1 * 3; ++i) {
            cin >> fg[i];
        }

        int W2, H2;
        if (!(cin >> W2 >> H2)) break;
        vector<int> bg(W2 * H2 * 3);
        for (int i = 0; i < W2 * H2 * 3; ++i) {
            cin >> bg[i];
        }

        for (int y = 0; y < H1; ++y) {
            for (int x = 0; x < W1; ++x) {
                int bx = X + x;
                int by = Y + y;
                if (bx >= 0 && bx < W2 && by >= 0 && by < H2) {
                    int fg_idx = (y * W1 + x) * 3;
                    int bg_idx = (by * W2 + bx) * 3;
                    
                    for (int c = 0; c < 3; ++c) {
                        double fore = fg[fg_idx + c];
                        double back = bg[bg_idx + c];
                        double val = fore * OPACITY + back * (1.0 - OPACITY);
                        int new_val = (int)round(val);
                        if (new_val < 0) new_val = 0;
                        if (new_val > 255) new_val = 255;
                        bg[bg_idx + c] = new_val;
                    }
                }
            }
        }

        cout << W2 << " " << H2 << "\n";
        for (int y = 0; y < H2; ++y) {
            for (int x = 0; x < W2; ++x) {
                for (int c = 0; c < 3; ++c) {
                    cout << bg[(y * W2 + x) * 3 + c];
                    if (x == W2 - 1 && c == 2) {
                        cout << "\n";
                    } else {
                        cout << " ";
                    }
                }
            }
        }
    }

    return 0;
}
