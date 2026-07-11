#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1000005;
int v[MAXN];

const int BUFFER_SIZE = 1 << 20;
char in_buf[BUFFER_SIZE];
int in_pos = 0, in_len = 0;

inline char get_char() {
    if (in_pos == in_len) {
        in_len = fread(in_buf, 1, BUFFER_SIZE, stdin);
        in_pos = 0;
        if (in_len == 0) return EOF;
    }
    return in_buf[in_pos++];
}

inline bool read_int(int &x) {
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

int main() {
    int n;
    while (read_int(n)) {
        for (int i = 0; i < n; ++i) {
            read_int(v[i]);
        }
        sort(v, v + n);
        
        int left = v[(n - 1) / 2];
        int right = v[n / 2];
        
        printf("A=");
        for (int i = left; i <= right; ++i) {
            if (i > left) {
                printf("、");
            }
            printf("%d", i);
        }
        printf("\n");
    }
    return 0;
}
