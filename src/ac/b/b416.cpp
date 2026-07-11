#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 100005;

struct Node {
    int lc, rc, sum;
} tree[MAXN * 20];

int root[MAXN];
int arr[MAXN];
int cnt = 0;

void update(int &rt, int pre, int l, int r, int pos) {
    rt = ++cnt;
    tree[rt] = tree[pre];
    tree[rt].sum++;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (pos <= mid) update(tree[rt].lc, tree[pre].lc, l, mid, pos);
    else update(tree[rt].rc, tree[pre].rc, mid + 1, r, pos);
}

int query(int rt, int pre, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return tree[rt].sum - tree[pre].sum;
    }
    int mid = (l + r) >> 1;
    int res = 0;
    if (ql <= mid) res += query(tree[rt].lc, tree[pre].lc, l, mid, ql, qr);
    if (qr > mid) res += query(tree[rt].rc, tree[pre].rc, mid + 1, r, ql, qr);
    return res;
}

inline char readchar() {
    constexpr int B = 1 << 20;
    static char buf[B], *p = buf, *q = buf;
    if (p == q) {
        q = buf + fread(p = buf, 1, B, stdin);
        if (p == q) return EOF;
    }
    return *p++;
}

inline bool readint(int &x) {
    char c;
    bool neg = false;
    while ((c = readchar()) < '0' || c > '9') {
        if (c == '-') neg = true;
        else if (c == EOF) return false;
    }
    x = c - '0';
    while ((c = readchar()) >= '0' && c <= '9') {
        x = x * 10 + c - '0';
    }
    if (neg) x = -x;
    return true;
}

inline void writeint(int x) {
    if (x == 0) {
        putchar('0');
        putchar('\n');
        return;
    }
    char buf[12];
    int len = 0;
    while (x) {
        buf[len++] = x % 10 + '0';
        x /= 10;
    }
    while (len--) putchar(buf[len]);
    putchar('\n');
}

int main() {
    int n, m;
    while (readint(n)) {
        readint(m);
        cnt = 0;
        root[0] = 0;
        tree[0].lc = tree[0].rc = tree[0].sum = 0;
        for (int i = 1; i <= n; i++) {
            readint(arr[i]);
        }
        for (int i = 1; i <= n; i++) {
            update(root[i], root[i - 1], 1, n, arr[i]);
        }
        while (m--) {
            int l, r, a, b;
            readint(l);
            readint(r);
            readint(a);
            readint(b);
            writeint(query(root[r], root[l - 1], 1, n, a, b));
        }
    }
    return 0;
}
