#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const double sqrt3 = sqrt(3.0);
    const double pi = acos(-1.0);

    double a;
    cout << fixed << setprecision(3);
    while (cin >> a) {
        double s = a * a;
        double striped   = (1.0 - sqrt3 + pi / 3.0) * s;
        double dotted    = (-4.0 + 2.0 * sqrt3 + pi / 3.0) * s;
        double remaining = (4.0 - sqrt3 - 2.0 * pi / 3.0) * s;
        cout << striped << ' ' << dotted << ' ' << remaining << '\n';
    }
    return 0;
}
