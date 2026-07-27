#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double r;
    long long m;
    const long long VAL_POS = 1250;   // floor( (1/8) * 10000 )
    const long long VAL_ZERO = 0;     // floor( 0 * 10000 )
    const double EPS = 1e-12;
    while (cin >> r >> m) {
        long long ans = (fabs(r) < EPS) ? VAL_ZERO : VAL_POS;
        cout << (ans % m) << '\n';
    }
    return 0;
}
