#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    int caseNo = 0;
    while (cin >> N >> M) {
        vector<string> grid(N);
        for (int i = 0; i < N; i++) cin >> grid[i];
        
        int dr[16] = {-3,-3,-2,-1,0,1,2,3,3,3,2,1,0,-1,-2,-3};
        int dc[16] = {0,1,2,3,3,3,2,1,0,-1,-2,-3,-3,-3,-2,-1};
        
        vector<string> out(N, string(M, '0'));
        
        for (int r = 3; r < N-3; r++) {
            for (int c = 3; c < M-3; c++) {
                int vals[32];
                for (int i = 0; i < 16; i++) {
                    vals[i] = grid[r+dr[i]][c+dc[i]] - '0';
                    vals[i+16] = vals[i];
                }
                int maxRun = 0, cur = 1;
                for (int i = 1; i < 32; i++) {
                    if (vals[i] == vals[i-1]) cur++;
                    else { maxRun = max(maxRun, cur); cur = 1; }
                }
                maxRun = max(maxRun, cur);
                if (maxRun >= 12) out[r][c] = '1';
            }
        }
        
        cout << "Case #" << ++caseNo << ":\n";
        for (int i = 0; i < N; i++) cout << out[i] << "\n";
    }
    return 0;
}
