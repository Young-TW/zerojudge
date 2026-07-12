#include <iostream>

using namespace std;

long long power(long long a, long long n) {
    long long res = 1;
    long long base = a;
    while (n > 0) {
        if (n & 1) res *= base;
        base *= base;
        n >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long a, n;
    while (cin >> a >> n) {
        if (a == 0 && n == 0) {
            cout << "All Over." << "\n";
            break;
        }
        if (n < 0) {
            if (a == 1) {
                cout << 1 << "\n";
            } else if (a == -1) {
                cout << (n % 2 == 0 ? 1 : -1) << "\n";
            } else {
                cout << 0 << "\n";
            }
        } else {
            cout << power(a, n) << "\n";
        }
    }
    return 0;
}
