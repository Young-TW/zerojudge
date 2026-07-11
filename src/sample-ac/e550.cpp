#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <utility>
#include <limits>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    
    bool first = true;
    while (T--) {
        int r, c;
        if (!(cin >> r >> c)) break;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        vector<string> grid;
        string line;
        while (getline(cin, line)) {
            if (line.empty()) break;
            grid.push_back(line);
        }
        
        int ans = 0;
        if (r > 0 && c > 0 && r <= (int)grid.size() && c <= (int)grid[r-1].size() && grid[r-1][c-1] == '0') {
            queue<pair<int, int>> q;
            q.push({r-1, c-1});
            grid[r-1][c-1] = '1';
            ans = 1;
            int dr[] = {0, 0, 1, -1};
            int dc[] = {1, -1, 0, 0};
            while (!q.empty()) {
                auto curr = q.front(); q.pop();
                for (int i = 0; i < 4; ++i) {
                    int nr = curr.first + dr[i];
                    int nc = curr.second + dc[i];
                    if (nr >= 0 && nr < (int)grid.size() && nc >= 0 && nc < (int)grid[nr].size() && grid[nr][nc] == '0') {
                        grid[nr][nc] = '1';
                        q.push({nr, nc});
                        ans++;
                    }
                }
            }
        }
        
        if (!first) cout << "\n";
        cout << ans << "\n";
        first = false;
    }
    
    return 0;
}
