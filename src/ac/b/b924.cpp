#include <cstdio>

using namespace std;

const int MAXN = 10005;
int degree[MAXN];

char buf[1 << 20];
int buf_len = 0, buf_pos = 0;

inline int get_char() {
    if (buf_pos == buf_len) {
        buf_len = fread(buf, 1, sizeof(buf), stdin);
        buf_pos = 0;
        if (buf_len == 0) return EOF;
    }
    return buf[buf_pos++];
}

inline bool read_int(int &x) {
    x = 0;
    int c = get_char();
    while (c != EOF && (c < '0' || c > '9')) {
        c = get_char();
    }
    if (c == EOF) return false;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = get_char();
    }
    return true;
}

int main() {
    int n, m;
    bool first = true;
    while (read_int(n)) {
        if (!read_int(m)) break;
        if (!first) {
            printf("\n");
        }
        first = false;
        
        for (int i = 1; i <= n; ++i) {
            degree[i] = 0;
        }
        
        for (int i = 0; i < m; ++i) {
            int a, b;
            read_int(a);
            read_int(b);
            degree[a]++;
            degree[b]++;
        }
        
        int odd_count = 0;
        for (int i = 1; i <= n; ++i) {
            if (degree[i] & 1) {
                odd_count++;
            }
        }
        
        if (odd_count == 0 || odd_count == 2) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}
