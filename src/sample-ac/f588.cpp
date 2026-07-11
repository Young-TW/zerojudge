#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<long long> smallest_prime_factors;

void sieve(long long n) {
    smallest_prime_factors.resize(n + 1, 0);
    for (long long i = 2; i <= n; ++i) {
        if (smallest_prime_factors[i] == 0) {
            smallest_prime_factors[i] = i;
            for (long long j = i * i; j <= n; j += i) {
                if (smallest_prime_factors[j] == 0) {
                    smallest_prime_factors[j] = i;
                }
            }
        }
    }
}

long long euler_phi(long long x) {
    if (x == 1) return 1;
    long long res = x;
    long long temp = x;
    for (long long p = smallest_prime_factors[temp]; p != 0 && p * p <= temp; p = smallest_prime_factors[temp]) {
        res -= res / p;
        while (temp % p == 0) {
            temp /= p;
        }
    }
    if (temp > 1) {
        res -= res / temp;
    }
    return res;
}

long long sum_phi(long long n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (smallest_prime_factors.empty()) {
        sieve(1000000);
    }
    long long res = 0;
    for (long long i = 1; i <= n; ++i) {
        res += euler_phi(i);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    sieve(1000000);
    while (T--) {
        long long N;
        cin >> N;
        if (N <= 1000000) {
            long long ans = 0;
            for (long long i = 1; i <= N; ++i) {
                ans += euler_phi(i);
            }
            cout << ans << '\n';
        } else {
            long long ans = N * (N + 1) / 2;
            vector<long long> primes;
            vector<bool> is_prime(N + 1, true);
            is_prime[0] = is_prime[1] = false;
            for (long long i = 2; i <= N; ++i) {
                if (is_prime[i]) {
                    primes.push_back(i);
                    for (long long j = i * i; j <= N; j += i) {
                        is_prime[j] = false;
                    }
                }
            }
            for (long long p : primes) {
                ans -= sum_phi(N / p);
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
