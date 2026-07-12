#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    while (cin >> N >> M) {
        vector<vector<int>> grid(N, vector<int>(M));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cin >> grid[i][j];
            }
        }
        
        int Sx, Sy, Ex, Ey;
        cin >> Sx >> Sy >> Ex >> Ey;
        
        if (Sx < 0 || Sx >= N || Sy < 0 || Sy >= M || Ex < 0 || Ex >= N || Ey < 0 || Ey >= M) {
            cout << 0 << "\n";
            continue;
        }
        
        if (grid[Sx][Sy] == 1 || grid[Ex][Ey] == 1) {
            cout << 0 << "\n";
            continue;
        }
        
        if (Sx == Ex && Sy == Ey) {
            cout << 1 << "\n";
            continue;
        }
        
        vector<vector<int>> dist(N, vector<int>(M, -1));
        vector<vector<int>> ways(N, vector<int>(M, 0));
        
        queue<pair<int, int>> q;
        q.push({Sx, Sy});
        dist[Sx][Sy] = 0;
        ways[Sx][Sy] = 1;
        
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        
        while (!q.empty()) {
            pair<int, int> curr = q.front();
            q.pop();
            int x = curr.first;
            int y = curr.second;
            
            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                
                if (nx >= 0 && nx < N && ny >= 0 && ny < M && grid[nx][ny] == 0) {
                    if (dist[nx][ny] == -1) {
                        dist[nx][ny] = dist[x][y] + 1;
                        ways[nx][ny] = ways[x][y];
                        q.push({nx, ny});
                    } else if (dist[nx][ny] == dist[x][y] + 1) {
                        ways[nx][ny] = (ways[nx][ny] + ways[x][y]) % 100000;
                    }
                }
            }
        }
        
        cout << ways[Ex][Ey] % 100000 << "\n";
    }
    
    return 0;
}
