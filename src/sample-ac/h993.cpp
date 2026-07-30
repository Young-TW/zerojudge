#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int X;
    if (!(cin >> X)) return 0;          // X is not needed further
    string N;
    cin >> N;
    int L = (int)N.size();

    // 1. powers of 10
    vector<long long> pow10(L + 1);
    pow10[0] = 1;
    for (int i = 1; i <= L; ++i) {
        pow10[i] = (pow10[i - 1] * 10) % MOD;
    }

    // 2. prefix sums of powers: pref[i] = sum_{t=0}^{i} 10^t
    vector<long long> pref(L + 1);
    pref[0] = 1; // 10^0
    for (int i = 1; i <= L; ++i) {
        pref[i] = (pref[i - 1] + pow10[i]) % MOD;
    }

    // 3. suffix values modulo MOD
    vector<long long> suffix_mod(L + 1, 0); // suffix_mod[L] = 0
    for (int i = L - 1; i >= 0; --i) {
        long long digit = N[i] - '0';
        long long add = (digit * pow10[L - 1 - i]) % MOD;
        suffix_mod[i] = (add + suffix_mod[i + 1]) % MOD;
    }

    // 4. first position where digit != '1'
    int firstDiff = L; // default: all '1'
    for (int i = 0; i < L; ++i) {
        if (N[i] != '1') {
            firstDiff = i;
            break;
        }
    }

    long long answer = 0;

    for (int k = 1; k <= L; ++k) {
        // short(k)
        long long short_cnt = 0;
        if (L - 1 >= k) {
            short_cnt = pref[L - 1 - k];
        }

        // extra(k)
        long long extra = 0;
        if (k <= firstDiff) {                 // equality case
            extra = (suffix_mod[k] + 1) % MOD;
        } else {
            if (firstDiff < L && N[firstDiff] > '1') {
                extra = pow10[L - k];         // greater case
            } else {
                extra = 0;                     // smaller case
            }
        }

        long long cnt = (short_cnt + extra) % MOD;
        answer += cnt;
        if (answer >= MOD) answer -= MOD;
    }

    cout << answer % MOD << '\n';
    return 0;
}
