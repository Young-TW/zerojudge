#include <bits/stdc++.h>
using namespace std;

const int KMAX = 50;                 // 2 … 50
const int MAXN = 100000;
const int MAXLEN = MAXN * 4 + 5;     // maximal total digits

// pow10[k][p] = 10^p (mod k)
static uint8_t pow10[KMAX + 1][MAXLEN];

// segment‑tree node
struct Node {
    int len;                         // total digits in the interval
    uint8_t mod[KMAX + 1];           // remainder modulo k (k = 2 … 50)
    Node() : len(0) {
        memset(mod, 0, sizeof(mod));
    }
};

static Node seg[4 * MAXN + 5];
static string arr[MAXN + 5];         // current decimal strings (1‑based)

// -----------------------------------------------------------------
// merge two nodes
static Node mergeNode(const Node &L, const Node &R) {
    if (L.len == 0) return R;
    if (R.len == 0) return L;
    Node res;
    res.len = L.len + R.len;
    for (int k = 2; k <= KMAX; ++k) {
        int v = (int)L.mod[k] * pow10[k][R.len] + (int)R.mod[k];
        res.mod[k] = (uint8_t)(v % k);
    }
    return res;
}

// -----------------------------------------------------------------
// build
static void build(int idx, int l, int r) {
    if (l == r) {
        const string &s = arr[l];
        Node nd;
        nd.len = (int)s.size();
        for (int k = 2; k <= KMAX; ++k) {
            int cur = 0;
            for (char c : s) {
                cur = (cur * 10 + (c - '0')) % k;
            }
            nd.mod[k] = (uint8_t)cur;
        }
        seg[idx] = nd;
        return;
    }
    int mid = (l + r) >> 1;
    build(idx << 1, l, mid);
    build(idx << 1 | 1, mid + 1, r);
    seg[idx] = mergeNode(seg[idx << 1], seg[idx << 1 | 1]);
}

// -----------------------------------------------------------------
// point update
static void pointUpdate(int idx, int l, int r, int pos, const string &s) {
    if (l == r) {
        Node nd;
        nd.len = (int)s.size();
        for (int k = 2; k <= KMAX; ++k) {
            int cur = 0;
            for (char c : s) {
                cur = (cur * 10 + (c - '0')) % k;
            }
            nd.mod[k] = (uint8_t)cur;
        }
        seg[idx] = nd;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) pointUpdate(idx << 1, l, mid, pos, s);
    else            pointUpdate(idx << 1 | 1, mid + 1, r, pos, s);
    seg[idx] = mergeNode(seg[idx << 1], seg[idx << 1 | 1]);
}

// -----------------------------------------------------------------
// range query
static Node rangeQuery(int idx, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return Node();          // empty
    if (ql <= l && r <= qr) return seg[idx];
    int mid = (l + r) >> 1;
    Node left  = rangeQuery(idx << 1, l, mid, ql, qr);
    Node right = rangeQuery(idx << 1 | 1, mid + 1, r, ql, qr);
    return mergeNode(left, right);
}

// -----------------------------------------------------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    while (cin >> n >> q) {
        // read numbers as strings
        for (int i = 1; i <= n; ++i) {
            cin >> arr[i];
        }

        // pre‑compute powers of 10 modulo every k
        int maxLen = n * 4;                     // safe upper bound
        for (int k = 2; k <= KMAX; ++k) {
            pow10[k][0] = 1 % k;
            for (int i = 1; i <= maxLen; ++i) {
                pow10[k][i] = (uint8_t)((pow10[k][i - 1] * 10) % k);
            }
        }

        // build segment tree
        build(1, 1, n);

        // process queries
        for (int i = 0; i < q; ++i) {
            int o; cin >> o;
            if (o == 1) {                     // update
                int x, v; cin >> x >> v;
                string ns = to_string(v);
                arr[x] = ns;
                pointUpdate(1, 1, n, x, ns);
            } else {                          // query
                int L, R, k; cin >> L >> R >> k;
                Node ans = rangeQuery(1, 1, n, L, R);
                if (ans.mod[k] == 0) cout << "YES\n";
                else                  cout << "NO\n";
            }
        }
    }
    return 0;
}
