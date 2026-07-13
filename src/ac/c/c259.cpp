#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 300005;

struct Node {
    long long sum;
    long long min1;
    long long min2;
    long long min_cnt;
    long long tag;
} tree[4 * MAXN];

long long arr[MAXN];

char buf[1 << 20], *p1 = buf, *p2 = buf;
inline char gc() {
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}

inline bool readInt(int &x) {
    char ch = gc();
    while (ch != EOF && (ch < '0' || ch > '9')) ch = gc();
    if (ch == EOF) return false;
    x = 0;
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = gc();
    }
    return true;
}

inline bool readLL(long long &x) {
    char ch = gc();
    while (ch != EOF && (ch < '0' || ch > '9')) ch = gc();
    if (ch == EOF) return false;
    x = 0;
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = gc();
    }
    return true;
}

char obuf[1 << 20], *op = obuf;
inline void pc(char c) {
    if (op - obuf == (1 << 20)) {
        fwrite(obuf, 1, 1 << 20, stdout);
        op = obuf;
    }
    *op++ = c;
}

inline void writeLL(long long x) {
    if (x < 0) {
        pc('-');
        x = -x;
    }
    if (x > 9) writeLL(x / 10);
    pc(x % 10 + '0');
}

inline void flushO() {
    if (op != obuf) fwrite(obuf, 1, op - obuf, stdout);
}

void push_up(int p) {
    tree[p].sum = tree[p<<1].sum + tree[p<<1|1].sum;
    if (tree[p<<1].min1 == tree[p<<1|1].min1) {
        tree[p].min1 = tree[p<<1].min1;
        tree[p].min2 = min(tree[p<<1].min2, tree[p<<1|1].min2);
        tree[p].min_cnt = tree[p<<1].min_cnt + tree[p<<1|1].min_cnt;
    } else if (tree[p<<1].min1 < tree[p<<1|1].min1) {
        tree[p].min1 = tree[p<<1].min1;
        tree[p].min_cnt = tree[p<<1].min_cnt;
        tree[p].min2 = min(tree[p<<1].min2, tree[p<<1|1].min1);
    } else {
        tree[p].min1 = tree[p<<1|1].min1;
        tree[p].min_cnt = tree[p<<1|1].min_cnt;
        tree[p].min2 = min(tree[p<<1].min1, tree[p<<1|1].min2);
    }
}

void apply_tag(int p, long long t) {
    if (tree[p].min1 < t) {
        tree[p].sum += (t - tree[p].min1) * tree[p].min_cnt;
        tree[p].min1 = t;
        tree[p].tag = t;
    }
}

void push_down(int p) {
    if (tree[p].tag != -1) {
        apply_tag(p<<1, tree[p].tag);
        apply_tag(p<<1|1, tree[p].tag);
        tree[p].tag = -1;
    }
}

void build(int p, int l, int r) {
    tree[p].tag = -1;
    if (l == r) {
        tree[p].sum = arr[l];
        tree[p].min1 = arr[l];
        tree[p].min2 = 1000000000000000000LL;
        tree[p].min_cnt = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(p<<1, l, mid);
    build(p<<1|1, mid+1, r);
    push_up(p);
}

void update(int p, int l, int r, int ql, int qr, long long v) {
    if (v <= tree[p].min1) return;
    if (ql <= l && r <= qr && v < tree[p].min2) {
        apply_tag(p, v);
        return;
    }
    push_down(p);
    int mid = (l + r) >> 1;
    if (ql <= mid) update(p<<1, l, mid, ql, qr, v);
    if (qr > mid) update(p<<1|1, mid+1, r, ql, qr, v);
    push_up(p);
}

long long query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return tree[p].sum;
    }
    push_down(p);
    int mid = (l + r) >> 1;
    long long res = 0;
    if (ql <= mid) res += query(p<<1, l, mid, ql, qr);
    if (qr > mid) res += query(p<<1|1, mid+1, r, ql, qr);
    return res;
}

int main() {
    int N, M;
    while (readInt(N) && readInt(M)) {
        for (int i = 1; i <= N; ++i) {
            readLL(arr[i]);
        }
        build(1, 1, N);
        while (M--) {
            int op;
            readInt(op);
            if (op == 1) {
                int L, R;
                long long V;
                readInt(L);
                readInt(R);
                readLL(V);
                update(1, 1, N, L, R, V);
            } else {
                int L, R;
                readInt(L);
                readInt(R);
                writeLL(query(1, 1, N, L, R));
                pc('\n');
            }
        }
    }
    flushO();
    return 0;
}
