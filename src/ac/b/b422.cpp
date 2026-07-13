#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int W, H;
    while (cin >> W >> H) {
        cout << W << " " << H << "\n";
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                int r, g, b;
                cin >> r >> g >> b;
                int gray = (r + g + b + 1) / 3;
                if (j > 0) cout << " ";
                cout << gray << " " << gray << " " << gray;
            }
            cout << "\n";
        }
    }
    
    return 0;
}
