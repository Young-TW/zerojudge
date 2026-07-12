#include <cstdio>

char buf[1 << 20];
int p = 0;
int buf_size = 0;

inline char get_char() {
    if (p == buf_size) {
        buf_size = fread(buf, 1, sizeof(buf), stdin);
        p = 0;
        if (buf_size == 0) return EOF;
    }
    return buf[p++];
}

inline bool read_int(unsigned long long &x) {
    char c = get_char();
    while (c != EOF && (c < '0' || c > '9')) {
        c = get_char();
    }
    if (c == EOF) return false;
    x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = get_char();
    }
    return true;
}

int main() {
    unsigned long long n;
    while (read_int(n)) {
        unsigned long long ans = 0;
        unsigned long long sum = 0;
        for (unsigned long long i = 0; i < n; ++i) {
            unsigned long long x;
            if (!read_int(x)) break;
            ans += sum * x;
            sum += x;
        }
        printf("%llu\n", ans);
    }
    return 0;
}
