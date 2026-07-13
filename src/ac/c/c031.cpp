#include <iostream>
#include <cmath>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n) {
        long long k = (sqrt(1.0 + 8.0 * n) - 1.0) / 2.0;
        if (k * (k + 1) / 2 < n) {
            k++;
        }
        long long m = n - k * (k - 1) / 2;
        long long num, den;
        if (k % 2 == 1) {
            num = k - m + 1;
            den = m;
        } else {
            num = m;
            den = k - m + 1;
        }
        cout << "TERM " << n << " IS " << num << "/" << den << "\n";
    }
    
    return 0;
}
