#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 1005;
char grid[MAXN][MAXN];
int fire_time[MAXN][MAXN];
int joe_time[MAXN][MAXN];

int q[MAXN * MAXN];

int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        int R, C;
        cin >> R >> C;
        
        int jr = -1, jc = -1;
        int fire_head = 0, fire_tail = 0;
        
        memset(fire_time, 0x3f, sizeof(fire_time));
        memset(joe_time, 0x3f, sizeof(joe_time));
        
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                cin >> grid[i][j];
                if (grid[i][j] == 'J') {
                    jr = i;
                    jc = j;
                } else if (grid[i][j] == 'F') {
                    fire_time[i][j] = 0;
                    q[fire_tail++] = i * C + j;
                }
            }
        }
        
        // BFS for fire
        while (fire_head < fire_tail) {
            int curr = q[fire_head++];
            int r = curr / C;
            int c = curr % C;
            
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                if (nr >= 0 && nr < R && nc >= 0 && nc < C && grid[nr][nc] != '#') {
                    if (fire_time[nr][nc] > fire_time[r][c] + 1) {
                        fire_time[nr][nc] = fire_time[r][c] + 1;
                        q[fire_tail++] = nr * C + nc;
                    }
                }
            }
        }
        
        // BFS for Joe
        int joe_head = 0, joe_tail = 0;
        joe_time[jr][jc] = 0;
        q[joe_tail++] = jr * C + jc;
        
        int ans = -1;
        
        if (jr == 0 || jr == R - 1 || jc == 0 || jc == C - 1) {
            ans = 1;
        } else {
            while (joe_head < joe_tail) {
                int curr = q[joe_head++];
                int r = curr / C;
                int c = curr % C;
                
                for (int i = 0; i < 4; ++i) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    
                    if (nr >= 0 && nr < R && nc >= 0 && nc < C && grid[nr][nc] != '#') {
                        if (joe_time[nr][nc] > joe_time[r][c] + 1) {
                            joe_time[nr][nc] = joe_time[r][c] + 1;
                            if (joe_time[nr][nc] < fire_time[nr][nc]) {
                                if (nr == 0 || nr == R - 1 || nc == 0 || nc == C - 1) {
                                    ans = joe_time[nr][nc] + 1;
                                    joe_head = joe_tail; // break outer loop
                                    break;
                                }
                                q[joe_tail++] = nr * C + nc;
                            }
                        }
                    }
                }
            }
        }
        
        if (ans == -1) {
            cout << "IMPOSSIBLE\n";
        } else {
            cout << ans << "\n";
        }
    }
    
    return 0;
}
