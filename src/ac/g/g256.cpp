#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 1000000;
int dp[MAXN + 1];

int get_steps(long long n) {
    if (n == 1) return 0;
    if (n <= MAXN && dp[n] != -1) return dp[n];
    int steps;
    if (n % 2 == 0) {
        steps = get_steps(n / 2) + 1;
    } else {
        steps = get_steps(n * 3 + 1) + 1;
    }
    if (n <= MAXN) {
        dp[n] = steps;
    }
    return steps;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    memset(dp, -1, sizeof(dp));
    dp[1] = 0;
    
    long long n;
    while (cin >> n) {
        cout << get_steps(n) << "\n";
    }
    
    return 0;
}
