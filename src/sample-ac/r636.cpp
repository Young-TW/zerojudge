#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
using namespace std;

typedef long long ll;

ll mod;
vector<ll> fact, inv_fact;

ll power(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void precompute(int n) {
    fact.resize(n + 1);
    inv_fact.resize(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fact[i] = fact[i - 1] * i % mod;
    }
    inv_fact[n] = power(fact[n], mod - 2);
    for (int i = n - 1; i >= 0; --i) {
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % mod;
    }
}

ll comb(int a, int b) {
    if (a < 0 || b < 0 || a < b) return 0;
    return fact[a] * inv_fact[b] % mod * inv_fact[a - b] % mod;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, L;
    while (cin >> n >> L >> mod) {
        vector<int> c(n);
        for (int i = 0; i < n; ++i) {
            cin >> c[i];
        }

        int total = accumulate(c.begin(), c.end(), 0);
        if (total < L) {
            cout << "0\n";
            continue;
        }

        precompute(L);

        vector<ll> dp(L + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = L; j >= 0; --j) {
                for (int k = 1; k <= min(c[i], j); ++k) {
                    dp[j] = (dp[j] + dp[j - k] * comb(j, k)) % mod;
                }
            }
        }

        cout << dp[L] << '\n';
    }

    return 0;
}
