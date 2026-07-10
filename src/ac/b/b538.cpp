#include <iostream>
#include <cstdlib>

// 手寫 gcd：ZeroJudge 編譯器較舊，無 C++17 的 std::gcd
static long long igcd(long long a, long long b) {
    while (b) { long long t = a % b; a = b; b = t; }
    return a < 0 ? -a : a;
}

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
        long long g = igcd(std::llabs(p), q);
        if (g != 0) { p /= g; q /= g; }
        if (q == 1 || p == 0) {
            std::cout << p << '\n';
        } else {
            std::cout << p << '/' << q << '\n';
        }
    }
    return 0;
}
