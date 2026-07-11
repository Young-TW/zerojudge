#include <iostream>
#include <bitset>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    while (cin >> N >> M) {
        int total_sum = 0;
        bitset<10005> dp[51];
        dp[0].reset();
        dp[0][5000] = 1;
        
        for (int i = 0; i < N + M; ++i) {
            int v;
            cin >> v;
            total_sum += v;
            for (int j = N; j >= 1; --j) {
                if (v > 0) {
                    dp[j] |= (dp[j-1] << v);
                } else if (v < 0) {
                    dp[j] |= (dp[j-1] >> (-v));
                } else {
                    dp[j] |= dp[j-1];
                }
            }
        }
        
        long long max_val = -1e18, min_val = 1e18;
        for (int j = 0; j <= 10000; ++j) {
            if (dp[N][j]) {
                long long sum_x = j - 5000;
                long long sum_y = total_sum - sum_x;
                long long val = sum_x * sum_y;
                if (val > max_val) max_val = val;
                if (val < min_val) min_val = val;
            }
        }
        
        cout << max_val << " " << min_val << "\n";
    }
    
    return 0;
}
