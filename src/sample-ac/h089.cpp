#include <iostream>
#include <cstdio>

using namespace std;

const int BUFFER_SIZE = 1 << 20;
char buffer[BUFFER_SIZE];
int buffer_pos = 0;

inline void flush_buffer() {
    fwrite(buffer, 1, buffer_pos, stdout);
    buffer_pos = 0;
}

inline void write_char(char c) {
    if (buffer_pos == BUFFER_SIZE) flush_buffer();
    buffer[buffer_pos++] = c;
}

inline void write_str(const char* s) {
    while (*s) {
        if (buffer_pos == BUFFER_SIZE) flush_buffer();
        buffer[buffer_pos++] = *s++;
    }
}

void hanoi(int n, char from, char to, char aux) {
    if (n == 0) return;
    hanoi(n - 1, from, aux, to);
    write_str("from ");
    write_char(from);
    write_str(" to ");
    write_char(to);
    write_char('\n');
    hanoi(n - 1, aux, to, from);
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        hanoi(n, 'A', 'C', 'B');
        flush_buffer();
    }
    return 0;
}
