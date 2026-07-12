#include <iostream>

using namespace std;

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b) {
        unsigned long long temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    unsigned long long fib[10005];
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i < 10005; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    
    unsigned long long m, n;
    while (cin >> m >> n) {
        unsigned long long g = gcd(m, n);
        cout << fib[g] << "\n";
    }
    return 0;
}
