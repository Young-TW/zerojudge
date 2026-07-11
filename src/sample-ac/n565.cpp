#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int R, C;
    while (cin >> R >> C) {
        int N;
        if (!(cin >> N)) break;
        
        vector<vector<long long>> diff(R + 2, vector<long long>(C + 2, 0));
        
        for (int i = 0; i < N; ++i) {
            int r1, c1, r2, c2;
            long long v;
            cin >> r1 >> c1 >> r2 >> c2 >> v;
            
            r1 = max(0, r1);
            c1 = max(0, c1);
            r2 = min(r2, R);
            c2 = min(c2, C);
            
            if (r1 >= r2 || c1 >= c2) continue;
            
            diff[r1][c1] += v;
            diff[r1][c2] -= v;
            diff[r2][c1] -= v;
            diff[r2][c2] += v;
        }
        
        string out;
        out.reserve(R * C * 4); 
        
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                if (i > 0) diff[i][j] += diff[i-1][j];
                if (j > 0) diff[i][j] += diff[i][j-1];
                if (i > 0 && j > 0) diff[i][j] -= diff[i-1][j-1];
                
                out += to_string(diff[i][j]);
                if (j == C - 1) {
                    out += "\n";
                } else {
                    out += " ";
                }
            }
        }
        cout << out;
    }
    
    return 0;
}
