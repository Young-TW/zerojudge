#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int H, W, N;
    while (cin >> H >> W >> N) {
        vector<vector<int>> canvas(H, vector<int>(W, 0));
        
        for (int i = 0; i < N; ++i) {
            int r, c, t, x;
            cin >> r >> c >> t >> x;
            
            for (int h = 0; h < H; ++h) {
                for (int w = 0; w < W; ++w) {
                    int dist = abs(h - r) + abs(w - c);
                    if (dist <= t) {
                        canvas[h][w] += x;
                    }
                }
            }
        }
        
        for (int h = 0; h < H; ++h) {
            for (int w = 0; w < W; ++w) {
                cout << canvas[h][w];
                if (w < W - 1) {
                    cout << " ";
                }
            }
            cout << "\n";
        }
    }
    
    return 0;
}
