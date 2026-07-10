#include <iostream>
using namespace std;

int main() {
    long long n, m;
    while (cin >> n >> m) {
        if (m < 0) m = 0;
        if (m > n) { cout << 0 << "\n"; continue; }
        long long k = (m < n - m) ? m : (n - m);
        long long res = 1;
        for (long long i = 1; i <= k; i++) {
            res *= (n - i + 1);
            res /= i;
        }
        cout << res << "\n";
    }
    return 0;
}
