#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int W, H;
    while (cin >> W >> H) {
        vector<vector<int>> matrix(H, vector<int>(W));
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                cin >> matrix[i][j];
            }
        }
        
        for (int i = 0; i < 2 * H; ++i) {
            int r = (i < H) ? i : (2 * H - 1 - i);
            for (int j = 0; j < 2 * W; ++j) {
                int c = (j < W) ? j : (2 * W - 1 - j);
                cout << matrix[r][c] << (j == 2 * W - 1 ? '\n' : ' ');
            }
        }
    }
    
    return 0;
}
