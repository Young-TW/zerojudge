#include <cstdio>

char buf[1 << 20];
int buf_pos = 0;
int buf_len = 0;

inline int read_char() {
    if (buf_pos == buf_len) {
        buf_len = fread(buf, 1, sizeof(buf), stdin);
        buf_pos = 0;
        if (buf_len == 0) return EOF;
    }
    return buf[buf_pos++];
}

inline bool read_int(int &x) {
    int c = read_char();
    while (c != EOF && (c < '0' || c > '9')) {
        c = read_char();
    }
    if (c == EOF) return false;
    x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = read_char();
    }
    if (c != EOF) {
        buf_pos--;
    }
    return true;
}

inline int read_alpha() {
    int c = read_char();
    while (c != EOF && !((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
        c = read_char();
    }
    return c;
}

int main() {
    int N;
    while (read_int(N)) {
        char ans[5001];
        
        int c = read_alpha();
        if (c == EOF) break;
        
        ans[0] = c;
        for (int j = 1; j < N; ++j) {
            read_alpha();
        }
        
        for (int i = 1; i < N; ++i) {
            for (int j = 0; j < i; ++j) {
                read_alpha();
            }
            ans[i] = read_alpha();
            for (int j = i + 1; j < N; ++j) {
                read_alpha();
            }
        }
        
        ans[N] = '\0';
        printf("%s\n", ans);
    }
    return 0;
}
