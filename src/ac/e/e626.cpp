#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXP = 31623;
vector<int> primes;
bool is_prime[MAXP + 1];

void sieve() {
    fill(is_prime, is_prime + MAXP + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= MAXP; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * 2; j <= MAXP; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();
    long long n;
    while (cin >> n && n != -1) {
        long long temp = n;
        vector<pair<long long, int>> factors;
        for (int p : primes) {
            if ((long long)p * p > temp) break;
            if (temp % p == 0) {
                int cnt = 0;
                while (temp % p == 0) {
                    temp /= p;
                    cnt++;
                }
                factors.push_back({p, cnt});
            }
        }
        if (temp > 1) {
            factors.push_back({temp, 1});
        }
        
        vector<long long> divisors;
        divisors.push_back(1);
        for (auto& f : factors) {
            long long p = f.first;
            int cnt = f.second;
            int sz = divisors.size();
            long long mul = 1;
            for (int i = 1; i <= cnt; ++i) {
                mul *= p;
                for (int j = 0; j < sz; ++j) {
                    divisors.push_back(divisors[j] * mul);
                }
            }
        }
        
        long long best_k = 1;
        for (long long d : divisors) {
            if (d % 2 == 1) {
                if (d * d < 2 * n) {
                    if (d > best_k) {
                        best_k = d;
                    }
                }
            }
            if ((n / d) % 2 == 1) {
                if (2 * d * d < n) {
                    if (2 * d > best_k) {
                        best_k = 2 * d;
                    }
                }
            }
        }
        
        long long y = (2 * n) / best_k;
        long long a = (y - best_k + 1) / 2;
        long long b = a + best_k - 1;
        cout << n << " = " << a << " + ... + " << b << "\n";
    }
    return 0;
}
