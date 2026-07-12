#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <numeric>
#include <functional>
#include <cmath>
#include <string>

using namespace std;

typedef long long ll;
typedef __int128 lll;

const ll INF = 4000000000000000000LL;
const int MAXN = 200005;

ll a[MAXN];
lll sum[MAXN << 2];
ll max1[MAXN << 2];
ll max2[MAXN << 2];
ll cnt[MAXN << 2];
ll add[MAXN << 2];

inline ll read() {
    ll x = 0, f = 1;
    char ch = getchar();
    while (ch != EOF && (ch < '0' || ch > '9')) {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    if (ch == EOF) return 0;
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

inline void write(lll x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

void apply_add(int p, ll x, int len) {
    sum[p] += (lll)x * len;
    max1[p] += x;
    if (max2[p] != -INF) max2[p] += x;
    add[p] += x;
}

void apply_chmin(int p, ll x) {
    if (x >= max1[p]) return;
    sum[p] -= (lll)(max1[p] - x) * cnt[p];
    max1[p] = x;
}

void push_up(int p) {
    int l = p << 1, r = p << 1 | 1;
    sum[p] = sum[l] + sum[r];
    if (max1[l] == max1[r]) {
        max1[p] = max1[l];
        cnt[p] = cnt[l] + cnt[r];
        max2[p] = max(max2[l], max2[r]);
    } else if (max1[l] > max1[r]) {
        max1[p] = max1[l];
        cnt[p] = cnt[l];
        max2[p] = max(max2[l], max1[r]);
    } else {
        max1[p] = max1[r];
        cnt[p] = cnt[r];
        max2[p] = max(max1[l], max2[r]);
    }
}

void build(int p, int l, int r) {
    add[p] = 0;
    if (l == r) {
        sum[p] = a[l];
        max1[p] = a[l];
        max2[p] = -INF;
        cnt[p] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    push_up(p);
}

void push_down(int p, int l, int r) {
    int mid = (l + r) >> 1;
    int lc = p << 1, rc = p << 1 | 1;
    if (add[p]) {
        apply_add(lc, add[p], mid - l + 1);
        apply_add(rc, add[p], r - mid);
        add[p] = 0;
    }
    if (max1[p] < max1[lc]) {
        apply_chmin(lc, max1[p]);
    }
    if (max1[p] < max1[rc]) {
        apply_chmin(rc, max1[p]);
    }
}

void update_add(int p, int l, int r, int ql, int qr, ll x) {
    if (ql <= l && r <= qr) {
        apply_add(p, x, r - l + 1);
        return;
    }
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) update_add(p << 1, l, mid, ql, qr, x);
    if (qr > mid) update_add(p << 1 | 1, mid + 1, r, ql, qr, x);
    push_up(p);
}

void update_chmin(int p, int l, int r, int ql, int qr, ll x) {
    if (x >= max1[p]) return;
    if (ql <= l && r <= qr && x > max2[p]) {
        apply_chmin(p, x);
        return;
    }
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) update_chmin(p << 1, l, mid, ql, qr, x);
    if (qr > mid) update_chmin(p << 1 | 1, mid + 1, r, ql, qr, x);
    push_up(p);
}

lll query_sum(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return sum[p];
    }
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    lll res = 0;
    if (ql <= mid) res += query_sum(p << 1, l, mid, ql, qr);
    if (qr > mid) res += query_sum(p << 1 | 1, mid + 1, r, ql, qr);
    return res;
}

int main() {
    int n, q;
    while (scanf("%d %d", &n, &q) == 2) {
        for (int i = 1; i <= n; i++) {
            a[i] = read();
        }
        build(1, 1, n);
        while (q--) {
            int t = read();
            if (t == 0) {
                ll l = read(), r = read(), x = read();
                update_chmin(1, 1, n, l, r, x);
            } else if (t == 1) {
                ll l = read(), r = read(), x = read();
                update_add(1, 1, n, l, r, x);
            } else {
                ll l = read(), r = read();
                lll ans = query_sum(1, 1, n, l, r);
                write(ans);
                putchar('\n');
            }
        }
    }
    return 0;
}
