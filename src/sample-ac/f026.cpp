#include <cstdio>
#include <cmath>

using namespace std;

const int MAXN = 1005;
int a[MAXN];
int b[MAXN];

inline int readChar() {
    static char buf[1 << 16];
    static int pos = 0, len = 0;
    if (pos == len) {
        len = fread(buf, 1, 1 << 16, stdin);
        pos = 0;
        if (len == 0) return EOF;
    }
    return buf[pos++];
}

int readDecimal() {
    int c = readChar();
    while (c != '-' && (c < '0' || c > '9')) {
        if (c == EOF) return EOF;
        c = readChar();
    }
    int sign = 1;
    if (c == '-') {
        sign = -1;
        c = readChar();
    }
    int val = 0;
    while (c >= '0' && c <= '9') {
        val = val * 10 + (c - '0');
        c = readChar();
    }
    if (c == '.') {
        c = readChar();
        if (c >= '0' && c <= '9') {
            val = val * 10 + (c - '0');
            c = readChar();
            while (c >= '0' && c <= '9') {
                c = readChar();
            }
        } else {
            val = val * 10;
        }
    } else {
        val = val * 10;
    }
    return val * sign;
}

int readInt() {
    int c = readChar();
    while (c != '-' && (c < '0' || c > '9')) {
        if (c == EOF) return EOF;
        c = readChar();
    }
    int sign = 1;
    if (c == '-') {
        sign = -1;
        c = readChar();
    }
    int val = 0;
    while (c >= '0' && c <= '9') {
        val = val * 10 + (c - '0');
        c = readChar();
    }
    return val * sign;
}

int main() {
    int t = readInt();
    while (t--) {
        int n = readInt();
        int S_int = 0;
        for (int i = 0; i < n; ++i) {
            a[i] = readDecimal();
            S_int += a[i];
        }
        int B = 0;
        for (int i = 0; i < n; ++i) {
            b[i] = readInt();
            B += b[i];
        }
        
        long double L = 0;
        long double S = (long double)S_int / 10.0L;
        long double B_ld = (long double)B;
        for (int i = 0; i < n; ++i) {
            L += (long double)b[i] * log10l((long double)b[i] * S / B_ld);
        }
        
        long long y = (long long)floorl(L);
        long double frac = L - y;
        long double x = powl(10.0L, frac);
        
        long double rounded_x = roundl(x * 1000.0L) / 1000.0L;
        if (rounded_x >= 10.0L) {
            rounded_x /= 10.0L;
            y++;
        }
        
        printf("%.3fE%lld\n", (double)rounded_x, y);
    }
    return 0;
}
