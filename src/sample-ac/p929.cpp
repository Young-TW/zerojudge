#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int R, C, H, W;
    while (cin >> R >> C >> H >> W) {
        vector<vector<int>> grid(R, vector<int>(C));
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                cin >> grid[i][j];
            }
        }
        
        string row_str;
        for (int i = 0; i < R; ++i) {
            row_str.clear();
            for (int j = 0; j < C; ++j) {
                for (int w = 0; w < W; ++w) {
                    if (j > 0 || w > 0) row_str += ' ';
                    row_str += ('0' + grid[i][j]);
                }
            }
            row_str += '\n';
            for (int h = 0; h < H; ++h) {
                cout << row_str;
            }
        }
    }
    return 0;
}
