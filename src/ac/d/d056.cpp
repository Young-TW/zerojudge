#include <cstdio>
#include <cstring>

const int BUF_SIZE = 1 << 20;
char buf[BUF_SIZE], *p1 = buf, *p2 = buf;

inline char gc() {
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, BUF_SIZE, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}

inline int readInt() {
    int x = 0;
    char c = gc();
    while (c < '0' || c > '9') {
        if (c == EOF) return -1;
        c = gc();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return x;
}

char out_buf[BUF_SIZE];
int out_len = 0;

inline void flush_out() {
    if (out_len) fwrite(out_buf, 1, out_len, stdout);
    out_len = 0;
}

inline void pc(char c) {
    if (out_len == BUF_SIZE) flush_out();
    out_buf[out_len++] = c;
}

int res[1000005];

int main() {
    int N = readInt();
    if (N == -1) return 0;
    
    for (int t = 0; t < N; ++t) {
        int M = readInt();
        if (M == -1) break;
        
        for (int i = 0; i < M; ++i) {
            int a = readInt();
            int b = readInt();
            res[i] = a + b;
        }
        
        for (int i = M - 1; i > 0; --i) {
            if (res[i] >= 10) {
                res[i - 1] += res[i] / 10;
                res[i] %= 10;
            }
        }
        
        for (int i = 0; i < M; ++i) {
            pc(res[i] + '0');
        }
        pc('\n');
        
        if (t < N - 1) {
            pc('\n');
        }
    }
    
    flush_out();
    return 0;
}
