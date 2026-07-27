#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int W, H;
    while (cin >> W >> H) {
        vector<int> cntR(256, 0), cntG(256, 0), cntB(256, 0), cntL(256, 0);
        for (int y = 0; y < H; ++y) {
            for (int x = 0; x < W; ++x) {
                int r, g, b;
                cin >> r >> g >> b;
                ++cntR[r];
                ++cntG[g];
                ++cntB[b];
                int bright = static_cast<int>(round((r + g + b) / 3.0));
                ++cntL[bright];
            }
        }
        auto print = [](const vector<int>& v) {
            for (int i = 0; i < 256; ++i) {
                if (i) cout << ' ';
                cout << v[i];
            }
            cout << '\n';
        };
        print(cntR);
        print(cntG);
        print(cntB);
        print(cntL);
    }
    return 0;
}
