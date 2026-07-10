#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

const int LIM = 10000000; // 10^7, sqrt(10^14)
static bool isPrime[LIM + 1];

static inline long long readLL() {
    long long x = 0;
    int c = getchar();
    while (c != EOF && (c < '0' || c > '9')) c = getchar();
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return x;
}

int main() {
    memset(isPrime, true, sizeof(isPrime));
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; (long long)i * i <= LIM; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= LIM; j += i) {
                isPrime[j] = false;
            }
        }
    }

    long long n = readLL();
    static char outbuf[1 << 25];
    int opos = 0;
    for (long long i = 0; i < n; i++) {
        long long x = readLL();
        long long r = (long long) sqrtl((long double) x);
        while (r > 0 && r * r > x) r--;
        while ((r + 1) * (r + 1) <= x) r++;
        bool ok = false;
        if (r * r == x) {
            if (r <= LIM && isPrime[(int) r]) ok = true;
        }
        if (ok) {
            outbuf[opos++] = 'Y';
            outbuf[opos++] = 'E';
            outbuf[opos++] = 'S';
        } else {
            outbuf[opos++] = 'N';
            outbuf[opos++] = 'O';
        }
        outbuf[opos++] = '\n';
    }
    fwrite(outbuf, 1, opos, stdout);
    return 0;
}
