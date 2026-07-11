#include <cstdio>
#include <algorithm>

using namespace std;

long long powmod(long long a, long long e, long long p) {
    long long r = 1;
    a %= p;
    if (a < 0) a += p;
    while (e > 0) {
        if (e & 1) r = (unsigned long long)r * a % p;
        a = (unsigned long long)a * a % p;
        e >>= 1;
    }
    return r;
}

long long tonelli_shanks(long long n, long long p) {
    if (n == 0) return 0;
    if (powmod(n, (p - 1) / 2, p) != 1) return -1;
    if (p % 4 == 3) {
        return powmod(n, (p + 1) / 4, p);
    }
    
    long long q = p - 1;
    long long s = 0;
    while (q % 2 == 0) {
        q /= 2;
        s++;
    }
    
    long long z = 2;
    while (powmod(z, (p - 1) / 2, p) != p - 1) {
        z++;
    }
    
    long long M = s;
    long long c = powmod(z, q, p);
    long long t = powmod(n, q, p);
    long long R = powmod(n, (q + 1) / 2, p);
    
    while (true) {
        if (t == 1) return R;
        
        long long i = 0;
        long long tmp = t;
        while (tmp != 1) {
            tmp = (unsigned long long)tmp * tmp % p;
            i++;
        }
        
        long long b = powmod(c, 1LL << (M - i - 1), p);
        M = i;
        c = (unsigned long long)b * b % p;
        t = (unsigned long long)t * c % p;
        R = (unsigned long long)R * b % p;
    }
}

int main() {
    long long p, a, b, c;
    while (scanf("%lld %lld %lld %lld", &p, &a, &b, &c) == 4) {
        if (p == 2) {
            if (b == 0) {
                if (c == 0) printf("0\n");
                else printf("1\n");
            } else {
                if (c == 0) printf("0 1\n");
                else printf("no solution\n");
            }
            continue;
        }
        
        long long delta = (b * b - (4 * a % p) * c % p) % p;
        delta = (delta + p) % p;
        
        if (delta == 0) {
            long long inv2a = powmod((2 * a) % p, p - 2, p);
            long long x = ((-b % p) + p) % p;
            x = x * inv2a % p;
            printf("%lld\n", x);
        } else {
            long long S = tonelli_shanks(delta, p);
            if (S == -1) {
                printf("no solution\n");
            } else {
                long long inv2a = powmod((2 * a) % p, p - 2, p);
                long long x1 = (((-b + S) % p + p) % p) * inv2a % p;
                long long x2 = (((-b - S) % p + p) % p) * inv2a % p;
                if (x1 > x2) swap(x1, x2);
                printf("%lld %lld\n", x1, x2);
            }
        }
    }
    return 0;
}
