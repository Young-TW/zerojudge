#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

struct Point {
    int l, r, c;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int L, R, C;
    while (cin >> L >> R >> C && (L || R || C)) {
        vector<vector<string>> grid(L, vector<string>(R));
        for (int i = 0; i < L; ++i) {
            for (int j = 0; j < R; ++j) {
                cin >> grid[i][j];
            }
        }
        
        int dl[] = {1, -1, 0, 0, 0, 0};
        int dr[] = {0, 0, 1, -1, 0, 0};
        int dc[] = {0, 0, 0, 0, 1, -1};
        
        vector<vector<vector<int>>> dist(L, vector<vector<int>>(R, vector<int>(C, -1)));
        queue<Point> q;
        
        for (int i = 0; i < L; ++i) {
            for (int j = 0; j < R; ++j) {
                for (int k = 0; k < C; ++k) {
                    if (grid[i][j][k] == 'S') {
                        q.push({i, j, k});
                        dist[i][j][k] = 0;
                    }
                }
            }
        }
        
        int ans = -1;
        while (!q.empty()) {
            Point curr = q.front();
            q.pop();
            
            if (grid[curr.l][curr.r][curr.c] == 'E') {
                ans = dist[curr.l][curr.r][curr.c];
                break;
            }
            
            for (int i = 0; i < 6; ++i) {
                int nl = curr.l + dl[i];
                int nr = curr.r + dr[i];
                int nc = curr.c + dc[i];
                
                if (nl >= 0 && nl < L && nr >= 0 && nr < R && nc >= 0 && nc < C) {
                    if (dist[nl][nr][nc] == -1 && grid[nl][nr][nc] != '#') {
                        dist[nl][nr][nc] = dist[curr.l][curr.r][curr.c] + 1;
                        q.push({nl, nr, nc});
                    }
                }
            }
        }
        
        if (ans != -1) {
            cout << "Escaped in " << ans << " minute(s).\n";
        } else {
            cout << "Trapped!\n";
        }
    }
    
    return 0;
}
