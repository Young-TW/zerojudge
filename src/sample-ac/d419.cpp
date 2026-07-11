#include <iostream>

using namespace std;

const int MAXN = 1000000;
int dp[MAXN + 1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    for (int i = 2; i <= MAXN; i++) {
        if (dp[i] == 0) {
            for (int j = i; j <= MAXN; j += i) {
                if (dp[j] == 0) {
                    dp[j] = i;
                }
            }
        }
    }
    
    for (int i = 2; i <= MAXN; i++) {
        dp[i] = dp[i / dp[i]] + 1;
    }
    
    for (int i = 2; i <= MAXN; i++) {
        dp[i] += dp[i - 1];
    }
    
    int n;
    while (cin >> n) {
        cout << dp[n] << "\n";
    }
    
    return 0;
}
