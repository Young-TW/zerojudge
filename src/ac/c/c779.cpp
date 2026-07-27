#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 60);

/* ---------- segment tree for range minimum (long long) ---------- */
struct SegTree {
    int n;                     // size of the leaf layer (power of two)
    vector<long long> t;       // 2*n elements

    explicit SegTree(int sz = 0) { init(sz); }

    void init(int sz) {
        n = 1;
        while (n < sz) n <<= 1;
        t.assign(2 * n, INF);
    }

    // build from whole array a[0..sz-1]
    void build(const vector<long long> &a) {
        int sz = (int)a.size();
        for (int i = 0; i < sz; ++i) t[n + i] = a[i];
        for (int i = n - 1; i > 0; --i)
            t[i] = min(t[i << 1], t[i << 1 | 1]);
    }

    // query minimum on [l, r] inclusive
    long long query(int l, int r) const {
        if (l > r) return INF;
        l += n; r += n;
        long long res = INF;
        while (l <= r) {
            if (l & 1) res = min(res, t[l++]);
            if (!(r & 1)) res = min(res, t[r--]);
            l >>= 1; r >>= 1;
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    /* ----- read first line (unknown count) ----- */
    string line;
    if (!getline(cin, line)) return 0;
    stringstream ss(line);
    vector<int> B;
    int x;
    while (ss >> x) B.push_back(x);

    int C;
    if (!(cin >> C)) return 0;

    int N = (int)B.size();
    int maxB = 0;
    for (int v : B) maxB = max(maxB, v);
    int MAXH = maxB + (N - 1) * C;          // safe upper bound

    vector<long long> dpPrev(MAXH + 1, INF), dpCurr(MAXH + 1, INF);

    /* ----- first plant ----- */
    for (int h = B[0]; h <= MAXH; ++h)
        dpPrev[h] = h - B[0];

    /* ----- remaining plants ----- */
    for (int i = 1; i < N; ++i) {
        SegTree seg(MAXH + 1);
        seg.build(dpPrev);
        fill(dpCurr.begin(), dpCurr.end(), INF);

        for (int h = B[i]; h <= MAXH; ++h) {
            int L = max(0, h - C);
            int R = min(MAXH, h + C);
            long long best = seg.query(L, R);
            if (best != INF)
                dpCurr[h] = (h - B[i]) + best;
        }
        dpPrev.swap(dpCurr);
    }

    long long answer = INF;
    for (long long v : dpPrev) answer = min(answer, v);
    cout << answer << '\n';
    return 0;
}
