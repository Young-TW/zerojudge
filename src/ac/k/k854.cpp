#include <iostream>
#include <vector>
#include <cstdint>

const int MOD = 1000000007;
const int MAXN = 4000;               // enough for W+N (≤3500)

int64_t mod_pow(int64_t a, int64_t e) {
    int64_t r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int64_t fact[MAXN + 1];
int64_t invFact[MAXN + 1];

int64_t C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD;
}

int main() {
    // pre‑compute factorials
    fact[0] = 1;
    for (int i = 1; i <= MAXN; ++i) fact[i] = fact[i - 1] * i % MOD;
    invFact[MAXN] = mod_pow(fact[MAXN], MOD - 2);
    for (int i = MAXN; i >= 1; --i) invFact[i - 1] = invFact[i] * i % MOD;

    int W, N;
    while (std::cin >> W >> N) {
        std::vector<int> a(N);
        int sum = 0;
        for (int i = 0; i < N; ++i) {
            std::cin >> a[i];
            sum += a[i];
        }

        if (sum + (N - 1) > W) {
            std::cout << 0 << '\n';
            continue;
        }

        int free = W - sum - (N - 1);          // F ≥ 0
        int n = free + N;                      // total stars + separators
        int k = N;                             // choose positions of separators
        std::cout << C(n, k) << '\n';
    }
    return 0;
}
