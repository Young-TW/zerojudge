#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        int total = n * n;
        vector<int> x(total + 1), y(total + 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int h;
                cin >> h;
                x[h] = i;
                y[h] = j;
            }
        }
        
        vector<long long> dp(total + 1, 0);
        for (int h = 2; h <= total; ++h) {
            for (int k = 1; k < h; ++k) {
                int dist = abs(x[h] - x[k]) + abs(y[h] - y[k]);
                long long val = dp[k] + (long long)dist * dist;
                if (val > dp[h]) {
                    dp[h] = val;
                }
            }
        }
        
        cout << dp[total] << "\n";
    }
    return 0;
}
