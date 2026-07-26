#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M) {
        vector<string> grid(N);
        for (int i = 0; i < N; ++i) {
            cin >> grid[i];
        }
        
        int start_r = -1, start_c = -1;
        for (int j = 1; j < M - 1; ++j) {
            if (grid[0][j] == '.') {
                start_r = 0; start_c = j;
            }
            if (grid[N - 1][j] == '.') {
                start_r = N - 1; start_c = j;
            }
        }
        for (int i = 1; i < N - 1; ++i) {
            if (grid[i][0] == '.') {
                start_r = i; start_c = 0;
            }
            if (grid[i][M - 1] == '.') {
                start_r = i; start_c = M - 1;
            }
        }
        
        int r = start_r, c = start_c;
        int pr = -1, pc = -1;
        
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        while (true) {
            int nr = -1, nc = -1;
            for (int d = 0; d < 4; ++d) {
                int tr = r + dr[d];
                int tc = c + dc[d];
                if (tr >= 0 && tr < N && tc >= 0 && tc < M && grid[tr][tc] == '.') {
                    if (tr == pr && tc == pc) continue;
                    nr = tr; nc = tc;
                    break;
                }
            }
            if (nr == -1) break;
            pr = r; pc = c;
            r = nr; c = nc;
        }
        
        cout << r + 1 << " " << c + 1 << "\n";
    }
    
    return 0;
}
