#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128  = __int128_t;

// greatest common divisor for __int128
static i128 igcd(i128 a, i128 b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        i128 t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// print a reduced fraction (num/den) where after reduction both fit in int64
static void print_fraction(i128 num, i128 den) {
    if (num == 0) {               // zero area
        cout << 0 << '\n';
        return;
    }
    i128 g = igcd(num, den);
    num /= g;
    den /= g;
    int64 n = static_cast<int64>(num);
    int64 d = static_cast<int64>(den);
    if (d == 1) {
        cout << n << '\n';
    } else {
        cout << n << " / " << d << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int64 k, a, b;
    while (cin >> k >> a >> b) {
        // ----- S1 : k * a * a / (2 * (a+b) * (2a+b))
        i128 num1 = (i128)k * a * a;
        i128 den1 = (i128)2 * (a + b) * (2 * a + b);
        print_fraction(num1, den1);

        // ----- S2 : k * a / (2 * (2a+b))
        i128 num2 = (i128)k * a;
        i128 den2 = (i128)2 * (2 * a + b);
        print_fraction(num2, den2);

        // ----- S3 : k * (a+b) / (2 * (2a+b))
        i128 num3 = (i128)k * (a + b);
        i128 den3 = (i128)2 * (2 * a + b);
        print_fraction(num3, den3);
    }
    return 0;
}
