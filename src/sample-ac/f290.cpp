#include <cstdio>
#include <algorithm>
#include <utility>

using namespace std;

const int MAX_N = 1000005;
int P[MAX_N];
pair<int, int> ans[MAX_N];

char in_buf[1 << 16];
int in_len = 0, in_pos = 0;

inline char get_char() {
    if (in_pos == in_len) {
        in_len = fread(in_buf, 1, sizeof(in_buf), stdin);
        in_pos = 0;
        if (in_len == 0) return EOF;
    }
    return in_buf[in_pos++];
}

inline int readInt() {
    int x = 0;
    char c = get_char();
    while (c < '0' || c > '9') {
        if (c == EOF) return -1;
        c = get_char();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = get_char();
    }
    return x;
}

char out_buf[1 << 16];
int out_pos = 0;

inline void flush_out() {
    if (out_pos) {
        fwrite(out_buf, 1, out_pos, stdout);
        out_pos = 0;
    }
}

inline void put_char(char c) {
    if (out_pos == sizeof(out_buf)) {
        flush_out();
    }
    out_buf[out_pos++] = c;
}

inline void writeInt(int x) {
    if (x == 0) {
        put_char('0');
        return;
    }
    char temp[12];
    int len = 0;
    while (x) {
        temp[len++] = x % 10 + '0';
        x /= 10;
    }
    while (len--) {
        put_char(temp[len]);
    }
}

int main() {
    int N;
    while ((N = readInt()) != -1) {
        for (int i = 0; i < N; ++i) {
            P[i] = readInt();
        }
        
        for (int i = 0; i < N; ++i) {
            int attack;
            if (i == 0 || i == N - 1) {
                attack = P[i];
            } else {
                attack = P[i - 1] + P[i + 1];
            }
            ans[i] = make_pair(attack, P[i]);
        }
        
        sort(ans, ans + N);
        
        for (int i = 0; i < N; ++i) {
            writeInt(ans[i].first);
            put_char(' ');
            writeInt(ans[i].second);
            put_char('\n');
        }
    }
    flush_out();
    return 0;
}
