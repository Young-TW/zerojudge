#include <iostream>
#include <vector>
#include <string>

using namespace std;
using ll = long long;

const int MOD = 1000000007;
const int MAXN = 1000000;

ll modpow(ll a, ll e) {
    ll res = 1;
    while (e) {
        if (e & 1) res = res * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Precompute factorials, inverse factorials, and modular inverses up to MAXN
    vector<int> fact(MAXN + 1), inv_fact(MAXN + 1), inv(MAXN + 1);
    fact[0] = 1;
    for (int i = 1; i <= MAXN; ++i) {
        fact[i] = (ll)fact[i - 1] * i % MOD;
    }
    inv_fact[MAXN] = modpow(fact[MAXN], MOD - 2);
    for (int i = MAXN; i >= 1; --i) {
        inv_fact[i - 1] = (ll)inv_fact[i] * i % MOD;
    }
    for (int i = 1; i <= MAXN; ++i) {
        inv[i] = (ll)fact[i - 1] * inv_fact[i] % MOD;
    }

    string s;
    while (cin >> s) {
        int n = s.size();
        vector<int> freq(26, 0);
        for (char ch : s) freq[ch - 'a']++;
        int A = freq[0];
        vector<int> others;
        for (int i = 1; i < 26; ++i) {
            if (freq[i] > 0) others.push_back(freq[i]);
        }
        int m = others.size();

        // Total permutations of the multiset
        ll total = fact[n];
        total = total * inv_fact[A] % MOD;
        for (int c : others) {
            total = total * inv_fact[c] % MOD;
        }

        // Inclusion–exclusion over subsets of other characters
        ll ans_sum = 0;
        int mask = 0;
        int current_sum = 0;
        int parity = 0;

        // Empty subset
        int denom = A + current_sum; // = A
        int term = inv[denom];
        if ((parity & 1) == 0) {
            ans_sum += term;
            if (ans_sum >= MOD) ans_sum -= MOD;
        } else {
            ans_sum -= term;
            if (ans_sum < 0) ans_sum += MOD;
        }

        int total_masks = 1 << m;
        for (int i = 1; i < total_masks; ++i) {
            int bit = __builtin_ctz(i);
            if (mask & (1 << bit)) {
                mask ^= (1 << bit);
                current_sum -= others[bit];
                --parity;
            } else {
                mask ^= (1 << bit);
                current_sum += others[bit];
                ++parity;
            }
            denom = A + current_sum;
            term = inv[denom];
            if ((parity & 1) == 0) {
                ans_sum += term;
                if (ans_sum >= MOD) ans_sum -= MOD;
            } else {
                ans_sum -= term;
                if (ans_sum < 0) ans_sum += MOD;
            }
        }

        ll answer = total * A % MOD;
        answer = answer * ans_sum % MOD;
        cout << answer << '\n';
    }
    return 0;
}
