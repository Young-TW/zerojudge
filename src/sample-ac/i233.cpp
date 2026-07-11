#include <cstdio>
#include <cstring>
#include <algorithm>

const int BUF_SIZE = 1 << 20;
char buf[BUF_SIZE], *p1 = buf, *p2 = buf;
inline char gc() {
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, BUF_SIZE, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}

template<typename T>
inline void read(T &x) {
    x = 0;
    char c = gc();
    bool neg = false;
    while (c != EOF && (c < '0' || c > '9')) {
        if (c == '-') neg = true;
        c = gc();
    }
    if (c == EOF) return;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    if (neg) x = -x;
}

char obuf[BUF_SIZE], *op = obuf;
inline void pc(char c) {
    if (op - obuf >= BUF_SIZE) {
        fwrite(obuf, 1, op - obuf, stdout);
        op = obuf;
    }
    *op++ = c;
}

inline void write(long long x) {
    if (x < 0) {
        pc('-');
        x = -x;
    }
    if (x == 0) {
        pc('0');
    } else {
        char temp[20];
        int len = 0;
        while (x) {
            temp[len++] = x % 10 + '0';
            x /= 10;
        }
        while (len--) pc(temp[len]);
    }
    pc('\n');
}

long long S1[1000005];
long long S2[1000005];

int main() {
    int n;
    read(n);
    
    for (int i = 1; i <= n; ++i) {
        int a;
        read(a);
        S1[i] = S1[i - 1] + a;
        S2[i] = S2[i - 1] + (long long)a * i;
    }
    
    int q;
    read(q);
    while (q--) {
        int L, R;
        read(L);
        read(R);
        long long ans = (long long)(R + 1) * (S1[R] - S1[L - 1]) - (S2[R] - S2[L - 1]);
        write(ans);
    }
    
    fwrite(obuf, 1, op - obuf, stdout);
    return 0;
}
