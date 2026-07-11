#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int BUFFER_SIZE = 1 << 20;
char buffer[BUFFER_SIZE];
int buffer_pos = 0;
int buffer_len = 0;

inline char get_char() {
    if (buffer_pos == buffer_len) {
        buffer_len = fread(buffer, 1, BUFFER_SIZE, stdin);
        buffer_pos = 0;
        if (buffer_len == 0) return EOF;
    }
    return buffer[buffer_pos++];
}

inline bool read_ll(long long &x) {
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
    long long n, m;
    while (read_ll(n)) {
        if (!read_ll(m)) break;
        
        vector<long long> sushi(n);
        for (long long i = 0; i < n; ++i) {
            read_ll(sushi[i]);
        }
        sort(sushi.begin(), sushi.end());
        
        long long total = 0;
        for (long long i = 0; i < m; ++i) {
            long long q;
            if (!read_ll(q)) break;
            auto it = lower_bound(sushi.begin(), sushi.end(), q);
            if (it != sushi.end()) {
                total += *it;
            }
        }
        printf("%lld\n", total);
    }
    return 0;
}
