#include <iostream>
#include <vector>
#include <string>

using namespace std;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M) {
        vector<string> grid(N);
        int sx = -1, sy = -1;
        
        for (int i = 0; i < N; ++i) {
            cin >> grid[i];
            if (sx == -1) {
                for (int j = 0; j < M; ++j) {
                    if (grid[i][j] == 'S') {
                        sx = i;
                        sy = j;
                        break;
                    }
                }
            }
        }
        
        vector<int> qx(N * M);
        vector<int> qy(N * M);
        int head = 0, tail = 0;
        
        qx[tail] = sx;
        qy[tail] = sy;
        tail++;
        grid[sx][sy] = '#';
        
        bool found = false;
        
        while (head < tail) {
            int x = qx[head];
            int y = qy[head];
            head++;
            
            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                
                if (nx >= 0 && nx < N && ny >= 0 && ny < M && grid[nx][ny] != '#') {
                    if (grid[nx][ny] == 'T') {
                        found = true;
                        break;
                    }
                    qx[tail] = nx;
                    qy[tail] = ny;
                    tail++;
                    grid[nx][ny] = '#';
                }
            }
            if (found) break;
        }
        
        if (found) {
            cout << "mission passed respect+\n";
        } else {
            cout << "wasted\n";
        }
    }
    
    return 0;
}
