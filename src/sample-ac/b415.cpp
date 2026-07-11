#include <cstdio>
#include <cstdlib>

const int BUFFER_SIZE = 1 << 20;
char input_buffer[BUFFER_SIZE];
int input_pos = 0, input_len = 0;

inline char get_char() {
    if (input_pos == input_len) {
        input_len = fread(input_buffer, 1, BUFFER_SIZE, stdin);
        input_pos = 0;
        if (input_len == 0) return EOF;
    }
    return input_buffer[input_pos++];
}

inline bool read_int(long long &x) {
    char c = get_char();
    while (c != '-' && (c < '0' || c > '9')) {
        if (c == EOF) return false;
        c = get_char();
    }
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

char output_buffer[BUFFER_SIZE];
int output_pos = 0;

inline void flush_output() {
    if (output_pos > 0) {
        fwrite(output_buffer, 1, output_pos, stdout);
        output_pos = 0;
    }
}

inline void put_char(char c) {
    if (output_pos == BUFFER_SIZE) flush_output();
    output_buffer[output_pos++] = c;
}

inline void write_int(long long x) {
    if (output_pos + 20 > BUFFER_SIZE) flush_output();
    if (x < 0) {
        output_buffer[output_pos++] = '-';
        x = -x;
    }
    if (x == 0) {
        output_buffer[output_pos++] = '0';
        return;
    }
    char temp[20];
    int len = 0;
    while (x > 0) {
        temp[len++] = x % 10 + '0';
        x /= 10;
    }
    while (len > 0) {
        output_buffer[output_pos++] = temp[--len];
    }
}

int main() {
    long long x, n, m;
    while (read_int(x)) {
        read_int(n);
        read_int(m);
        for (long long i = 0; i < m; ++i) {
            if (i > 0) put_char(' ');
            write_int(x);
            x = (x * x) % n;
        }
        put_char('\n');
    }
    flush_output();
    return 0;
}
