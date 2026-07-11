#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M, Q;
    while (cin >> N >> M >> Q) {
        vector<vector<int>> grid(N, vector<int>(M));
        vector<pair<int, int>> pos(N * M + 1);
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cin >> grid[i][j];
                pos[grid[i][j]] = {i, j};
            }
        }
        
        for (int q = 0; q < Q; ++q) {
            int x;
            cin >> x;
            int r = pos[x].first;
            int c = pos[x].second;
            
            int up = grid[(r - 1 + N) % N][c];
            int down = grid[(r + 1) % N][c];
            int left = grid[r][(c - 1 + M) % M];
            int right = grid[r][(c + 1) % M];
            
            int ans[4] = {up, down, left, right};
            sort(ans, ans + 4);
            
            cout << ans[0] << " " << ans[1] << " " << ans[2] << " " << ans[3] << "\n";
        }
    }
    
    return 0;
}
