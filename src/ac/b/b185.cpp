#include <iostream>
#include <string>
#include <algorithm>
#include <climits>
#include <cstring>
using namespace std;

int main() {
    int n, m;
    while (cin >> n >> m) {
        string grid[6];
        for (int i = 0; i < n; i++) {
            cin >> grid[i];
        }
        
        int init[6][6];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                init[i][j] = (grid[i][j] == 'O') ? 1 : 0;
        
        int best = INT_MAX;
        
        for (int mask = 0; mask < (1 << m); mask++) {
            int state[6][6];
            memcpy(state, init, sizeof(state));
            
            int presses = 0;
            
            // Apply first row presses
            for (int j = 0; j < m; j++) {
                if (mask & (1 << j)) {
                    presses++;
                    state[0][j] ^= 1;
                    if (j > 0) state[0][j-1] ^= 1;
                    if (j < m-1) state[0][j+1] ^= 1;
                    if (n > 1) state[1][j] ^= 1;
                }
            }
            
            // Chase: press row i to fix row i-1
            for (int i = 1; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (state[i-1][j] == 1) {
                        presses++;
                        state[i][j] ^= 1;
                        if (j > 0) state[i][j-1] ^= 1;
                        if (j < m-1) state[i][j+1] ^= 1;
                        state[i-1][j] ^= 1;
                        if (i < n-1) state[i+1][j] ^= 1;
                    }
                }
            }
            
            bool ok = true;
            for (int i = 0; i < n && ok; i++)
                for (int j = 0; j < m && ok; j++)
                    if (state[i][j] == 1) ok = false;
            
            if (ok) best = min(best, presses);
        }
        
        if (best == INT_MAX) {
            cout << "Can not" << endl;
        } else {
            cout << "Minimum Steps :" << best << endl;
        }
    }
    return 0;
}
