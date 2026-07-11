#include <iostream>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        int N, K;
        if (!(cin >> N >> K)) break;
        
        bool dp[100] = {false};
        dp[0] = true;
        
        for (int i = 0; i < N; ++i) {
            int x;
            cin >> x;
            bool next_dp[100] = {false};
            int rem = ((x % K) + K) % K;
            for (int r = 0; r < K; ++r) {
                if (dp[r]) {
                    next_dp[(r + rem) % K] = true;
                    next_dp[(r - rem + K) % K] = true;
                }
            }
            memcpy(dp, next_dp, sizeof(dp));
        }
        
        if (dp[0]) {
            cout << "Divisible\n";
        } else {
            cout << "Not divisible\n";
        }
    }
    
    return 0;
}
