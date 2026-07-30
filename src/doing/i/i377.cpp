#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int R, C;
    while (cin >> R >> C) {
        vector<string> grid(R);
        for (int i = 0; i < R; i++) {
            cin >> grid[i];
        }
        string word;
        cin >> word;
        
        int L = (int)word.size();
        
        int dr[] = {0, 1, 1, 1, 0, -1, -1, -1};
        int dc[] = {1, 0, 1, -1, -1, 0, -1, 1};
        
        bool found = false;
        int sr = 0, sc = 0, er = 0, ec = 0;
        
        for (int r = 0; r < R && !found; r++) {
            for (int c = 0; c < C && !found; c++) {
                if (tolower((unsigned char)grid[r][c]) != tolower((unsigned char)word[0])) continue;
                for (int d = 0; d < 8 && !found; d++) {
                    bool match = true;
                    for (int k = 0; k < L; k++) {
                        int nr = r + dr[d] * k;
                        int nc = c + dc[d] * k;
                        if (nr < 0 || nr >= R || nc < 0 || nc >= C) {
                            match = false;
                            break;
                        }
                        if (tolower((unsigned char)grid[nr][nc]) != tolower((unsigned char)word[k])) {
                            match = false;
                            break;
                        }
                    }
                    if (match) {
                        found = true;
                        sr = r + 1;
                        sc = c + 1;
                        er = r + dr[d] * (L - 1) + 1;
                        ec = c + dc[d] * (L - 1) + 1;
                    }
                }
            }
        }
        
        if (found) {
            cout << sr << " " << sc << "\n";
            cout << er << " " << ec << "\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
