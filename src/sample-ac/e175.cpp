#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n && n != 0) {
        vector<string> board(n);
        for (int i = 0; i < n; ++i) {
            cin >> board[i];
        }
        
        int q;
        cin >> q;
        for (int i = 0; i < q; ++i) {
            int x, y;
            cin >> x >> y;
            
            int r = n - y;
            int c = x - 1;
            
            if (board[r][c] == '.') {
                cout << 0 << "\n";
                continue;
            }
            
            char color = board[r][c];
            vector<vector<bool>> visited(n, vector<bool>(n, false));
            vector<vector<bool>> air_visited(n, vector<bool>(n, false));
            
            queue<pair<int, int>> q_bfs;
            q_bfs.push({r, c});
            visited[r][c] = true;
            
            int liberties = 0;
            int dx[] = {0, 0, 1, -1};
            int dy[] = {1, -1, 0, 0};
            
            while (!q_bfs.empty()) {
                pair<int, int> curr = q_bfs.front();
                q_bfs.pop();
                int cr = curr.first;
                int cc = curr.second;
                
                for (int d = 0; d < 4; ++d) {
                    int nr = cr + dx[d];
                    int nc = cc + dy[d];
                    
                    if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                        if (board[nr][nc] == color) {
                            if (!visited[nr][nc]) {
                                visited[nr][nc] = true;
                                q_bfs.push({nr, nc});
                            }
                        } else if (board[nr][nc] == '.') {
                            if (!air_visited[nr][nc]) {
                                air_visited[nr][nc] = true;
                                liberties++;
                            }
                        }
                    }
                }
            }
            cout << liberties << "\n";
        }
    }
    
    return 0;
}
