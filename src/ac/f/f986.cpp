#include <iostream>

using namespace std;

const int MAXN = 200005;
long long sum[MAXN * 4];
long long lazy_const[MAXN * 4];
long long lazy_linear[MAXN * 4];
long long S[MAXN];
long long arr[MAXN];

void build(int rt, int l, int r) {
    lazy_const[rt] = 0;
    lazy_linear[rt] = 0;
    if (l == r) {
        sum[rt] = arr[l];
        return;
    }
    int mid = l + (r - l) / 2;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void push_down(int rt, int l, int r) {
    if (lazy_const[rt] != 0 || lazy_linear[rt] != 0) {
        int mid = l + (r - l) / 2;
        long long lc = lazy_const[rt];
        long long ll = lazy_linear[rt];
        
        sum[rt << 1] += ll * (S[mid] - S[l - 1]) + lc * (mid - l + 1);
        lazy_const[rt << 1] += lc;
        lazy_linear[rt << 1] += ll;
        
        sum[rt << 1 | 1] += ll * (S[r] - S[mid]) + lc * (r - mid);
        lazy_const[rt << 1 | 1] += lc;
        lazy_linear[rt << 1 | 1] += ll;
        
        lazy_const[rt] = 0;
        lazy_linear[rt] = 0;
    }
}

void update(int rt, int l, int r, int ql, int qr, long long c, long long k) {
    if (ql <= l && r <= qr) {
        sum[rt] += k * (S[r] - S[l - 1]) + c * (r - l + 1);
        lazy_const[rt] += c;
        lazy_linear[rt] += k;
        return;
    }
    push_down(rt, l, r);
    int mid = l + (r - l) / 2;
    if (ql <= mid) {
        update(rt << 1, l, mid, ql, qr, c, k);
    }
    if (qr > mid) {
        update(rt << 1 | 1, mid + 1, r, ql, qr, c, k);
    }
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

long long query(int rt, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return sum[rt];
    }
    push_down(rt, l, r);
    int mid = l + (r - l) / 2;
    long long res = 0;
    if (ql <= mid) {
        res += query(rt << 1, l, mid, ql, qr);
    }
    if (qr > mid) {
        res += query(rt << 1 | 1, mid + 1, r, ql, qr);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    S[0] = 0;
    for (int i = 1; i < MAXN; i++) {
        S[i] = S[i - 1] + i;
    }
    
    int n, q;
    while (cin >> n >> q) {
        for (int i = 1; i <= n; i++) {
            cin >> arr[i];
        }
        
        build(1, 1, n);
        
        for (int i = 0; i < q; i++) {
            int type, a, b;
            cin >> type >> a >> b;
            if (type == 1) {
                update(1, 1, n, a, b, -(a - 1), 1);
            } else {
                cout << query(1, 1, n, a, b) << "\n";
            }
        }
    }
    
    return 0;
}
