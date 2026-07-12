#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

using int64 = long long;

vector<int> primes;
unordered_map<int64, int64> phi_cache;

void generate_primes() {
    const int LIMIT = 50000;
    vector<bool> is_prime(LIMIT + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= LIMIT; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= LIMIT; j += i) {
                is_prime[j] = false;
            }
        }
    }
    for (int i = 2; i <= LIMIT; ++i) {
        if (is_prime[i]) primes.push_back(i);
    }
}

int64 phi(int64 n) {
    if (n == 1) return 1;
    auto it = phi_cache.find(n);
    if (it != phi_cache.end()) return it->second;
    int64 result = n;
    int64 temp = n;
    for (int p : primes) {
        if (1LL * p * p > temp) break;
        if (temp % p == 0) {
            while (temp % p == 0) temp /= p;
            result = result / p * (p - 1);
        }
    }
    if (temp > 1) {
        result = result / temp * (temp - 1);
    }
    phi_cache[n] = result;
    return result;
}

int64 modpow(int64 a, int64 e, int64 mod) {
    int64 res = 1 % mod;
    a %= mod;
    while (e > 0) {
        if (e & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        e >>= 1;
    }
    return res;
}

int64 solve(int64 x, int64 m) {
    if (m == 1) return 0;
    if (x == 1) return 1 % m;
    int64 ph = phi(m);
    int64 exp = solve(x, ph);
    return modpow(x, exp + ph, m);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    generate_primes();
    phi_cache.reserve(50000);
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int64 x, M;
        cin >> x >> M;
        cout << solve(x, M) << '\n';
    }
    return 0;
}
