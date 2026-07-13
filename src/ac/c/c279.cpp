#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> queries;
    int N;
    while (cin >> N) {
        queries.push_back(N);
    }
    if (queries.empty()) return 0;
    int maxN = *max_element(queries.begin(), queries.end());
    // sieve primes up to maxN
    vector<bool> is_prime(maxN + 1, true);
    if (maxN >= 0) is_prime[0] = false;
    if (maxN >= 1) is_prime[1] = false;
    for (int i = 2; i * i <= maxN; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= maxN; j += i) {
                is_prime[j] = false;
            }
        }
    }
    vector<int> primes;
    for (int i = 2; i <= maxN; ++i) {
        if (is_prime[i]) primes.push_back(i);
    }
    // DP: dp[i] = max number of distinct primes summing to i, -1 if impossible
    const int NEG = -1;
    vector<int> dp(maxN + 1, NEG);
    dp[0] = 0;
    for (int p : primes) {
        for (int i = maxN; i >= p; --i) {
            if (dp[i - p] != NEG) {
                if (dp[i - p] + 1 > dp[i]) {
                    dp[i] = dp[i - p] + 1;
                }
            }
        }
    }
    for (int n : queries) {
        cout << dp[n] << "\n";
    }
    return 0;
}
