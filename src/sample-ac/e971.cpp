#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m, n;
    while (cin >> m >> n) {
        vector<vector<int>> grid(m, vector<int>(n));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> grid[i][j];
            }
        }
        
        for (int i = 0; i < m; ++i) {
            int cnt = 0;
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    cnt++;
                }
            }
            
            int ones_seen = 0;
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    ones_seen++;
                } else {
                    if (ones_seen % 2 == 1 && ones_seen < cnt) {
                        grid[i][j] = 1;
                    }
                }
            }
        }
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << grid[i][j];
                if (j < n - 1) {
                    cout << " ";
                }
            }
            cout << "\n";
        }
    }
    
    return 0;
}
