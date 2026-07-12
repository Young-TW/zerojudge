#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <utility>

using namespace std;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void bfs(int r, int c, int H, int W, const vector<string>& grid, vector<vector<bool>>& visited) {
    char lang = grid[r][c];
    queue<pair<int, int>> q;
    q.push({r, c});
    visited[r][c] = true;
    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int nr = curr.first + dx[i];
            int nc = curr.second + dy[i];
            if (nr >= 0 && nr < H && nc >= 0 && nc < W && !visited[nr][nc] && grid[nr][nc] == lang) {
                visited[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    int case_num = 1;
    while (cin >> N) {
        for (int t = 0; t < N; ++t) {
            int H, W;
            cin >> H >> W;
            vector<string> grid(H);
            for (int i = 0; i < H; ++i) {
                cin >> grid[i];
            }
            
            vector<vector<bool>> visited(H, vector<bool>(W, false));
            int counts[26] = {0};
            
            for (int i = 0; i < H; ++i) {
                for (int j = 0; j < W; ++j) {
                    if (!visited[i][j]) {
                        char lang = grid[i][j];
                        counts[lang - 'a']++;
                        bfs(i, j, H, W, grid, visited);
                    }
                }
            }
            
            vector<pair<int, char>> res;
            for (int i = 0; i < 26; ++i) {
                if (counts[i] > 0) {
                    res.push_back({counts[i], 'a' + i});
                }
            }
            
            sort(res.begin(), res.end(), [](const pair<int, char>& a, const pair<int, char>& b) {
                if (a.first != b.first) {
                    return a.first > b.first;
                }
                return a.second < b.second;
            });
            
            cout << "World #" << case_num << "\n";
            for (size_t i = 0; i < res.size(); ++i) {
                cout << res[i].second << ": " << res[i].first << "\n";
            }
            case_num++;
        }
    }
    return 0;
}
