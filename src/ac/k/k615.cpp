#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    while (cin >> n >> m) {
        vector<string> grid(n);
        for (int i = 0; i < n; ++i) {
            cin >> grid[i];
        }
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] >= '1' && grid[i][j] <= '8') {
                    int p_count = 0;
                    int h_count = 0;
                    for (int di = -1; di <= 1; ++di) {
                        for (int dj = -1; dj <= 1; ++dj) {
                            if (di == 0 && dj == 0) continue;
                            int ni = i + di;
                            int nj = j + dj;
                            if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
                                if (grid[ni][nj] == 'P') {
                                    p_count++;
                                } else if (grid[ni][nj] == '#') {
                                    h_count++;
                                }
                            }
                        }
                    }
                    if (p_count == (grid[i][j] - '0') && h_count > 0) {
                        cout << 'O';
                    } else {
                        cout << grid[i][j];
                    }
                } else {
                    cout << grid[i][j];
                }
            }
            cout << "\n";
        }
    }
    
    return 0;
}
