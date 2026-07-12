#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n && n != 0) {
        char grid[25][25];
        for (int y = n; y >= 1; --y) {
            string row;
            cin >> row;
            for (int x = 1; x <= n; ++x) {
                grid[x][y] = row[x - 1];
            }
        }
        
        int q;
        cin >> q;
        while (q--) {
            int x, y;
            cin >> x >> y;
            
            if (grid[x][y] != '.') {
                cout << "Interesting...\n";
                continue;
            }
            
            int adj_count = 0;
            int adj_O = 0;
            int adj_X = 0;
            
            int dx[] = {0, 0, -1, 1};
            int dy[] = {1, -1, 0, 0};
            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx >= 1 && nx <= n && ny >= 1 && ny <= n) {
                    adj_count++;
                    if (grid[nx][ny] == 'O') adj_O++;
                    if (grid[nx][ny] == 'X') adj_X++;
                }
            }
            
            char C;
            if (adj_O == adj_count && adj_count > 0) {
                C = 'O';
            } else if (adj_X == adj_count && adj_count > 0) {
                C = 'X';
            } else {
                cout << "Interesting...\n";
                continue;
            }
            
            int diag_count = 0;
            int diag_C = 0;
            int ddx[] = {-1, -1, 1, 1};
            int ddy[] = {1, -1, 1, -1};
            for (int i = 0; i < 4; ++i) {
                int nx = x + ddx[i];
                int ny = y + ddy[i];
                if (nx >= 1 && nx <= n && ny >= 1 && ny <= n) {
                    diag_count++;
                    if (grid[nx][ny] == C) diag_C++;
                }
            }
            
            bool is_real = false;
            if (adj_count == 4) {
                if (diag_C >= 3) is_real = true;
            } else if (adj_count == 3) {
                if (diag_C == 2) is_real = true;
            } else if (adj_count == 2) {
                if (diag_C == 1) is_real = true;
            }
            
            if (is_real) {
                cout << "Real!\n";
            } else {
                cout << "Fake!\n";
            }
        }
    }
    return 0;
}
