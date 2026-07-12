#include <cstdio>

long long gcd(long long a, long long b);
void process(long long a, long long b);
void stop(long long a, long long b);

long long gcd_base(long long a, long long b) {
    return a;
}

long long gcd_rec(long long a, long long b) {
    return gcd(b, a % b);
}

long long gcd(long long a, long long b) {
    long long (*f[2])(long long, long long) = {gcd_rec, gcd_base};
    return f[b == 0](a, b);
}

void process(long long a, long long b) {
    printf("%lld\n", gcd(a, b));
    long long x, y;
    scanf("%lld %lld", &x, &y);
    void (*f[2])(long long, long long) = {process, stop};
    f[(x == 0) & (y == 0)](x, y);
}

void stop(long long a, long long b) {
}

int main() {
    long long a, b;
    scanf("%lld %lld", &a, &b);
    void (*f[2])(long long, long long) = {process, stop};
    f[(a == 0) & (b == 0)](a, b);
    return 0;
}
