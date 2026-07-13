#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    unsigned long long dp[40005] = {0};
    dp[0] = 1;
    for (int j = 1; j * j <= 40000; ++j) {
        int sq = j * j;
        for (int i = sq; i <= 40000; ++i) {
            dp[i] += dp[i - sq];
        }
    }
    
    int T;
    while (cin >> T) {
        while (T--) {
            int N;
            cin >> N;
            cout << dp[N] << "\n";
        }
    }
    
    return 0;
}
