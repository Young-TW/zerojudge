#include <iostream>
#include <vector>

using namespace std;

const int MAXP = 46000;
int primes[MAXP];
bool is_comp[MAXP];
int prime_cnt = 0;

void sieve() {
    for (int i = 2; i < MAXP; ++i) {
        if (!is_comp[i]) {
            primes[prime_cnt++] = i;
        }
        for (int j = 0; j < prime_cnt && (long long)i * primes[j] < MAXP; ++j) {
            is_comp[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sieve();
    long long p;
    while (cin >> p) {
        long long n = p - 1;
        vector<long long> factors;
        for (int i = 0; i < prime_cnt; ++i) {
            long long pr = primes[i];
            if (pr * pr > n) break;
            if (n % pr == 0) {
                factors.push_back(pr);
                while (n % pr == 0) {
                    n /= pr;
                }
            }
        }
        if (n > 1) {
            factors.push_back(n);
        }
        
        for (long long g = 1; g < p; ++g) {
            bool ok = true;
            for (long long q : factors) {
                if (power(g, (p - 1) / q, p) == 1) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                cout << g << "\n";
                break;
            }
        }
    }
    return 0;
}
