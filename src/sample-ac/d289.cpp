#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long dp[8005] = {0};
    dp[0] = 1;
    int coeffs[] = {1, 13, 33, 43, 139, 169, 1309, 2597};
    
    for (int c : coeffs) {
        for (int i = c; i <= 8000; ++i) {
            dp[i] += dp[i - c];
        }
    }
    
    int I;
    while (cin >> I) {
        cout << dp[I] << "\n";
    }
    
    return 0;
}
