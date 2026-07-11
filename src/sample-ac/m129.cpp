#include <cstdio>

using namespace std;

inline int readInt() {
    int x = 0;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == EOF) return EOF;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return x;
}

int main() {
    int n;
    while ((n = readInt()) != EOF) {
        long long h = 0;
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            long long a = readInt();
            if (a >= h) {
                h = a;
            } else {
                long long diff = h - a;
                long long c = (diff + 1) / 2;
                ans += c;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
