#include <bits/stdc++.h>
using namespace std;

const int MOD = 100000007;                 // prime modulus
static uint32_t *fact;                     // factorial table

// fast exponentiation (a^e mod MOD)
static uint32_t modpow(uint32_t a, uint32_t e) {
    uint64_t res = 1;
    uint64_t base = a;
    while (e) {
        if (e & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        e >>= 1;
    }
    return static_cast<uint32_t>(res);
}

// C(a,b) for 0 <= b <= a < MOD
static uint32_t smallC(uint32_t a, uint32_t b) {
    if (b > a) return 0;
    uint32_t fa = fact[a];
    uint32_t fb = fact[b];
    uint32_t fab = fact[a - b];
    uint32_t inv_fb  = modpow(fb,  MOD - 2);
    uint32_t inv_fab = modpow(fab, MOD - 2);
    uint64_t ans = (uint64_t)fa * inv_fb % MOD;
    ans = ans * inv_fab % MOD;
    return static_cast<uint32_t>(ans);
}

// Lucas theorem
static uint32_t lucas(unsigned long long n, unsigned long long m) {
    if (m > n) return 0;
    uint64_t res = 1;
    while (n || m) {
        uint32_t ni = static_cast<uint32_t>(n % MOD);
        uint32_t mi = static_cast<uint32_t>(m % MOD);
        if (mi > ni) return 0;
        res = res * smallC(ni, mi) % MOD;
        n /= MOD;
        m /= MOD;
    }
    return static_cast<uint32_t>(res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // pre‑compute factorials modulo MOD
    fact = new uint32_t[MOD];
    fact[0] = 1;
    for (int i = 1; i < MOD; ++i)
        fact[i] = static_cast<uint32_t>((uint64_t)fact[i - 1] * i % MOD);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        unsigned long long n, m;
        cin >> n >> m;
        cout << lucas(n, m) << '\n';
    }
    return 0;
}
