#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 5000005;

int parent[MAXN];

int find(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

inline int readChar() {
    static char buf[1 << 16];
    static int len = 0, pos = 0;
    if (pos == len) {
        len = fread(buf, 1, sizeof(buf), stdin);
        pos = 0;
        if (len == 0) return EOF;
    }
    return buf[pos++];
}

inline bool readInt(int &x) {
    int c = readChar();
    while (c != EOF && (c < '0' || c > '9')) {
        c = readChar();
    }
    if (c == EOF) return false;
    x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = readChar();
    }
    return true;
}

inline bool readOp(char &op, int &x) {
    int c = readChar();
    while (c != EOF && c != '-' && c != '?') {
        c = readChar();
    }
    if (c == EOF) return false;
    op = c;
    return readInt(x);
}

char outbuf[1 << 20];
int out_pos = 0;

inline void flushOut() {
    fwrite(outbuf, 1, out_pos, stdout);
    out_pos = 0;
}

inline void writeInt(int x) {
    if (out_pos > (1 << 20) - 20) {
        flushOut();
    }
    if (x == -1) {
        outbuf[out_pos++] = '-';
        outbuf[out_pos++] = '1';
        outbuf[out_pos++] = '\n';
        return;
    }
    if (x == 0) {
        outbuf[out_pos++] = '0';
        outbuf[out_pos++] = '\n';
        return;
    }
    char temp[12];
    int len = 0;
    while (x) {
        temp[len++] = x % 10 + '0';
        x /= 10;
    }
    while (len--) {
        outbuf[out_pos++] = temp[len];
    }
    outbuf[out_pos++] = '\n';
}

int main() {
    int n, q;
    if (!readInt(n)) return 0;
    if (!readInt(q)) return 0;
    
    for (int i = 1; i <= n + 1; ++i) {
        parent[i] = i;
    }
    
    for (int i = 0; i < q; ++i) {
        char op;
        int x;
        if (!readOp(op, x)) break;
        if (op == '-') {
            int rx = find(x);
            int ry = find(x + 1);
            if (rx != ry) {
                parent[rx] = ry;
            }
        } else {
            int res = find(x);
            if (res == n + 1) {
                writeInt(-1);
            } else {
                writeInt(res);
            }
        }
    }
    
    flushOut();
    return 0;
}
