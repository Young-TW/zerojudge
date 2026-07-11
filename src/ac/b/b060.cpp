#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m;
    while (cin >> m) {
        vector<vector<int>> D(m + 1, vector<int>(m + 1));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= m; ++j) {
                cin >> D[i][j];
            }
        }
        
        string line;
        getline(cin, line); // consume end of line after the matrix
        getline(cin, line); // read the request line
        
        stringstream ss(line);
        vector<int> req;
        int x;
        while (ss >> x) {
            req.push_back(x);
        }
        int n = req.size();
        if (n == 0) {
            cout << 0 << '\n';
            continue;
        }
        
        const int INF = 1e9;
        vector<vector<int>> dp_cur(m + 1, vector<int>(m + 1, INF));
        vector<vector<int>> dp_next(m + 1, vector<int>(m + 1, INF));
        
        // Initialize for the first request
        int r1 = req[0];
        // Driver starting at 1 serves
        int cost = D[1][r1];
        int i = 2, j = 3;
        if (i > j) swap(i, j);
        dp_cur[i][j] = min(dp_cur[i][j], cost);
        // Driver starting at 2 serves
        cost = D[2][r1];
        i = 1; j = 3;
        if (i > j) swap(i, j);
        dp_cur[i][j] = min(dp_cur[i][j], cost);
        // Driver starting at 3 serves
        cost = D[3][r1];
        i = 1; j = 2;
        if (i > j) swap(i, j);
        dp_cur[i][j] = min(dp_cur[i][j], cost);
        
        // Process subsequent requests
        for (int k = 0; k < n - 1; ++k) {
            // Reset dp_next to INF
            for (int i = 1; i <= m; ++i) {
                fill(dp_next[i].begin() + 1, dp_next[i].end(), INF);
            }
            
            int cur_active = req[k];
            int next_req = req[k + 1];
            
            for (int i = 1; i <= m; ++i) {
                for (int j = i; j <= m; ++j) {
                    int cur_cost = dp_cur[i][j];
                    if (cur_cost == INF) continue;
                    
                    // Option 1: the active driver serves the next request
                    int nc = cur_cost + D[cur_active][next_req];
                    if (nc < dp_next[i][j]) dp_next[i][j] = nc;
                    
                    // Option 2: the idle driver at i serves the next request
                    nc = cur_cost + D[i][next_req];
                    int ni = cur_active, nj = j;
                    if (ni > nj) swap(ni, nj);
                    if (nc < dp_next[ni][nj]) dp_next[ni][nj] = nc;
                    
                    // Option 3: the idle driver at j serves the next request
                    nc = cur_cost + D[j][next_req];
                    ni = i; nj = cur_active;
                    if (ni > nj) swap(ni, nj);
                    if (nc < dp_next[ni][nj]) dp_next[ni][nj] = nc;
                }
            }
            swap(dp_cur, dp_next);
        }
        
        int ans = INF;
        for (int i = 1; i <= m; ++i) {
            for (int j = i; j <= m; ++j) {
                ans = min(ans, dp_cur[i][j]);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
