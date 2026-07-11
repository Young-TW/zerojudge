#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<vector<int>> a(N, vector<int>(N));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> a[i][j];
            }
        }
        
        int min_sum = INT_MAX;
        for (int r1 = 0; r1 < N; ++r1) {
            vector<int> col_sum(N, 0);
            for (int r2 = r1; r2 < N; ++r2) {
                for (int i = 0; i < N; ++i) {
                    col_sum[i] += a[i][r2];
                }
                
                int cur = col_sum[0];
                int best = col_sum[0];
                for (int i = 1; i < N; ++i) {
                    cur = min(col_sum[i], cur + col_sum[i]);
                    best = min(best, cur);
                }
                min_sum = min(min_sum, best);
            }
        }
        cout << min_sum << "\n";
    }
    return 0;
}
