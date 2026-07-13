#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<vector<int>> grid(n, vector<int>(n, 0));
        int r = 0, c = n / 2;
        grid[r][c] = 1;
        
        for (int k = 2; k <= n * n; ++k) {
            if (r == 0 && c == n - 1) {
                r = 1;
            } else {
                int nr = (r - 1 + n) % n;
                int nc = (c + 1) % n;
                if (grid[nr][nc] != 0) {
                    r = r + 1;
                } else {
                    r = nr;
                    c = nc;
                }
            }
            grid[r][c] = k;
        }
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << grid[i][j] << (j == n - 1 ? "" : " ");
            }
            cout << "\n";
        }
    }
    
    return 0;
}
