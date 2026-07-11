#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<string> maze(N);
        for (int i = 0; i < N; ++i) {
            cin >> maze[i];
        }
        
        int start_r = 1, start_c = 1;
        int end_r = N - 2, end_c = N - 2;
        
        if (start_r < 0 || start_r >= N || start_c < 0 || start_c >= N ||
            end_r < 0 || end_r >= N || end_c < 0 || end_c >= N ||
            maze[start_r][start_c] == '#' || maze[end_r][end_c] == '#') {
            cout << "No solution!\n";
            continue;
        }
        
        vector<vector<int>> dist(N, vector<int>(N, -1));
        queue<pair<int, int>> q;
        
        q.push({start_r, start_c});
        dist[start_r][start_c] = 1;
        
        bool found = false;
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        
        while (!q.empty()) {
            pair<int, int> curr = q.front();
            q.pop();
            int r = curr.first;
            int c = curr.second;
            
            if (r == end_r && c == end_c) {
                cout << dist[r][c] << "\n";
                found = true;
                break;
            }
            
            for (int i = 0; i < 4; ++i) {
                int nr = r + dx[i];
                int nc = c + dy[i];
                
                if (nr >= 0 && nr < N && nc >= 0 && nc < N && maze[nr][nc] == '.' && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
        
        if (!found) {
            cout << "No solution!\n";
        }
    }
    return 0;
}
