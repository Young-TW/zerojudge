#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int R, C;
    while (cin >> R >> C) {
        string s;
        cin >> s;
        
        vector<string> grid(R, string(C, '.'));
        
        int r = 0, c = 0;
        if (R > 0 && C > 0) grid[r][c] = '*';
        
        int dr[] = {0, 1, 0, -1};
        int dc[] = {1, 0, -1, 0};
        int dir = 0;
        
        for (int i = 0; i < (int)s.size(); i++) {
            int d = s[i] - '0';
            for (int j = 0; j < d; j++) {
                int nr = r + dr[dir];
                int nc = c + dc[dir];
                if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                    r = nr;
                    c = nc;
                    grid[r][c] = '*';
                } else {
                    break;
                }
            }
            dir = (dir + 1) % 4;
        }
        
        for (int i = 0; i < R; i++) {
            cout << grid[i] << '\n';
        }
    }
    
    return 0;
}
