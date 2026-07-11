#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

bool is_prime(int x) {
    if (x < 2) return false;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) return false;
    }
    return true;
}

int smallest_prime_factor(int x) {
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) return i;
    }
    return x; // x is prime (should not be called for prime in our logic)
}

uint64_t power(uint64_t base, int exp) {
    uint64_t result = 1;
    for (int i = 0; i < exp; ++i) {
        result *= base;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    uint64_t N;
    while (cin >> N) {
        vector<uint64_t> factors;
        bool squarefree = true;
        uint64_t n = N;
        
        // Factor out 2
        if (n % 2 == 0) {
            int e = 0;
            while (n % 2 == 0) {
                n /= 2;
                ++e;
            }
            if (e == 1) {
                factors.push_back(2);
            } else {
                squarefree = false;
                if (is_prime(e)) {
                    factors.push_back(power(2, e));
                } else {
                    int d = smallest_prime_factor(e);
                    int k = e / d;
                    uint64_t val = power(2, d);
                    for (int i = 0; i < k; ++i) factors.push_back(val);
                }
            }
        }
        
        // Factor out odd primes
        for (uint64_t p = 3; p * p <= n; p += 2) {
            if (n % p == 0) {
                int e = 0;
                while (n % p == 0) {
                    n /= p;
                    ++e;
                }
                if (e == 1) {
                    factors.push_back(p);
                } else {
                    squarefree = false;
                    if (is_prime(e)) {
                        factors.push_back(power(p, e));
                    } else {
                        int d = smallest_prime_factor(e);
                        int k = e / d;
                        uint64_t val = power(p, d);
                        for (int i = 0; i < k; ++i) factors.push_back(val);
                    }
                }
            }
        }
        
        // Remaining prime factor (exponent 1)
        if (n > 1) {
            factors.push_back(n);
        }
        
        if (squarefree) {
            cout << -1 << '\n';
        } else {
            sort(factors.begin(), factors.end());
            for (size_t i = 0; i < factors.size(); ++i) {
                if (i) cout << ' ';
                cout << factors[i];
            }
            cout << '\n';
        }
    }
    return 0;
}
