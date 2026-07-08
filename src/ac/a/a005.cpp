#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        long long a, b, c, d;
        cin >> a >> b >> c >> d;
        long long e;
        if (b - a == c - b && c - b == d - c) {
            e = d + (d - c);
        } else {
            e = d * (d / c);
        }
        cout << a << " " << b << " " << c << " " << d << " " << e << "\n";
    }
    return 0;
}
