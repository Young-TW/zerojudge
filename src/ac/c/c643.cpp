#include <bits/stdc++.h>
using namespace std;

using u64 = unsigned long long;
using u128 = __uint128_t;

const u64 BASE = 1000000000000000000ULL;          // 1e18, divisible by 5
const int ODD[5] = {1, 3, 5, 7, 9};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    vector<int> query(T);
    int max_n = 0;
    for (int i = 0; i < T; ++i) {
        cin >> query[i];
        max_n = max(max_n, query[i]);
    }

    // answer digits, least‑significant first
    vector<char> ansLSB;
    ansLSB.reserve(max_n);

    // big integers, least‑significant block first
    vector<u64> P(1, 1);          // 2^0
    vector<u64> Q;               // A0 = 0
    int pMod5 = 1;                // P % 5

    for (int i = 0; i < max_n; ++i) {
        int qMod5 = Q.empty() ? 0 : int(Q[0] % 5ULL);
        int chosen = -1;
        for (int d : ODD) {
            if ( (qMod5 + d * pMod5) % 5 == 0 ) {
                chosen = d;
                break;
            }
        }
        if (chosen == -1) {               // should never happen
            ansLSB.push_back('X');        // placeholder
            continue;
        }
        ansLSB.push_back(char('0' + chosen));

        // ---- Q = (Q + chosen * P) / 5 ----
        // ensure Q has at least size of P
        if (Q.size() < P.size()) Q.resize(P.size(), 0ULL);

        // addition
        u64 carry = 0;
        for (size_t k = 0; k < P.size(); ++k) {
            u128 sum = (u128)Q[k] + (u128)P[k] * (u64)chosen + carry;
            Q[k] = (u64)(sum % BASE);
            carry = (u64)(sum / BASE);
        }
        size_t idx = P.size();
        while (carry) {
            if (idx >= Q.size()) Q.push_back(0);
            u128 sum = (u128)Q[idx] + carry;
            Q[idx] = (u64)(sum % BASE);
            carry = (u64)(sum / BASE);
            ++idx;
        }

        // division by 5 (exact)
        u64 rem = 0;
        for (int k = (int)Q.size() - 1; k >= 0; --k) {
            u128 cur = (u128)rem * BASE + Q[k];
            Q[k] = (u64)(cur / 5);
            rem   = (u64)(cur % 5);
        }
        while (!Q.empty() && Q.back() == 0) Q.pop_back();

        // ---- P = P * 2 ----
        carry = 0;
        for (size_t k = 0; k < P.size(); ++k) {
            u128 cur = (u128)P[k] * 2 + carry;
            P[k] = (u64)(cur % BASE);
            carry = (u64)(cur / BASE);
        }
        if (carry) P.push_back(carry);

        pMod5 = (pMod5 * 2) % 5;
    }

    // output answers
    for (int n : query) {
        string out;
        out.reserve(n);
        for (int i = 0; i < n; ++i) out.push_back(ansLSB[i]);
        reverse(out.begin(), out.end());
        cout << out << '\n';
    }
    return 0;
}
