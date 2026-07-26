#include <cstdio>

long long gcd(long long a, long long b) {
    while (b) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    long long a, b;
    while (scanf("%lld %lld", &a, &b) == 2 && (a || b)) {
        printf("%lld\n", gcd(a, b));
    }
    return 0;
}
