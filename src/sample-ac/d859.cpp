#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int dp[1005] = {0};
    int sum[1005] = {0};
    
    for (int i = 1; i <= 1000; ++i) {
        dp[i] = 1 + sum[i / 2];
        sum[i] = sum[i - 1] + dp[i];
    }
    
    int n;
    while (cin >> n) {
        cout << dp[n] << "\n";
    }
    
    return 0;
}
