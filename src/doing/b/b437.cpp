#include <iostream>
#include <map>
#include <random>
#include <chrono>
#include <utility>

using namespace std;

typedef unsigned long long ull;
typedef __int128 lll;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

ull mul_mod(ull a, ull b, ull mod) {
    return (ull)((lll)a * b % mod);
}

ull pow_mod(ull base, ull exp, ull mod) {
    ull res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = mul_mod(res, base, mod);
        base = mul_mod(base, base, mod);
        exp >>= 1;
    }
    return res;
}

ull my_gcd(ull a, ull b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

bool isPrime(ull n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    ull d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }
    for (ull a : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
        if (n == a) return true;
        if (n % a == 0) return false;
        ull x = pow_mod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int i = 0; i < r - 1; i++) {
            x = mul_mod(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

ull pollard_rho(ull n) {
    while (true) {
        ull x = rng() % (n - 2) + 2;
        ull y = x;
        ull c = rng() % (n - 1) + 1;
        ull d = 1;
        while (d == 1) {
            ull prod = 1;
            bool fail = false;
            for (int i = 0; i < 128; i++) {
                x = (mul_mod(x, x, n) + c) % n;
                y = (mul_mod(y, y, n) + c) % n;
                y = (mul_mod(y, y, n) + c) % n;
                ull diff = x > y ? x - y : y - x;
                if (diff == 0) {
                    fail = true;
                    break;
                }
                prod = mul_mod(prod, diff, n);
            }
            if (fail) break;
            d = my_gcd(prod, n);
            if (d != 1 && d != n) return d;
            if (d == n) break;
        }
    }
}

void factorize(ull n, map<ull, int>& factors) {
    if (n == 1) return;
    for (ull p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
        while (n % p == 0) {
            factors[p]++;
            n /= p;
        }
    }
    if (n == 1) return;
    if (isPrime(n)) {
        factors[n]++;
        return;
    }
    ull d = pollard_rho(n);
    factorize(d, factors);
    factorize(n / d, factors);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (cin >> T) {
        while (T--) {
            ull N;
            cin >> N;
            map<ull, int> factors;
            factorize(N, factors);
            
            cout << N << " =";
            bool first = true;
            for (auto& p : factors) {
                if (!first) {
                    cout << " *";
                }
                first = false;
                cout << " " << p.first;
                if (p.second > 1) {
                    cout << "^" << p.second;
                }
            }
            cout << "\n";
        }
    }
    return 0;
}
