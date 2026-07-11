#include <cstdio>

inline bool readTwoLL(long long &a, long long &b) {
    int c;
    while ((c = getchar()) != EOF && (c < '0' || c > '9'));
    if (c == EOF) return false;
    a = c - '0';
    while ((c = getchar()) >= '0' && c <= '9') {
        a = a * 10 + (c - '0');
    }
    while ((c = getchar()) != EOF && (c < '0' || c > '9'));
    if (c == EOF) return false;
    b = c - '0';
    while ((c = getchar()) >= '0' && c <= '9') {
        b = b * 10 + (c - '0');
    }
    return true;
}

inline void writeLL(long long n) {
    if (n == 0) {
        putchar('0');
        return;
    }
    char buf[20];
    int idx = 0;
    while (n > 0) {
        buf[idx++] = n % 10 + '0';
        n /= 10;
    }
    while (idx > 0) {
        putchar(buf[--idx]);
    }
}

int main() {
    long long n, m;
    while (readTwoLL(n, m)) {
        if (n > m) {
            long long temp = n;
            n = m;
            m = temp;
        }
        long long S = (m - n) * n * (n + 1) / 2 + n * (n + 1) * (2 * n + 1) / 6;
        long long R_total = n * (n + 1) / 2 * m * (m + 1) / 2;
        long long R = R_total - S;
        
        writeLL(S);
        putchar(' ');
        writeLL(R);
        putchar('\n');
    }
    return 0;
}
