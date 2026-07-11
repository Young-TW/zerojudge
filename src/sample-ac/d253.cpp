#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int coins[] = {1, 5, 10, 25, 50};
    long long dp[7490] = {1};
    
    for (int c = 0; c < 5; ++c) {
        for (int i = coins[c]; i <= 7489; ++i) {
            dp[i] += dp[i - coins[c]];
        }
    }
    
    int n;
    while (cin >> n) {
        cout << dp[n] << "\n";
    }
    
    return 0;
}
