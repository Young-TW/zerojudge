#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, r, c;
    bool first = true;
    while (cin >> n >> m >> r >> c) {
        vector<vector<int>> a(n, vector<int>(m));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin >> a[i][j];
        
        int ans = INT_MAX;
        
        for (int mask = 0; mask < (1 << n); mask++) {
            if (__builtin_popcount(mask) != r) continue;
            vector<int> rs;
            for (int i = 0; i < n; i++) 
                if (mask & (1 << i)) rs.push_back(i);
            
            vector<int> vcol(m, 0);
            for (int j = 0; j < m; j++) {
                for (int k = 0; k + 1 < (int)rs.size(); k++) {
                    vcol[j] += abs(a[rs[k]][j] - a[rs[k+1]][j]);
                }
            }
            
            vector<vector<int>> hcost(m, vector<int>(m, 0));
            for (int j = 0; j < m; j++) {
                for (int jj = j + 1; jj < m; jj++) {
                    int s = 0;
                    for (int k : rs) s += abs(a[k][j] - a[k][jj]);
                    hcost[j][jj] = s;
                }
            }
            
            vector<int> dp(m, INT_MAX);
            for (int j = 0; j < m; j++) dp[j] = vcol[j];
            
            for (int cnt = 1; cnt < c; cnt++) {
                vector<int> ndp(m, INT_MAX);
                for (int j = 0; j < m; j++) {
                    if (dp[j] == INT_MAX) continue;
                    for (int jj = j + 1; jj < m; jj++) {
                        int val = dp[j] + vcol[jj] + hcost[j][jj];
                        if (val < ndp[jj]) ndp[jj] = val;
                    }
                }
                dp = ndp;
            }
            for (int j = 0; j < m; j++) 
                if (dp[j] < ans) ans = dp[j];
        }
        
        if (!first) cout << "\n";
        cout << ans << "\n";
        first = false;
    }
    return 0;
}
