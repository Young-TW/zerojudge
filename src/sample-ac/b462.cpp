#include <iostream>
#include <cmath>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    double aR, bR, aG, bG, aB, bB;
    while (cin >> aR >> bR >> aG >> bG >> aB >> bB) {
        int W, H;
        if (!(cin >> W >> H)) break;
        cout << W << " " << H << "\n";
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                int r, g, b;
                cin >> r >> g >> b;
                
                int nr = static_cast<int>(round(aR * r + bR));
                int ng = static_cast<int>(round(aG * g + bG));
                int nb = static_cast<int>(round(aB * b + bB));
                
                if (nr < 0) nr = 0;
                if (nr > 255) nr = 255;
                if (ng < 0) ng = 0;
                if (ng > 255) ng = 255;
                if (nb < 0) nb = 0;
                if (nb > 255) nb = 255;
                
                if (j > 0) cout << " ";
                cout << nr << " " << ng << " " << nb;
            }
            cout << "\n";
        }
    }
    return 0;
}
