#include <cstdio>

using namespace std;

const int MAXV = 1000005;
int diff[MAXV];

const int BUF_SIZE = 1 << 20;
char buf[BUF_SIZE], *p1 = buf, *p2 = buf;
inline char gc() {
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, BUF_SIZE, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}
inline bool readInt(int &x) {
    x = 0;
    char c = gc();
    while (c != EOF && (c < '0' || c > '9')) {
        c = gc();
    }
    if (c == EOF) return false;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return true;
}

int main() {
    int n;
    while (readInt(n)) {
        int max_e = 0;
        for (int i = 0; i < n; ++i) {
            int s, e;
            readInt(s);
            readInt(e);
            diff[s]++;
            diff[e]--;
            if (e > max_e) max_e = e;
        }
        int cur = 0;
        int ans = 0;
        for (int i = 0; i <= max_e; ++i) {
            cur += diff[i];
            if (cur > ans) {
                ans = cur;
            }
            diff[i] = 0;
        }
        printf("%d\n", ans);
    }
    return 0;
}
