#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 1000005;
bool is_prime[MAXN];
vector<int> primes;

void sieve() {
    fill(is_prime, is_prime + MAXN, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i < MAXN; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j < MAXN; j += i) {
                is_prime[j] = false;
            }
        }
    }
    for (int i = 2; i < MAXN; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    int n;
    while (cin >> n && n != 0) {
        if (is_prime[n]) {
            cout << "1 " << n << "\n";
        } else if (n % 2 == 0) {
            // Goldbach's conjecture: every even integer > 2 is sum of two primes
            // To maximize product, we want primes close to n/2
            // Find the smallest prime p such that n-p is also prime
            // Actually, to maximize product p*(n-p), p should be close to n/2
            // We iterate from n/2 downwards to find the first pair
            int best_p = -1;
            for (int i = n / 2; i >= 2; --i) {
                if (is_prime[i] && is_prime[n - i]) {
                    best_p = i;
                    break;
                }
            }
            cout << "2 " << best_p << " " << (n - best_p) << "\n";
        } else {
            // n is odd and composite
            // Try to represent as sum of 2 primes: one must be 2, other n-2
            if (is_prime[n - 2]) {
                cout << "2 2 " << (n - 2) << "\n";
            } else {
                // Must be sum of 3 primes
                // One of them should be 3 (smallest odd prime) to leave even number
                // Then apply Goldbach on n-3
                int remaining = n - 3;
                int best_p = -1;
                for (int i = remaining / 2; i >= 2; --i) {
                    if (is_prime[i] && is_prime[remaining - i]) {
                        best_p = i;
                        break;
                    }
                }
                vector<int> result = {3, best_p, remaining - best_p};
                sort(result.begin(), result.end());
                cout << "3 " << result[0] << " " << result[1] << " " << result[2] << "\n";
            }
        }
    }

    return 0;
}
