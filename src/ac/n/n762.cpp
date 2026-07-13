#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        int n;
        cin >> n;
        
        vector<string> mine(n);
        vector<string> touch(n);
        
        for (int i = 0; i < n; ++i) {
            cin >> mine[i];
        }
        for (int i = 0; i < n; ++i) {
            cin >> touch[i];
        }
        
        bool touched_mine = false;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (touch[i][j] == 'x' && mine[i][j] == '*') {
                    touched_mine = true;
                    break;
                }
            }
            if (touched_mine) break;
        }
        
        vector<string> ans(n, string(n, '.'));
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (mine[i][j] == '*') {
                    if (touched_mine) {
                        ans[i][j] = '*';
                    } else {
                        ans[i][j] = '.';
                    }
                } else {
                    if (touch[i][j] == 'x') {
                        int cnt = 0;
                        for (int dx = -1; dx <= 1; ++dx) {
                            for (int dy = -1; dy <= 1; ++dy) {
                                if (dx == 0 && dy == 0) continue;
                                int ni = i + dx;
                                int nj = j + dy;
                                if (ni >= 0 && ni < n && nj >= 0 && nj < n) {
                                    if (mine[ni][nj] == '*') {
                                        cnt++;
                                    }
                                }
                            }
                        }
                        ans[i][j] = '0' + cnt;
                    } else {
                        ans[i][j] = '.';
                    }
                }
            }
        }
        
        for (int i = 0; i < n; ++i) {
            cout << ans[i] << "\n";
        }
        
        if (T > 0) {
            cout << "\n";
        }
    }
    
    return 0;
}
