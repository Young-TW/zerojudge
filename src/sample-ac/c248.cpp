#include <cstdio>

const int MOD = 1000000007;
const int MAXN = 2097155;

int fact[MAXN];
int inv_fact[MAXN];

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}

void precompute() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = (int)((long long)fact[i - 1] * i % MOD);
    }
    inv_fact[MAXN - 1] = (int)power(fact[MAXN - 1], MOD - 2);
    for (int i = MAXN - 2; i >= 0; i--) {
        inv_fact[i] = (int)((long long)inv_fact[i + 1] * (i + 1) % MOD);
    }
}

int catalan(int n) {
    if (n == 0) return 1;
    return (int)((long long)fact[2 * n] * inv_fact[n] % MOD * inv_fact[n + 1] % MOD);
}

int main() {
    precompute();
    int T;
    if (scanf("%d", &T) == 1) {
        while (T--) {
            int N;
            if (scanf("%d", &N) == 1) {
                printf("%d\n", catalan(N));
            }
        }
    }
    return 0;
}
