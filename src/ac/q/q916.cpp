#include <bits/stdc++.h>
using namespace std;

struct Dice {
    int top, bottom, north, south, east, west;
};

inline void roll(Dice &d, char dir) {
    int t = d.top, b = d.bottom, n = d.north,
        s = d.south, e = d.east, w = d.west;
    if (dir == 'N') {
        d.top = s;
        d.north = t;
        d.bottom = n;
        d.south = b;
    } else if (dir == 'S') {
        d.top = n;
        d.south = t;
        d.bottom = s;
        d.north = b;
    } else if (dir == 'E') {
        d.top = w;
        d.east = t;
        d.bottom = e;
        d.west = b;
    } else {                // dir == 'W'
        d.top = e;
        d.west = t;
        d.bottom = w;
        d.east = b;
    }
}

/* convert __int128 to decimal string */
string toString(__int128 v) {
    if (v == 0) return "0";
    bool neg = v < 0;
    if (neg) v = -v;
    string s;
    while (v > 0) {
        int digit = v % 10;
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
    long long N;
    while (cin >> N) {
        Dice d = {1, 6, 2, 5, 3, 4};
        __int128 ans = 0;
        for (long long i = 0; i < N; ++i) {
            char dir;
            long long x;
            cin >> dir >> x;

            // simulate four rolls to obtain the period
            Dice tmp = d;
            int period[4];
            long long sum4 = 0;
            for (int j = 0; j < 4; ++j) {
                roll(tmp, dir);
                period[j] = tmp.top;
                sum4 += period[j];
            }

            long long k = x / 4;
            int r = (int)(x % 4);

            ans += (__int128)k * sum4;
            for (int j = 0; j < r; ++j) ans += period[j];

            // update orientation: only the remaining r rolls matter
            for (int j = 0; j < r; ++j) roll(d, dir);
        }
        cout << toString(ans) << '\n';
    }
    return 0;
}
