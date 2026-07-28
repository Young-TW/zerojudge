#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long t;
    while (cin >> t) {
        long long c1 = t * 3;
        long long c2 = (t <= 300) ? 299 : 299 + (t - 300) * 3;
        long long c3 = (t <= 750) ? 699 : 699 + (t - 750) * 3;
        long long ans = min(c1, min(c2, c3));
        cout << ans << '\n';
    }
    return 0;
}
