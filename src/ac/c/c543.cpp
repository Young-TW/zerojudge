#include <iostream>
#include <string>
#include <vector>

using namespace std;

const long long MOD = 1000000007;

vector<long long> fact = {1, 1};
vector<long long> inv_fact = {1, 1};

long long modpow(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

void ensure_fact(int n) {
    if (n < (int)fact.size()) return;
    int old_size = fact.size();
    fact.resize(n + 1);
    for (int i = old_size; i <= n; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    inv_fact.resize(n + 1);
    inv_fact[n] = modpow(fact[n], MOD - 2, MOD);
    for (int i = n - 1; i >= old_size; i--) {
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
    }
}

long long C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string N;
    while (cin >> N) {
        int L = (int)N.length();
        ensure_fact(L + 9);
        long long ans = (C(L + 8, 9) - 1 + MOD) % MOD;
        int prev = 0;
        for (int i = 0; i < L; i++) {
            int d = N[i] - '0';
            int start_c = (i == 0) ? 1 : prev;
            if (start_c < d) {
                int rem = L - 1 - i;
                long long sum = (C(rem + 10 - start_c, rem + 1) - C(rem + 10 - d, rem + 1) + MOD) % MOD;
                ans = (ans + sum) % MOD;
            }
            if (d < prev) {
                break;
            }
            prev = d;
            if (i == L - 1) {
                ans = (ans + 1) % MOD;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
