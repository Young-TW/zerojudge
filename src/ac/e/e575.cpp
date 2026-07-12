#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        int M, N, Q;
        cin >> M >> N >> Q;
        vector<string> grid(M);
        for (int i = 0; i < M; ++i) {
            cin >> grid[i];
        }
        cout << M << " " << N << " " << Q << "\n";
        for (int k = 0; k < Q; ++k) {
            int r, c;
            cin >> r >> c;
            int len = 1;
            while (true) {
                int half = len / 2;
                int new_half = half + 1;
                int r1 = r - new_half;
                int c1 = c - new_half;
                int r2 = r + new_half;
                int c2 = c + new_half;
                
                if (r1 < 0 || c1 < 0 || r2 >= M || c2 >= N) break;
                
                bool ok = true;
                char center = grid[r][c];
                for (int j = c1; j <= c2 && ok; ++j) {
                    if (grid[r1][j] != center || grid[r2][j] != center) {
                        ok = false;
                    }
                }
                for (int i = r1 + 1; i < r2 && ok; ++i) {
                    if (grid[i][c1] != center || grid[i][c2] != center) {
                        ok = false;
                    }
                }
                
                if (ok) {
                    len += 2;
                } else {
                    break;
                }
            }
            cout << len << "\n";
        }
    }
    
    return 0;
}
