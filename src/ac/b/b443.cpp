#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdint>
#include <random>
#include <chrono>
#include <cassert>
#include <utility>

using namespace std;

using u64 = unsigned long long;
using u128 = unsigned __int128;

inline u64 mul_mod(u64 a, u64 b, u64 mod) {
    return (u128)a * b % mod;
}

u64 pow_mod(u64 a, u64 e, u64 mod) {
    u64 res = 1 % mod;
    while (e) {
        if (e & 1) res = mul_mod(res, a, mod);
        a = mul_mod(a, a, mod);
        e >>= 1;
    }
    return res;
}

u64 gcd_u64(u64 a, u64 b) {
    while (b) {
        u64 t = a % b;
        a = b;
        b = t;
    }
    return a;
}

bool is_prime(u64 n) {
    if (n < 2) return false;
    static const u64 small_primes[] = {2,3,5,7,11,13,17,19,23,29,31,37};
    for (u64 p : small_primes) {
        if (n % p == 0) return n == p;
    }
    u64 d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }
    for (u64 a : small_primes) {
        if (a >= n) continue;
        u64 x = pow_mod(a, d, n);
        if (x == 1 || x == n-1) continue;
        bool composite = true;
        for (int r = 1; r < s; r++) {
            x = mul_mod(x, x, n);
            if (x == n-1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

u64 pollard_rho(u64 n) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    static std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    while (true) {
        u64 c = std::uniform_int_distribution<u64>(1, n-1)(rng);
        u64 x = std::uniform_int_distribution<u64>(0, n-1)(rng);
        u64 y = x;
        u64 d = 1;
        auto f = [&](u64 x) { return (mul_mod(x, x, n) + c) % n; };
        while (d == 1) {
            x = f(x);
            y = f(f(y));
            u64 diff = x > y ? x - y : y - x;
            d = gcd_u64(diff, n);
        }
        if (d != n) return d;
    }
}

void factor(u64 n, map<u64, int>& res) {
    if (n == 1) return;
    if (is_prime(n)) {
        res[n]++;
        return;
    }
    u64 d = pollard_rho(n);
    factor(d, res);
    factor(n/d, res);
}

struct Matrix {
    u64 a, b, c, d;
};

Matrix mul_mat(const Matrix& A, const Matrix& B, u64 mod) {
    Matrix C;
    C.a = (mul_mod(A.a, B.a, mod) + mul_mod(A.b, B.c, mod)) % mod;
    C.b = (mul_mod(A.a, B.b, mod) + mul_mod(A.b, B.d, mod)) % mod;
    C.c = (mul_mod(A.c, B.a, mod) + mul_mod(A.d, B.c, mod)) % mod;
    C.d = (mul_mod(A.c, B.b, mod) + mul_mod(A.d, B.d, mod)) % mod;
    return C;
}

Matrix pow_mat(Matrix base, u64 exp, u64 mod) {
    Matrix res = {1, 0, 0, 1};
    while (exp) {
        if (exp & 1) res = mul_mat(res, base, mod);
        base = mul_mat(base, base, mod);
        exp >>= 1;
    }
    return res;
}

bool is_identity(const Matrix& M) {
    return M.a == 1 && M.b == 0 && M.c == 0 && M.d == 1;
}

u64 get_pisano_prime(u64 p) {
    if (p == 2) return 3;
    if (p == 5) return 20;
    u64 candidate;
    u64 p_mod5 = p % 5;
    if (p_mod5 == 1 || p_mod5 == 4) candidate = p - 1;
    else candidate = 2 * (p + 1);
    map<u64, int> fac;
    factor(candidate, fac);
    u64 order = candidate;
    Matrix M = {1, 1, 1, 0};
    for (const auto& kv : fac) {
        u64 q = kv.first;
        int cnt = kv.second;
        for (int i = 0; i < cnt; i++) {
            if (order % q == 0) {
                u64 new_order = order / q;
                Matrix M_pow = pow_mat(M, new_order, p);
                if (is_identity(M_pow)) {
                    order = new_order;
                } else {
                    break;
                }
            }
        }
    }
    return order;
}

u64 pow_u64_exact(u64 base, int exp) {
    u128 res = 1;
    u128 b = base;
    while (exp) {
        if (exp & 1) res *= b;
        b *= b;
        exp >>= 1;
    }
    return (u64)res;
}

u64 compute_pisano_prime_power(u64 p, int e) {
    if (p == 2) {
        if (e == 1) return 3;
        if (e == 2) return 6;
        return 3 * (1ULL << (e-1));
    } else if (p == 5) {
        u64 pe = pow_u64_exact(5, e);
        return 4 * pe;
    } else {
        u64 pi_p = get_pisano_prime(p);
        u64 pe = pow_u64_exact(p, e-1);
        return (u64)((u128)pi_p * pe);
    }
}

u64 lcm_u64(u64 a, u64 b) {
    if (a == 0 || b == 0) return 0;
    u64 g = gcd_u64(a, b);
    u128 mul = (u128)a / g * b;
    return (u64)mul;
}

pair<u64, u64> fib_pair(u64 n, u64 mod) {
    if (n == 0) return {0, 1};
    auto p = fib_pair(n >> 1, mod);
    u64 a = p.first;
    u64 b = p.second;
    u64 two_b = (b << 1);
    if (two_b >= mod) two_b -= mod;
    u64 t = (two_b >= a) ? two_b - a : two_b + mod - a;
    u64 c = mul_mod(a, t, mod);
    u64 d = (mul_mod(a, a, mod) + mul_mod(b, b, mod)) % mod;
    if (n & 1) {
        return {d, (c + d) % mod};
    } else {
        return {c, d};
    }
}

u64 fib_mod(u64 n, u64 mod) {
    if (mod == 1) return 0;
    return fib_pair(n, mod).first;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        u64 n, m;
        cin >> n >> m;
        if (m == 1) {
            cout << 0 << '\n';
            continue;
        }
        map<u64, int> fac_m;
        factor(m, fac_m);
        u64 period = 1;
        for (const auto& kv : fac_m) {
            u64 p = kv.first;
            int e = kv.second;
            u64 pe_period = compute_pisano_prime_power(p, e);
            period = lcm_u64(period, pe_period);
        }
        u64 exp = pow_mod(2, n, period);
        u64 ans = fib_mod(exp, m);
        cout << ans << '\n';
    }
    return 0;
}
