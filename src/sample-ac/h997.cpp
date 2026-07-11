#include <iostream>

using namespace std;

const int MOD = 1000000007;
const int MAXN = 2005;

int S[MAXN][MAXN];
int P[MAXN][MAXN];
long long fact[MAXN * 2];
long long invfact[MAXN * 2];

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

void precompute() {
    S[0][0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        for (int j = 1; j <= i; ++j) {
            S[i][j] = ((long long)j * S[i-1][j] + S[i-1][j-1]) % MOD;
        }
    }

    P[0][0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        for (int j = 1; j <= i; ++j) {
            int val = P[i-1][j-1];
            if (i >= j) {
                val = (val + P[i-j][j]) % MOD;
            }
            P[i][j] = val;
        }
    }

    fact[0] = 1;
    for (int i = 1; i < MAXN * 2; ++i) {
        fact[i] = (fact[i-1] * i) % MOD;
    }
    invfact[MAXN * 2 - 1] = power(fact[MAXN * 2 - 1], MOD - 2);
    for (int i = MAXN * 2 - 2; i >= 0; --i) {
        invfact[i] = (invfact[i+1] * (i+1)) % MOD;
    }
}

long long C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * invfact[k] % MOD * invfact[n-k] % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precompute();
    int n, m, t;
    while (cin >> n >> m >> t) {
        if (t == 1) {
            for (int x = 1; x <= m; ++x) {
                cout << power(x, n) << (x == m ? "" : " ");
            }
        } else if (t == 2) {
            for (int x = 1; x <= m; ++x) {
                cout << C(n + x - 1, x - 1) << (x == m ? "" : " ");
            }
        } else if (t == 3) {
            long long sum = 0;
            for (int x = 1; x <= m; ++x) {
                if (x <= n) sum = (sum + S[n][x]) % MOD;
                cout << sum << (x == m ? "" : " ");
            }
        } else if (t == 4) {
            long long sum = 0;
            for (int x = 1; x <= m; ++x) {
                if (x <= n) sum = (sum + P[n][x]) % MOD;
                cout << sum << (x == m ? "" : " ");
            }
        }
        cout << "\n";
    }
    return 0;
}
