#include <iostream>
#include <cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long s;
    while (cin >> s && s != 0) {
        long long n = (long long)((sqrt(1.0 + 8.0 * s) - 1.0) / 2.0);
        while (n * (n + 1) / 2 <= s) n++;
        long long x = n * (n + 1) / 2 - s;
        cout << x << " " << n << "\n";
    }
    return 0;
}
