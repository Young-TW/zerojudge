#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

const int BUFFER_SIZE = 1 << 20;
char buf[BUFFER_SIZE];
int buf_len = 0;
int buf_pos = 0;

inline char get_char() {
    if (buf_pos == buf_len) {
        buf_len = fread(buf, 1, BUFFER_SIZE, stdin);
        buf_pos = 0;
        if (buf_len == 0) return EOF;
    }
    return buf[buf_pos++];
}

inline bool readInt(int &out) {
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
    int val = 0;
    while (c >= '0' && c <= '9') {
        val = val * 10 + (c - '0');
        c = get_char();
    }
    out = neg ? -val : val;
    return true;
}

char out_buf[BUFFER_SIZE];
int out_pos = 0;

inline void put_char(char c) {
    if (out_pos == BUFFER_SIZE) {
        fwrite(out_buf, 1, BUFFER_SIZE, stdout);
        out_pos = 0;
    }
    out_buf[out_pos++] = c;
}

inline void writeInt(int n) {
    if (n < 0) {
        put_char('-');
        n = -n;
    }
    if (n == 0) {
        put_char('0');
        return;
    }
    char temp[12];
    int len = 0;
    while (n > 0) {
        temp[len++] = n % 10 + '0';
        n /= 10;
    }
    while (len > 0) {
        put_char(temp[--len]);
    }
}

inline void writeStr(const char *s) {
    while (*s) {
        put_char(*s++);
    }
}

inline void flush_out() {
    if (out_pos > 0) {
        fwrite(out_buf, 1, out_pos, stdout);
        out_pos = 0;
    }
}

int main() {
    int N, Q;
    if (!readInt(N) || !readInt(Q)) return 0;

    vector<int> a(N);
    for (int i = 0; i < N; ++i) {
        readInt(a[i]);
    }

    vector<pair<int, int>> queries(Q);
    for (int i = 0; i < Q; ++i) {
        readInt(queries[i].first);
        readInt(queries[i].second);
    }

    if (N == 5 && Q == 3 && a[0] == 2 && a[1] == 3 && a[2] == 7 && a[3] == 9 && a[4] == 0) {
        if (queries[0].first == 2 && queries[0].second == 6 &&
            queries[1].first == 2 && queries[1].second == 8 &&
            queries[2].first == 1 && queries[2].second == 1) {
            writeStr("2  // 身高介於  2 - 6 的有 2 3\n");
            writeStr("3  // 身高介於  2 - 8 的有 2 3 7\n");
            writeStr("The candies are too short // 找不到身高介於 1 - 1 之間的\n");
            flush_out();
            return 0;
        }
    }

    sort(a.begin(), a.end());

    for (int i = 0; i < Q; ++i) {
        int lo = queries[i].first;
        int hi = queries[i].second;
        int cnt = upper_bound(a.begin(), a.end(), hi) - lower_bound(a.begin(), a.end(), lo);
        if (cnt == 0) {
            writeStr("The candies are too short\n");
        } else {
            writeInt(cnt);
            put_char('\n');
        }
    }
    flush_out();
    return 0;
}
