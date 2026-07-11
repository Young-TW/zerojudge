#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_N = 1000000;
int dp[MAX_N + 1];

int get_cycle_length(long long n) {
    if (n == 1) return 1;
    if (n <= MAX_N && dp[n] != 0) return dp[n];
    
    long long next_n;
    if (n % 2 == 1) {
        next_n = 3 * n + 1;
    } else {
        next_n = n / 2;
    }
    
    int length = 1 + get_cycle_length(next_n);
    if (n <= MAX_N) {
        dp[n] = length;
    }
    return length;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int i, j;
    while (cin >> i >> j) {
        int start = min(i, j);
        int end = max(i, j);
        int max_len = 0;
        for (int k = start; k <= end; ++k) {
            if (dp[k] == 0) {
                get_cycle_length(k);
            }
            if (dp[k] > max_len) {
                max_len = dp[k];
            }
        }
        cout << i << " " << j << " " << max_len << "\n";
    }
    
    return 0;
}
