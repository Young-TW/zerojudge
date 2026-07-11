#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M, K;
    while (cin >> N >> M >> K) {
        vector<vector<int>> dNeg(N, vector<int>(M, -1));
        vector<vector<int>> dPos(N, vector<int>(M, -1));
        
        queue<pair<int,int>> qNeg, qPos;
        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                int v;
                cin >> v;
                if (v == -1) {
                    dNeg[i][j] = 0;
                    qNeg.push(make_pair(i, j));
                } else if (v == 1) {
                    dPos[i][j] = 0;
                    qPos.push(make_pair(i, j));
                }
            }
        }
        
        // BFS for vampire (-1): diagonal moves
        const int dr_diag[] = {-1, -1, 1, 1};
        const int dc_diag[] = {-1, 1, -1, 1};
        while (!qNeg.empty()) {
            int r = qNeg.front().first;
            int c = qNeg.front().second;
            qNeg.pop();
            if (dNeg[r][c] >= K) continue;
            for (int d = 0; d < 4; d++) {
                int nr = r + dr_diag[d];
                int nc = c + dc_diag[d];
                if (nr >= 0 && nr < N && nc >= 0 && nc < M && dNeg[nr][nc] == -1) {
                    dNeg[nr][nc] = dNeg[r][c] + 1;
                    qNeg.push(make_pair(nr, nc));
                }
            }
        }
        
        // BFS for human (1): orthogonal moves
        const int dr_orth[] = {-1, 1, 0, 0};
        const int dc_orth[] = {0, 0, -1, 1};
        while (!qPos.empty()) {
            int r = qPos.front().first;
            int c = qPos.front().second;
            qPos.pop();
            if (dPos[r][c] >= K) continue;
            for (int d = 0; d < 4; d++) {
                int nr = r + dr_orth[d];
                int nc = c + dc_orth[d];
                if (nr >= 0 && nr < N && nc >= 0 && nc < M && dPos[nr][nc] == -1) {
                    dPos[nr][nc] = dPos[r][c] + 1;
                    qPos.push(make_pair(nr, nc));
                }
            }
        }
        
        // Output: human wins ties
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                int result = 0;
                if (dPos[i][j] != -1) {
                    result = 1;
                } else if (dNeg[i][j] != -1) {
                    result = -1;
                }
                if (j > 0) cout << ' ';
                cout << result;
            }
            cout << '\n';
        }
    }
    
    return 0;
}
