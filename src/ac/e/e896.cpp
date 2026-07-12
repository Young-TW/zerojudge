#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long dp[501] = {0};
    dp[0] = 1;
    for (int i = 1; i <= 500; ++i) {
        for (int j = 500; j >= i; --j) {
            dp[j] += dp[j - i];
        }
    }
    
    int L;
    while (cin >> L) {
        cout << dp[L] << "\n";
    }
    
    return 0;
}
