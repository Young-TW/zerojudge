#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string sa, sn;
    while (cin >> sa >> sn) {
        if (sa == "0" && sn == "0") {
            cout << "All Over.\n";
            break;
        }

        long long a = stoll(sa);               // a always fits in long long

        // ----- special bases ------------------------------------------------
        if (a == 0) {
            cout << 0 << '\n';
            continue;
        }
        if (a == 1) {
            cout << 1 << '\n';
            continue;
        }
        if (a == -1) {
            string ns = sn;
            if (!ns.empty() && ns[0] == '-') ns.erase(ns.begin());
            char last = ns.back();
            bool odd = ((last - '0') % 2 == 1);
            cout << (odd ? -1 : 1) << '\n';
            continue;
        }

        // ----- other bases (|a| >= 2) ---------------------------------------
        bool negExp = false;
        string ns = sn;
        if (!ns.empty() && ns[0] == '-') {
            negExp = true;
            ns.erase(ns.begin());
        }

        // convert exponent to 64‑bit integer (it is guaranteed to be small)
        long long exp = 0;
        for (char c : ns) {
            exp = exp * 10 + (c - '0');
        }

        if (negExp) {               // |a| >= 2 and negative exponent → 0
            cout << 0 << '\n';
            continue;
        }

        // fast exponentiation using __int128
        __int128 result = 1;
        __int128 base = a;
        long long e = exp;
        while (e) {
            if (e & 1LL) result *= base;
            base *= base;
            e >>= 1LL;
        }
        cout << static_cast<long long>(result) << '\n';
    }
    return 0;
}
