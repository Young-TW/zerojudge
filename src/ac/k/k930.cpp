#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int R, C;
    while (cin >> R >> C) {
        vector<vector<int>> grid(R, vector<int>(C));
        vector<vector<bool>> visited(R, vector<bool>(C, false));
        
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                cin >> grid[i][j];
            }
        }
        
        vector<int> perimeters;
        
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    queue<pair<int, int>> q;
                    q.push({i, j});
                    visited[i][j] = true;
                    int perimeter = 0;
                    
                    while (!q.empty()) {
                        pair<int, int> curr = q.front();
                        q.pop();
                        int cr = curr.first;
                        int cc = curr.second;
                        int p = 4;
                        
                        for (int k = 0; k < 4; ++k) {
                            int nr = cr + dx[k];
                            int nc = cc + dy[k];
                            if (nr >= 0 && nr < R && nc >= 0 && nc < C && grid[nr][nc] == 1) {
                                p--;
                                if (!visited[nr][nc]) {
                                    visited[nr][nc] = true;
                                    q.push({nr, nc});
                                }
                            }
                        }
                        perimeter += p;
                    }
                    perimeters.push_back(perimeter);
                }
            }
        }
        
        sort(perimeters.begin(), perimeters.end());
        
        for (size_t i = 0; i < perimeters.size(); ++i) {
            cout << perimeters[i] << (i == perimeters.size() - 1 ? "" : " ");
        }
        cout << "\n";
    }
    
    return 0;
}
