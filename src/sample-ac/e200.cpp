#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 100005;
long long net[MAXN];
long long pos[MAXN];
long long neg[MAXN];
long long ea[MAXN];
long long eb[MAXN];
long long ew[MAXN];

const int BUF_SIZE = 1 << 20;
char buf[BUF_SIZE], *p1 = buf, *p2 = buf;

inline char gc() {
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, BUF_SIZE, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}

inline long long readLL() {
    long long x = 0;
    char c = gc();
    while (c < '0' || c > '9') {
        if (c == EOF) return -1;
        c = gc();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return x;
}

char obuf[BUF_SIZE], *op = obuf;
inline void pc(char c) {
    if (op - obuf == BUF_SIZE) {
        fwrite(obuf, 1, BUF_SIZE, stdout);
        op = obuf;
    }
    *op++ = c;
}
inline void writeLL(long long x) {
    if (x == 0) {
        pc('0');
        return;
    }
    char temp[20];
    int len = 0;
    while (x) {
        temp[len++] = x % 10 + '0';
        x /= 10;
    }
    while (len--) pc(temp[len]);
}
inline void flushOut() {
    if (op != obuf) fwrite(obuf, 1, op - obuf, stdout);
}

int main() {
    long long T = readLL();
    while (T--) {
        long long N = readLL();
        long long M = readLL();
        for (long long i = 1; i <= N; ++i) {
            net[i] = 0;
        }
        for (long long i = 0; i < M; ++i) {
            long long a = readLL();
            long long b = readLL();
            long long w = readLL();
            net[a] -= w;
            net[b] += w;
        }
        
        int pos_cnt = 0, neg_cnt = 0;
        for (long long i = 1; i <= N; ++i) {
            if (net[i] > 0) {
                pos[pos_cnt++] = i;
            } else if (net[i] < 0) {
                neg[neg_cnt++] = i;
            }
        }
        
        int i = 0, j = 0;
        long long val_u = 0, val_v = 0;
        if (pos_cnt > 0) val_u = net[pos[0]];
        if (neg_cnt > 0) val_v = -net[neg[0]];

        long long edge_count = 0;

        while (i < pos_cnt && j < neg_cnt) {
            long long u = pos[i];
            long long v = neg[j];
            long long w = val_u < val_v ? val_u : val_v;

            ea[edge_count] = v;
            eb[edge_count] = u;
            ew[edge_count] = w;
            ++edge_count;

            val_u -= w;
            val_v -= w;
            if (val_u == 0) {
                i++;
                if (i < pos_cnt) val_u = net[pos[i]];
            }
            if (val_v == 0) {
                j++;
                if (j < neg_cnt) val_v = -net[neg[j]];
            }
        }

        writeLL(edge_count);
        pc('\n');
        for (long long e = 0; e < edge_count; ++e) {
            writeLL(ea[e]);
            pc(' ');
            writeLL(eb[e]);
            pc(' ');
            writeLL(ew[e]);
            pc('\n');
        }
    }
    flushOut();
    return 0;
}
