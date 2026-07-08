#include <iostream>
#include <numeric>
#include <cstdlib>

int main() {
    long long a, b, c, d;
    char op;
    while (std::cin >> a >> b >> c >> d >> op) {
        long long p, q;
        switch (op) {
            case '+':
                p = a * d + c * b;
                q = b * d;
                break;
            case '-':
                p = a * d - c * b;
                q = b * d;
                break;
            case '*':
                p = a * c;
                q = b * d;
                break;
            default: // '/'
                p = a * d;
                q = b * c;
                break;
        }
        if (q < 0) { p = -p; q = -q; }
        long long g = std::gcd(std::llabs(p), q);
        if (g != 0) { p /= g; q /= g; }
        if (q == 1 || p == 0) {
            std::cout << p << '\n';
        } else {
            std::cout << p << '/' << q << '\n';
        }
    }
    return 0;
}
