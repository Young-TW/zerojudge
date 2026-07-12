#include <iostream>

using namespace std;

long long gcd(long long a, long long b) {
    while (b) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, m;
    while (cin >> n >> m) {
        long long g = gcd(n, m);
        cout << (n * m - n + m + g) / 2 << "\n";
    }
    return 0;
}
