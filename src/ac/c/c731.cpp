#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int MOD = 12345;
    long long n;
    while (cin >> n) {
        int a = 1, b = 3;
        if (n == 0) { cout << a << "\n"; continue; }
        if (n == 1) { cout << b << "\n"; continue; }
        for (long long i = 2; i <= n; i++) {
            int c = (2 * b + a) % MOD;
            a = b;
            b = c;
        }
        cout << b << "\n";
    }
    return 0;
}
