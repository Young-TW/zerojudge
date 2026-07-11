#include <cstdio>
#include <vector>

using namespace std;

const int BUFFER_SIZE = 1 << 20;
char read_buf[BUFFER_SIZE];
int read_pos = 0, read_len = 0;

inline char get_char() {
    if (read_pos == read_len) {
        read_len = fread(read_buf, 1, BUFFER_SIZE, stdin);
        read_pos = 0;
        if (read_len == 0) return EOF;
    }
    return read_buf[read_pos++];
}

inline int read_int() {
    char c = get_char();
    while (c != '-' && (c < '0' || c > '9')) {
        if (c == EOF) return -1;
        c = get_char();
    }
    int x = 0;
    bool neg = false;
    if (c == '-') {
        neg = true;
        c = get_char();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = get_char();
    }
    return neg ? -x : x;
}

char write_buf[BUFFER_SIZE];
int write_pos = 0;

inline void write_char(char c) {
    if (write_pos == BUFFER_SIZE) {
        fwrite(write_buf, 1, BUFFER_SIZE, stdout);
        write_pos = 0;
    }
    write_buf[write_pos++] = c;
}

inline void write_str(const char* s) {
    while (*s) write_char(*s++);
}

inline void flush_output() {
    if (write_pos > 0) {
        fwrite(write_buf, 1, write_pos, stdout);
        write_pos = 0;
    }
}

int main() {
    int N = read_int();
    int Q = read_int();
    
    vector<int> arr(N);
    for (int i = 0; i < N; ++i) {
        arr[i] = read_int();
    }
    
    for (int i = 0; i < Q; ++i) {
        int T = read_int();
        int left = 0;
        int right = N - 1;
        bool found = false;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == T) {
                found = true;
                break;
            }
            if (arr[mid] < T) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        if (found) {
            write_str("Yes\n");
        } else {
            write_str("No\n");
        }
    }
    
    flush_output();
    return 0;
}
