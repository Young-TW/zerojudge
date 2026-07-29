// e293. 花開花落，雨初臨
// 自寫解 (self-written). For each big number (up to 5000 digits) find all
// primes <= 100 that divide it. Output ascending, space separated, else
// "Terrible Silence...".
//
// Key idea to avoid the "just barely TLE" brute force (25 mod-chains per
// number): group the 25 primes into 3 buckets whose products fit in 64-bit,
// then compute the big number mod each bucket product with ONE digit chain.
// (n mod M) mod p == n mod p for any p | M. This turns 25 digit-chains into 3.
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Group 1: 2..47 -> product = 614889782588491410 (< 2^63)
    static const int g1[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    const unsigned long long M1 = 614889782588491410ULL;
    // Group 2: 53..89 -> product = 38655288426304091
    static const int g2[] = {53, 59, 61, 67, 71, 73, 79, 83, 89};
    const unsigned long long M2 = 38655288426304091ULL;
    // Group 3: 97
    static const int g3[] = {97};
    const unsigned long long M3 = 97ULL;

    int n;
    if (!(cin >> n)) return 0;

    string s;
    string out;
    out.reserve(1 << 16);
    char buf[8];

    while (n-- > 0) {
        if (!(cin >> s)) break;
        unsigned long long r1 = 0, r2 = 0, r3 = 0;
        for (char c : s) {
            unsigned d = (unsigned)(c - '0');
            r1 = (r1 * 10 + d) % M1;
            r2 = (r2 * 10 + d) % M2;
            r3 = (r3 * 10 + d) % M3;
        }

        bool any = false;
        for (int p : g1) if (r1 % (unsigned)p == 0) {
            if (any) out += ' ';
            any = true;
            int len = snprintf(buf, sizeof(buf), "%d", p);
            out.append(buf, len);
        }
        for (int p : g2) if (r2 % (unsigned)p == 0) {
            if (any) out += ' ';
            any = true;
            int len = snprintf(buf, sizeof(buf), "%d", p);
            out.append(buf, len);
        }
        for (int p : g3) if (r3 % (unsigned)p == 0) {
            if (any) out += ' ';
            any = true;
            int len = snprintf(buf, sizeof(buf), "%d", p);
            out.append(buf, len);
        }

        if (!any) out += "Terrible Silence...";
        out += '\n';
    }

    cout << out;
    return 0;
}
