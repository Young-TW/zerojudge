#include <cstdio>
#include <algorithm>

int a[1000000];

char in_buf[8192];
int in_pos = 0, in_len = 0;

inline int readChar() {
    if (in_pos == in_len) {
        in_len = fread(in_buf, 1, 8192, stdin);
        in_pos = 0;
        if (in_len <= 0) return -1;
    }
    return in_buf[in_pos++];
}

inline int readInt() {
    int c = readChar();
    while (c != '-' && (c < '0' || c > '9')) {
        if (c == -1) return -1;
        c = readChar();
    }
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = readChar();
    }
    return x;
}

char out_buf[8192];
int out_pos = 0;

inline void flush_out() {
    fwrite(out_buf, 1, out_pos, stdout);
    out_pos = 0;
}

inline void writeInt(int x) {
    if (out_pos > 8000) flush_out();
    if (x == 0) {
        out_buf[out_pos++] = '0';
        return;
    }
    char temp[12];
    int len = 0;
    while (x) {
        temp[len++] = x % 10 + '0';
        x /= 10;
    }
    while (len--) {
        out_buf[out_pos++] = temp[len];
    }
}

int main() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    
    int n = readInt();
    for (int i = 0; i < n; ++i) {
        a[i] = readInt();
    }
    std::sort(a, a + n);
    for (int i = 0; i < n; ++i) {
        writeInt(a[i]);
        out_buf[out_pos++] = (i == n - 1) ? '\n' : ' ';
        if (out_pos > 8000) flush_out();
    }
    flush_out();
    return 0;
}
