#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using u128 = __int128;
using u64 = unsigned long long;

u64 mulmod(u64 a, u64 b, u64 mod) {
    return (u128)a * b % mod;
}

u64 powmod(u64 a, u64 e, u64 mod) {
    u64 res = 1;
    a %= mod;
    while (e > 0) {
        if (e & 1) res = mulmod(res, a, mod);
        a = mulmod(a, a, mod);
        e >>= 1;
    }
    return res;
}

u64 gcd(u64 a, u64 b) {
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

bool isPrime(u64 n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    u64 d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }
    for (u64 a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a) return true;
        if (n % a == 0) return false;
        u64 x = powmod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int i = 0; i < r - 1; ++i) {
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

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

u64 pollard(u64 n) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    while (true) {
        u64 x = rng() % (n - 2) + 2;
        u64 y = x;
        u64 c = rng() % (n - 1) + 1;
        u64 d = 1;
        while (d == 1) {
            x = (mulmod(x, x, n) + c) % n;
            y = (mulmod(y, y, n) + c) % n;
            y = (mulmod(y, y, n) + c) % n;
            d = gcd(x > y ? x - y : y - x, n);
        }
        if (d != n) return d;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    u64 N;
    while (std::cin >> N) {
        if (N < 4) {
            std::cout << "0 0\n";
            continue;
        }
        
        if (isPrime(N)) {
            std::cout << "0 0\n";
            continue;
        }
        
        u64 d = pollard(N);
        u64 other = N / d;
        
        if (isPrime(d) && isPrime(other)) {
            if (d > other) std::swap(d, other);
            std::cout << d << " " << other << "\n";
        } else {
            std::cout << "0 0\n";
        }
    }
    return 0;
}
