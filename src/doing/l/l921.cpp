#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int K;
    while (cin >> K) {
        int N;
        cin >> N;
        vector<vector<bool>> given(K, vector<bool>(K, false));
        for (int i = 0; i < N; ++i) {
            int x, y;
            cin >> x >> y;
            if (x >= 0 && x < K && y >= 0 && y < K) {
                given[x][y] = true;
            }
        }
        
        int size = 2 * K - 1;
        vector<string> grid(size, string(size, '#'));
        
        // Mark given points
        for (int x = 0; x < K; ++x) {
            for (int y = 0; y < K; ++y) {
                if (given[x][y]) {
                    grid[2*x][2*y] = '&';
                }
            }
        }
        
        // Draw edges: horizontal neighbors -> '|', vertical neighbors -> '-'
        for (int x = 0; x < K; ++x) {
            for (int y = 0; y < K; ++y) {
                if (given[x][y]) {
                    if (x + 1 < K && given[x+1][y]) {
                        grid[2*x+1][2*y] = '|';
                    }
                    if (y + 1 < K && given[x][y+1]) {
                        grid[2*x][2*y+1] = '-';
                    }
                }
            }
        }
        
        // Draw centers of squares
        for (int x = 0; x < K-1; ++x) {
            for (int y = 0; y < K-1; ++y) {
                int cnt = given[x][y] + given[x][y+1] + given[x+1][y] + given[x+1][y+1];
                if (cnt == 4) {
                    grid[2*x+1][2*y+1] = 'X';
                } else if (cnt == 3) {
                    grid[2*x+1][2*y+1] = '\\';
                }
            }
        }
        
        // Output
        for (int i = 0; i < size; ++i) {
            cout << grid[i] << '\n';
        }
    }
    
    return 0;
}
