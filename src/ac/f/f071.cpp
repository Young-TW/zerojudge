#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long a, b, c;
    while (cin >> a >> b >> c) {
        long long x[5], p[5];
        for (int i = 0; i < 5; ++i) cin >> x[i];
        for (int i = 0; i < 5; ++i) cin >> p[i];

        long long ans = 0;          // prize before possible subtraction
        long long sub = 0;          // sum of prizes belonging to number c
        bool foundC = false;

        for (int i = 0; i < 5; ++i) {
            if (x[i] == a) ans += p[i];
            if (x[i] == b) ans += p[i];
            if (x[i] == c) {
                sub += p[i];
                foundC = true;
            }
        }

        if (foundC) {
            ans -= sub;
            if (ans < 0) ans = 0;
        } else {
            ans *= 2;
        }

        cout << ans << '\n';
    }
    return 0;
}
