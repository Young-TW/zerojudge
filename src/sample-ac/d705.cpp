#include <iostream>

using namespace std;

unsigned long long power(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    base %= mod;
    unsigned long long res = 1;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

bool is_prime(unsigned long long n) {
    if (n < 2) return false;
    unsigned long long small_primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (unsigned long long p : small_primes) {
        if (n % p == 0) return n == p;
    }
    
    unsigned long long d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }
    
    unsigned long long bases[] = {2, 7, 61};
    for (unsigned long long a : bases) {
        unsigned long long x = power(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int i = 0; i < r - 1; i++) {
            x = (x * x) % n;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    unsigned long long n;
    while (cin >> n && n != 0) {
        if (is_prime(n)) {
            cout << "0\n";
        } else {
            cout << "1\n";
        }
    }
    
    return 0;
}
