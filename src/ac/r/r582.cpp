#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long ncows, ncars, nshow;
    while (cin >> ncows >> ncars >> nshow) {
        long long total = ncows + ncars;
        long long numerator = ncars * (total - 1);
        long long denominator = total * (total - 1 - nshow);
        double ans = (double)numerator / (double)denominator;
        cout << fixed << setprecision(5) << ans << "\n";
    }
    
    return 0;
}
