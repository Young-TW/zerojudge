#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cstring>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    const int MAXN = 100;
    vector<long long> dp(MAXN + 1, 0);
    dp[0] = 1;
    for (int j = 1; j <= MAXN; ++j) {
        for (int i = j; i <= MAXN; ++i) {
            dp[i] += dp[i - j];
        }
    }
    
    int n;
    while (cin >> n) {
        cout << dp[n] << "\n";
    }
    
    return 0;
}
