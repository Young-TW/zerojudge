#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;

// fast exponentiation modulo MOD
long long mod_pow(long long a, long long e) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

// binomial coefficients modulo MOD, using pre‑computed factorials
struct Binom {
    vector<long long> fact, invFact;
    Binom(int n = 0) { init(n); }
    void init(int n) {
        fact.assign(n + 1, 1);
        for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i % MOD;
        invFact.assign(n + 1, 1);
        invFact[n] = mod_pow(fact[n], MOD - 2);
        for (int i = n; i > 0; --i) invFact[i - 1] = invFact[i] * i % MOD;
    }
    long long C(int n, int k) const {
        if (k < 0 || k > n) return 0;
        return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    struct Query { int N; long long A, B, K; };
    vector<Query> qs;
    qs.reserve(T);
    int maxN = 0;
    for (int t = 0; t < T; ++t) {
        Query q;
        cin >> q.N >> q.A >> q.B >> q.K;
        qs.push_back(q);
        if (q.N > maxN) maxN = q.N;
    }
    
    Binom binom(maxN);
    
    for (const auto &q : qs) {
        int N = q.N;
        long long A = q.A, B = q.B, K = q.K;
        long long ans = 0;
        for (int i = 0; i <= N; ++i) {
            long long sumA = (long long)i * A;
            if (sumA > K) break;                 // A > 0
            long long rest = K - sumA;
            if (rest % B != 0) continue;
            long long j = rest / B;
            if (j < 0 || j > N) continue;
            long long add = binom.C(N, i) * binom.C(N, (int)j) % MOD;
            ans += add;
            if (ans >= MOD) ans -= MOD;
        }
        cout << ans << '\n';
    }
    return 0;
}
