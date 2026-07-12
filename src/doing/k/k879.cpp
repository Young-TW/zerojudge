#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int MAXN = 1005;
char grid[MAXN][MAXN];
char pre[MAXN][MAXN];
int vis[MAXN][MAXN];
int q[MAXN * MAXN][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    int timer = 0;
    while (cin >> n >> m) {
        timer++;
        int sx = -1, sy = -1, ex = -1, ey = -1;
        for (int i = 0; i < n; ++i) {
            cin >> grid[i];
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 'A') {
                    sx = i; sy = j;
                } else if (grid[i][j] == 'B') {
                    ex = i; ey = j;
                }
            }
        }
        
        int dx[] = {0, 0, 1, -1};
        int dy[] = {-1, 1, 0, 0};
        char dir[] = {'L', 'R', 'D', 'U'};
        
        int head = 0, tail = 0;
        q[tail][0] = sx; q[tail][1] = sy; tail++;
        vis[sx][sy] = timer;
        
        while (head < tail) {
            int x = q[head][0];
            int y = q[head][1];
            head++;
            
            if (x == ex && y == ey) break;
            
            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && vis[nx][ny] != timer && grid[nx][ny] != '#') {
                    vis[nx][ny] = timer;
                    pre[nx][ny] = dir[i];
                    q[tail][0] = nx; q[tail][1] = ny; tail++;
                }
            }
        }
        
        if (vis[ex][ey] != timer) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
            string path = "";
            int cx = ex, cy = ey;
            while (!(cx == sx && cy == sy)) {
                char d = pre[cx][cy];
                path += d;
                if (d == 'L') cy++;
                else if (d == 'R') cy--;
                else if (d == 'D') cx--;
                else if (d == 'U') cx++;
            }
            reverse(path.begin(), path.end());
            cout << path.length() << "\n";
            cout << path << "\n";
        }
    }
    return 0;
}
