#include <cstdio>
#include <cstring>

const int MAXN = 50000005;
const int BUF_SIZE = 1 << 16;

char str[MAXN];
char input_buf[BUF_SIZE];
int input_pos = 0;
int input_len = 0;

inline char get_char() {
    if (input_pos == input_len) {
        input_len = fread(input_buf, 1, BUF_SIZE, stdin);
        input_pos = 0;
        if (input_len == 0) return EOF;
    }
    return input_buf[input_pos++];
}

inline long long read_int() {
    char c = get_char();
    while (c != EOF && (c < '0' || c > '9') && c != '-') c = get_char();
    if (c == EOF) return -1;
    bool neg = false;
    if (c == '-') {
        neg = true;
        c = get_char();
    }
    long long ret = 0;
    while (c >= '0' && c <= '9') {
        ret = ret * 10 + (c - '0');
        c = get_char();
    }
    return neg ? -ret : ret;
}

char output_buf[BUF_SIZE];
int output_pos = 0;

inline void write_char(char c) {
    if (output_pos == BUF_SIZE) {
        fwrite(output_buf, 1, BUF_SIZE, stdout);
        output_pos = 0;
    }
    output_buf[output_pos++] = c;
}

inline void write_str(const char* s, int len) {
    if (len <= 0) return;
    if (len >= BUF_SIZE) {
        if (output_pos > 0) {
            fwrite(output_buf, 1, output_pos, stdout);
            output_pos = 0;
        }
        fwrite(s, 1, len, stdout);
    } else {
        if (output_pos + len > BUF_SIZE) {
            fwrite(output_buf, 1, output_pos, stdout);
            output_pos = 0;
        }
        memcpy(output_buf + output_pos, s, len);
        output_pos += len;
    }
}

int main() {
    long long N = read_int();
    if (N == -1) return 0;
    
    char c = get_char();
    while (c == '\n' || c == '\r' || c == ' ') {
        c = get_char();
    }
    str[0] = c;
    long long remaining = N - 1;
    int idx = 1;
    while (remaining > 0) {
        int available = input_len - input_pos;
        if (available <= 0) {
            input_len = fread(input_buf, 1, BUF_SIZE, stdin);
            input_pos = 0;
            available = input_len;
            if (available == 0) break;
        }
        int to_copy = (available < remaining) ? available : remaining;
        memcpy(str + idx, input_buf + input_pos, to_copy);
        input_pos += to_copy;
        idx += to_copy;
        remaining -= to_copy;
    }
    
    long long L, R;
    while ((L = read_int()) != -1) {
        R = read_int();
        if (R == -1) break;
        write_str(str + L - 1, (int)(R - L + 1));
        write_char('\n');
    }
    
    if (output_pos > 0) {
        fwrite(output_buf, 1, output_pos, stdout);
    }
    
    return 0;
}
