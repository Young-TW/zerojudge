#include <iostream>
#include <map>
#include <random>

using namespace std;

typedef unsigned long long ull;

ull mulmod(ull a, ull b, ull m) {
    return (unsigned __int128)a * b % m;
}

ull powmod(ull a, ull b, ull m) {
    ull res = 1;
    a %= m;
    while (b > 0) {
        if (b & 1) res = mulmod(res, a, m);
        a = mulmod(a, a, m);
        b >>= 1;
    }
    return res;
}

ull gcd(ull a, ull b) {
    while (b) {
        ull t = a % b;
        a = b;
        b = t;
    }
    return a;
}

bool isPrime(ull n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    ull d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }
    for (ull a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a) return true;
        if (n % a == 0) return false;
        ull x = powmod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int i = 0; i < r - 1; i++) {
            x = mulmod(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

mt19937_64 rng(12345);

ull pollard(ull n) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    if (n % 5 == 0) return 5;
    
    ull x = rng() % (n - 2) + 2;
    ull y = x;
    ull c = rng() % (n - 1) + 1;
    ull d = 1;
    
    auto f = [&](ull x) {
        return (mulmod(x, x, n) + c) % n;
    };
    
    while (d == 1) {
        x = f(x);
        y = f(f(y));
        ull diff = (x > y) ? x - y : y - x;
        d = gcd(diff, n);
    }
    
    if (d == n) {
        return pollard(n);
    }
    return d;
}

void factorize(ull n, map<ull, int>& factors) {
    if (n == 1) return;
    if (isPrime(n)) {
        factors[n]++;
        return;
    }
    ull d = pollard(n);
    factorize(d, factors);
    factorize(n / d, factors);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ull N;
    while (cin >> N && N != 0) {
        while (N % 2 == 0) {
            N /= 2;
        }
        map<ull, int> factors;
        factorize(N, factors);
        ull ans = 1;
        for (auto& p : factors) {
            ans *= (p.second + 1);
        }
        if (ans > 0) ans--;
        cout << ans << "\n";
    }
    return 0;
}
