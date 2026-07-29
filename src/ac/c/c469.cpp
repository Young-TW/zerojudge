// c469 - 方方國，方方地
// Self-written solution.
// Given area A, discard minimum land so remaining is a perfect square (integer).
// Answer = A - (floor(sqrt(A)))^2.
#include <bits/stdc++.h>
using namespace std;

static long long isqrt(long long a) {
    if (a < 0) return 0;
    long long r = (long long)sqrtl((long double)a);
    while (r > 0 && r * r > a) --r;
    while ((r + 1) * (r + 1) <= a) ++r;
    return r;
}

int main() {
    long long a;
    // Robust: process each integer found until EOF (handles single/multiple/trailing whitespace/\r).
    while (cin >> a) {
        long long r = isqrt(a);
        cout << (a - r * r) << "\n";
    }
    return 0;
}
