#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    unsigned long long m1, m2;
    const long double PI = acosl(-1.0L);
    const long double EPS = 1e-12L;

    while (cin >> m1 >> m2) {
        unsigned long long ans;
        if (m1 == m2) {
            ans = 3ULL;                     // special integer case
        } else {
            long double r = (long double)m1 / (long double)m2;
            long double theta = atanl(sqrtl(r));
            long double collisions = floorl(PI / theta + EPS);
            ans = (unsigned long long)collisions;
        }
        cout << ans << '\n';
    }
    return 0;
}
