#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    const int MAX_L = 1005;
    vector<bool> is_prime(MAX_L, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i < MAX_L; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j < MAX_L; j += i) {
                is_prime[j] = false;
            }
        }
    }

    vector<int> primes;
    for (int i = 2; i < MAX_L; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }

    vector<int> dp(MAX_L, 0);
    for (int L = 2; L < MAX_L; ++L) {
        int min_cost = 0;
        for (int p : primes) {
            if (p > L / 2) {
                break;
            }
            if (is_prime[L - p]) {
                int cost = L + dp[p] + dp[L - p];
                if (min_cost == 0 || cost < min_cost) {
                    min_cost = cost;
                }
            }
        }
        dp[L] = min_cost;
    }

    int L;
    while (cin >> L) {
        cout << dp[L] << "\n";
    }

    return 0;
}
