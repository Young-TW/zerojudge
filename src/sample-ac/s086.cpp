#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long a;
    while (cin >> a) {
        long double root = sqrtl((long double)a);
        long double ans = 4.0L * root;
        cout << fixed << setprecision(10) << ans << "\n";
    }
    
    return 0;
}
