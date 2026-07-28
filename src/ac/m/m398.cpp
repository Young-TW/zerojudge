#include <bits/stdc++.h>
using namespace std;

// convert __int128 to decimal string
string toString(__int128 x) {
    if (x == 0) return "0";
    bool neg = false;
    if (x < 0) { neg = true; x = -x; }
    string s;
    while (x > 0) {
        int digit = int(x % 10);
        s.push_back('0' + digit);
        x /= 10;
    }
    if (neg) s.push_back('-');
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long a, b, c;
    while (cin >> a >> b >> c) {
        __int128 sum1 = 0, sum2 = 0, sum3 = 0;
        for (long long i = 0, x; i < a; ++i) {
            cin >> x;
            sum1 += (__int128)x;
        }
        for (long long i = 0, x; i < b; ++i) {
            cin >> x;
            sum2 += (__int128)x;
        }
        for (long long i = 0, x; i < c; ++i) {
            cin >> x;
            sum3 += (__int128)x;
        }

        __int128 t1 = 0, t2 = 0, t3 = 0;
        if (a > 0) t1 = sum1 * 3 + (__int128)(a - 1) * 2;
        if (b > 0) t2 = sum2 * 3 + (__int128)(b - 1) * 2;
        if (c > 0) t3 = sum3 * 3 + (__int128)(c - 1) * 2;

        int idx = 1;
        __int128 best = t1;
        if (t2 < best) { best = t2; idx = 2; }
        else if (t2 == best && idx > 2) { idx = 2; } // tie → smaller index
        if (t3 < best) { best = t3; idx = 3; }
        else if (t3 == best && idx > 3) { idx = 3; }

        cout << idx << ' ' << toString(best) << '\n';
    }
    return 0;
}
