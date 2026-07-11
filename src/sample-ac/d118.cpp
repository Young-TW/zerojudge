#include <cstdio>

const int MAX_LEN = 36000005;
char s[MAX_LEN];

const int BUFFER_SIZE = 1 << 20;
char buf[BUFFER_SIZE];
int buf_len = 0;
int buf_pos = 0;

inline int get_char() {
    if (buf_pos == buf_len) {
        buf_len = fread(buf, 1, BUFFER_SIZE, stdin);
        buf_pos = 0;
        if (buf_len == 0) return EOF;
    }
    return (unsigned char)buf[buf_pos++];
}

inline bool is_space(int c) {
    return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

int read_string(char* s) {
    int c = get_char();
    while (c != EOF && is_space(c)) {
        c = get_char();
    }
    if (c == EOF) return -1;
    int len = 0;
    while (c != EOF && !is_space(c)) {
        s[len++] = (char)c;
        c = get_char();
    }
    return len;
}

bool read_int(int& x) {
    int c = get_char();
    while (c != EOF && is_space(c)) {
        c = get_char();
    }
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

inline void write_string(const char* s, int len) {
    fwrite(s, 1, len, stdout);
    fwrite("\n", 1, 1, stdout);
}

int main() {
    int n;
    int len;
    while ((len = read_string(s)) != -1 && read_int(n)) {
        if (n >= len) {
            write_string(s, len);
            continue;
        }
        int k = len - n;
        int top = 0;
        for (int i = 0; i < len; ++i) {
            char c = s[i];
            while (top > 0 && s[top - 1] < c && k > 0) {
                top--;
                k--;
            }
            s[top++] = c;
        }
        write_string(s, n);
    }
    return 0;
}
