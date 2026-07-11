#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int H, W, Si, Sj, Z;
    while (cin >> H >> W >> Si >> Sj >> Z) {
        vector<vector<int>> P(H, vector<int>(W));
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                cin >> P[i][j];
            }
        }
        
        int target_color = P[Si - 1][Sj - 1];
        if (target_color != Z) {
            queue<pair<int, int>> q;
            q.push({Si - 1, Sj - 1});
            P[Si - 1][Sj - 1] = Z;
            
            int dr[] = {-1, 1, 0, 0};
            int dc[] = {0, 0, -1, 1};
            
            while (!q.empty()) {
                pair<int, int> curr = q.front();
                q.pop();
                int r = curr.first;
                int c = curr.second;
                
                for (int i = 0; i < 4; ++i) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if (nr >= 0 && nr < H && nc >= 0 && nc < W && P[nr][nc] == target_color) {
                        P[nr][nc] = Z;
                        q.push({nr, nc});
                    }
                }
            }
        }
        
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                cout << P[i][j];
                if (j == W - 1) {
                    cout << "\n";
                } else {
                    cout << " ";
                }
            }
        }
    }
    
    return 0;
}
