#include <iostream>

using namespace std;

const int mod = 998244353;
const int B = 20;
const int M = 1 << B;
const int MAXN = 200000;

int fact[MAXN + 5];
int invfact[MAXN + 5];

long long power(long long base, long long exp, long long m) {
    long long res = 1;
    base %= m;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % m;
        base = (base * base) % m;
        exp /= 2;
    }
    return res;
}

void precompute(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (long long)fact[i - 1] * i % mod;
    }
    invfact[n] = power(fact[n], mod - 2, mod);
    for (int i = n - 1; i >= 0; i--) {
        invfact[i] = (long long)invfact[i + 1] * (i + 1) % mod;
    }
}

int C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return (long long)fact[n] * invfact[k] % mod * invfact[n - k] % mod;
}

int cnt[M];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precompute(MAXN);
    int n, k;
    while (cin >> n >> k) {
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            cnt[a]++;
        }
        
        for (int i = 0; i < B; i++) {
            for (int mask = 0; mask < M; mask++) {
                if (mask & (1 << i)) {
                    cnt[mask] += cnt[mask ^ (1 << i)];
                }
            }
        }
        
        long long ans = 0;
        for (int mask = 0; mask < M; mask++) {
            if (cnt[mask] >= k) {
                int c = C(cnt[mask], k);
                if (__builtin_popcount(mask) % 2 == 0) {
                    ans = (ans + c) % mod;
                } else {
                    ans = (ans - c + mod) % mod;
                }
            }
        }
        
        cout << ans << "\n";
        
        for (int mask = 0; mask < M; mask++) {
            cnt[mask] = 0;
        }
    }
    return 0;
}
