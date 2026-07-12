#include <cstdio>
#include <cstring>
#include <algorithm>

unsigned char buf[1 << 20];
int p = 0;
int buf_size = 0;

inline int get_char() {
    if (p == buf_size) {
        buf_size = fread(buf, 1, sizeof(buf), stdin);
        p = 0;
        if (buf_size == 0) return EOF;
    }
    return buf[p++];
}

inline bool read_int(int &x) {
    int c = get_char();
    while (c != EOF && (c < '0' || c > '9') && c != '-') c = get_char();
    if (c == EOF) return false;
    bool neg = false;
    if (c == '-') {
        neg = true;
        c = get_char();
    }
    x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = get_char();
    }
    if (neg) x = -x;
    return true;
}

int a[2000005];
int w[2000005];

int main() {
    int t;
    while (read_int(t)) {
        while (t--) {
            int n, k;
            read_int(n);
            read_int(k);
            for (int i = 0; i < n; ++i) {
                read_int(a[i]);
            }
            for (int i = 0; i < n; ++i) {
                read_int(w[i]);
            }
            
            long long ans = 0;
            long long suffix_sum = 0;
            int j = n;
            for (int i = n - 1; i >= 0; --i) {
                while (j > 0 && a[j - 1] - a[i] > k) {
                    j--;
                    suffix_sum += w[j];
                }
                ans += (long long)w[i] * suffix_sum;
            }
            printf("%lld\n", ans);
        }
    }
    return 0;
}
