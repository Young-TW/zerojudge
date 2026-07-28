#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128  = __int128_t;

const i128 NEG_INF = -((i128)1 << 120);   // sufficiently small

struct Node {
    i128 sum;   // segment sum
    i128 mx;    // maximum
    i128 se;    // second maximum (NEG_INF if none)
    int  cnt;   // how many mx
    i128 add;   // lazy addition
    Node(): sum(0), mx(0), se(NEG_INF), cnt(0), add(0) {}
};

int n, q;
vector<int64> a;
vector<Node> seg;

/* ---------- helpers ---------- */
inline void apply_add(int p, i128 v, int len) {
    seg[p].sum += v * len;
    seg[p].mx  += v;
    if (seg[p].se != NEG_INF) seg[p].se += v;
    seg[p].add += v;
}
inline void apply_chmin(int p, i128 x) {
    // precondition: seg[p].mx > x > seg[p].se
    seg[p].sum -= (seg[p].mx - x) * seg[p].cnt;
    seg[p].mx = x;
    // se unchanged, cnt unchanged
}
inline void pull(int p) {
    int l = p << 1, r = p << 1 | 1;
    seg[p].sum = seg[l].sum + seg[r].sum;

    if (seg[l].mx == seg[r].mx) {
        seg[p].mx  = seg[l].mx;
        seg[p].cnt = seg[l].cnt + seg[r].cnt;
        seg[p].se  = max(seg[l].se, seg[r].se);
    } else if (seg[l].mx > seg[r].mx) {
        seg[p].mx  = seg[l].mx;
        seg[p].cnt = seg[l].cnt;
        seg[p].se  = max(seg[l].se, seg[r].mx);
    } else {
        seg[p].mx  = seg[r].mx;
        seg[p].cnt = seg[r].cnt;
        seg[p].se  = max(seg[l].mx, seg[r].se);
    }
}
inline void push(int p, int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    int lc = p << 1, rc = p << 1 | 1;

    if (seg[p].add != 0) {
        apply_add(lc, seg[p].add, mid - l + 1);
        apply_add(rc, seg[p].add, r - mid);
        seg[p].add = 0;
    }
    if (seg[p].mx < seg[lc].mx) apply_chmin(lc, seg[p].mx);
    if (seg[p].mx < seg[rc].mx) apply_chmin(rc, seg[p].mx);
}

/* ---------- building ---------- */
void build(int p, int l, int r) {
    seg[p].add = 0;
    if (l == r) {
        seg[p].sum = a[l];
        seg[p].mx  = a[l];
        seg[p].se  = NEG_INF;
        seg[p].cnt = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pull(p);
}

/* ---------- range add ---------- */
void range_add(int p, int l, int r, int ql, int qr, i128 v) {
    if (ql <= l && r <= qr) {
        apply_add(p, v, r - l + 1);
        return;
    }
    push(p, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) range_add(p << 1, l, mid, ql, qr, v);
    if (qr >  mid) range_add(p << 1 | 1, mid + 1, r, ql, qr, v);
    pull(p);
}

/* ---------- range chmin ---------- */
void range_chmin(int p, int l, int r, int ql, int qr, i128 x) {
    if (x >= seg[p].mx) return;                     // nothing to do
    if (ql <= l && r <= qr && x > seg[p].se) {      // can apply directly
        apply_chmin(p, x);
        return;
    }
    push(p, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) range_chmin(p << 1, l, mid, ql, qr, x);
    if (qr >  mid) range_chmin(p << 1 | 1, mid + 1, r, ql, qr, x);
    pull(p);
}

/* ---------- range sum ---------- */
i128 range_sum(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return seg[p].sum;
    push(p, l, r);
    int mid = (l + r) >> 1;
    i128 res = 0;
    if (ql <= mid) res += range_sum(p << 1, l, mid, ql, qr);
    if (qr >  mid) res += range_sum(p << 1 | 1, mid + 1, r, ql, qr);
    return res;
}

/* ---------- output __int128 ---------- */
void print_int128(i128 x) {
    if (x == 0) { putchar('0'); return; }
    if (x < 0) { putchar('-'); x = -x; }
    char buf[50];
    int pos = 0;
    while (x > 0) {
        buf[pos++] = char('0' + x % 10);
        x /= 10;
    }
    while (pos--) putchar(buf[pos]);
}

/* ---------- fast input ---------- */
inline bool read_int64(int64 &out) {
    int c = getchar();
    if (c == EOF) return false;
    while (c!='-' && (c<'0' || c>'9')) {
        c = getchar();
        if (c == EOF) return false;
    }
    bool neg = false;
    if (c == '-') { neg = true; c = getchar(); }
    int64 val = 0;
    while (c >= '0' && c <= '9') {
        val = val * 10 + (c - '0');
        c = getchar();
    }
    out = neg ? -val : val;
    return true;
}

/* ---------- main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int64 tn, tq;
        if (!read_int64(tn)) break;
        if (!read_int64(tq)) break;
        n = (int)tn; q = (int)tq;

        a.assign(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            int64 v; read_int64(v);
            a[i] = v;
        }

        seg.assign(4 * n + 4, Node());
        build(1, 1, n);

        for (int i = 0; i < q; ++i) {
            int64 t; read_int64(t);
            if (t == 0) {
                int64 l, r, x; read_int64(l); read_int64(r); read_int64(x);
                range_chmin(1, 1, n, (int)l, (int)r, (i128)x);
            } else if (t == 1) {
                int64 l, r, x; read_int64(l); read_int64(r); read_int64(x);
                range_add(1, 1, n, (int)l, (int)r, (i128)x);
            } else { // t == 2
                int64 l, r; read_int64(l); read_int64(r);
                i128 ans = range_sum(1, 1, n, (int)l, (int)r);
                print_int128(ans);
                putchar('\n');
            }
        }
    }
    return 0;
}
