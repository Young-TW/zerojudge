#include <bits/stdc++.h>
using namespace std;

// convert __int128 to decimal string
string toString(__int128 v) {
    if (v == 0) return "0";
    bool neg = false;
    if (v < 0) { neg = true; v = -v; }
    string s;
    while (v > 0) {
        int digit = int(v % 10);
        s.push_back('0' + digit);
        v /= 10;
    }
    if (neg) s.push_back('-');
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    char type;
    while (cin >> type) {
        if (type == 'A') {
            long long h_ll, x_ll, y_ll;
            cin >> h_ll >> x_ll >> y_ll;
            __int128 h = h_ll, x = x_ll, y = y_ll;
            __int128 t;
            if (h <= x) {
                t = 1;
            } else {
                __int128 gain = x - y;               // >0
                __int128 remaining = h - x;
                __int128 extra = (remaining + gain - 1) / gain; // ceil
                t = extra + 1;
            }
            cout << toString(t) << '\n';
        } else if (type == 'B') {
            long long t_ll, x_ll, y_ll;
            cin >> t_ll >> x_ll >> y_ll;
            __int128 t = t_ll, x = x_ll, y = y_ll;
            __int128 h;
            if (t == 1) {
                h = x;
            } else {
                __int128 gain = x - y;               // >0
                h = (t - 1) * gain + x;
            }
            cout << toString(h) << '\n';
        }
    }
    return 0;
}
