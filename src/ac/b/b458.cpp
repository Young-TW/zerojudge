#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long T;
    int W, H;
    
    while (cin >> T >> W >> H) {
        cout << W << " " << H << "\n";
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                int r, g, b;
                cin >> r >> g >> b;
                double brightness = (r + g + b) / 3.0;
                if (brightness >= T) {
                    cout << 255 << " " << 255 << " " << 255;
                } else {
                    cout << 0 << " " << 0 << " " << 0;
                }
                if (j == W - 1) {
                    cout << "\n";
                } else {
                    cout << " ";
                }
            }
        }
    }
    
    return 0;
}
