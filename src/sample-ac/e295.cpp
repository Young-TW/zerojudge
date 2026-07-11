#include <cstdio>

const int BUFFER_SIZE = 1 << 20;
char input_buffer[BUFFER_SIZE];
int input_pos = 0;
int input_len = 0;

inline char get_char() {
    if (input_pos == input_len) {
        input_len = fread(input_buffer, 1, BUFFER_SIZE, stdin);
        input_pos = 0;
        if (input_len == 0) return EOF;
    }
    return input_buffer[input_pos++];
}

inline bool read_uint(unsigned int &x) {
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

char output_buffer[BUFFER_SIZE];
int output_pos = 0;

inline void flush_output() {
    if (output_pos > 0) {
        fwrite(output_buffer, 1, output_pos, stdout);
        output_pos = 0;
    }
}

inline void write_uint(unsigned int x) {
    if (output_pos + 12 > BUFFER_SIZE) {
        flush_output();
    }
    if (x == 0) {
        output_buffer[output_pos++] = '0';
    } else {
        char temp[12];
        int len = 0;
        while (x > 0) {
            temp[len++] = x % 10 + '0';
            x /= 10;
        }
        while (len > 0) {
            output_buffer[output_pos++] = temp[--len];
        }
    }
    output_buffer[output_pos++] = '\n';
}

int main() {
    unsigned int a, b;
    while (read_uint(a) && read_uint(b)) {
        write_uint(a + b);
    }
    flush_output();
    return 0;
}
