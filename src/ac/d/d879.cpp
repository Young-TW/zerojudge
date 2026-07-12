#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    int case_num = 1;
    
    while (cin >> N && N) {
        int M = 2 * N;
        vector<int> x(M), y(M);
        string name;
        
        for (int i = 0; i < M; ++i) {
            cin >> name >> x[i] >> y[i];
        }
        
        vector<vector<double>> dist(M, vector<double>(M, 0.0));
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < M; ++j) {
                double dx = x[i] - x[j];
                double dy = y[i] - y[j];
                dist[i][j] = sqrt(dx * dx + dy * dy);
            }
        }
        
        int max_mask = 1 << M;
        vector<double> dp(max_mask, 1e18);
        dp[0] = 0.0;
        
        for (int mask = 0; mask < max_mask; ++mask) {
            if (dp[mask] == 1e18) continue;
            
            int first = -1;
            for (int i = 0; i < M; ++i) {
                if (!(mask & (1 << i))) {
                    first = i;
                    break;
                }
            }
            
            if (first == -1) continue;
            
            for (int j = first + 1; j < M; ++j) {
                if (!(mask & (1 << j))) {
                    int next_mask = mask | (1 << first) | (1 << j);
                    if (dp[next_mask] > dp[mask] + dist[first][j]) {
                        dp[next_mask] = dp[mask] + dist[first][j];
                    }
                }
            }
        }
        
        cout << "Case " << case_num++ << ": " << fixed << setprecision(2) << dp[max_mask - 1] << "\n";
    }
    
    return 0;
}
