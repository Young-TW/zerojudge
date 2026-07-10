#include <iostream>
using namespace std;

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    long long a, b;
    while (cin >> a >> b) {
        cout << gcd(a, b) << "\n";
    }
    return 0;
}
