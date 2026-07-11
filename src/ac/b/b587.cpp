#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long dp[31];
    dp[0] = 1;
    dp[1] = 0;
    dp[2] = 3;
    for (int i = 3; i <= 30; ++i) {
        if (i % 2 != 0) {
            dp[i] = 0;
        } else {
            dp[i] = 4 * dp[i - 2] - dp[i - 4];
        }
    }
    
    int n;
    while (cin >> n && n != -1) {
        cout << dp[n] << "\n";
    }
    
    return 0;
}
