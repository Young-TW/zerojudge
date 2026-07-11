#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct SegTree {
    int n;
    vector<long long> maxv, lazy;

    SegTree(int n = 0) { init(n); }

    void init(int n_) {
        n = n_;
        maxv.assign(4 * n + 4, 0);
        lazy.assign(4 * n + 4, 0);
    }

    void build(int node, int l, int r, const vector<long long>& arr) {
        if (l == r) {
            maxv[node] = arr[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(node << 1, l, mid, arr);
        build(node << 1 | 1, mid + 1, r, arr);
        maxv[node] = max(maxv[node << 1], maxv[node << 1 | 1]);
    }

    void build(const vector<long long>& arr) {
        build(1, 1, n, arr);
    }

    void push(int node) {
        if (lazy[node] != 0) {
            maxv[node << 1]     += lazy[node];
            lazy[node << 1]     += lazy[node];
            maxv[node << 1 | 1] += lazy[node];
            lazy[node << 1 | 1] += lazy[node];
            lazy[node] = 0;
        }
    }

    void range_add(int node, int l, int r, int ql, int qr, long long val) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            maxv[node] += val;
            lazy[node] += val;
            return;
        }
        push(node);
        int mid = (l + r) >> 1;
        range_add(node << 1, l, mid, ql, qr, val);
        range_add(node << 1 | 1, mid + 1, r, ql, qr, val);
        maxv[node] = max(maxv[node << 1], maxv[node << 1 | 1]);
    }

    void range_add(int l, int r, long long val) {
        if (l > r) return;
        range_add(1, 1, n, l, r, val);
    }

    long long range_max(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return LLONG_MIN;
        if (ql <= l && r <= qr) return maxv[node];
        push(node);
        int mid = (l + r) >> 1;
        return max(range_max(node << 1, l, mid, ql, qr),
                   range_max(node << 1 | 1, mid + 1, r, ql, qr));
    }

    long long range_max(int l, int r) {
        if (l > r) return LLONG_MIN;
        return range_max(1, 1, n, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int N, M, K;
        cin >> N >> M >> K;
        vector<long long> A(N + 1);
        for (int i = 1; i <= N; ++i) cin >> A[i];

        int n = N - K + 1;                 // size of S array
        vector<long long> S(n + 1);        // 1-indexed
        vector<long long> pref(N + 1, 0);
        for (int i = 1; i <= N; ++i) pref[i] = pref[i - 1] + A[i];
        for (int i = 1; i <= n; ++i) {
            S[i] = pref[i + K - 1] - pref[i - 1];
        }

        SegTree st(n);
        st.build(S);

        for (int q = 0; q < M; ++q) {
            int type;
            cin >> type;
            if (type == 1) {
                int l, r;
                long long d;
                cin >> l >> r >> d;

                int fullL = l;
                int fullR = r - K + 1;
                if (fullL <= fullR) {
                    // full cover: add K*d
                    st.range_add(fullL, fullR, (long long)K * d);

                    // left partial
                    int leftL = max(1, l - K + 1);
                    int leftR = l - 1;
                    for (int i = leftL; i <= leftR; ++i) {
                        long long overlap = i + K - l;
                        st.range_add(i, i, d * overlap);
                    }

                    // right partial
                    int rightL = r - K + 2;
                    int rightR = min(n, r);
                    for (int i = rightL; i <= rightR; ++i) {
                        long long overlap = r - i + 1;
                        st.range_add(i, i, d * overlap);
                    }
                } else {
                    // update length < K, no full cover
                    int L = max(1, l - K + 1);
                    int R = min(n, r);
                    for (int i = L; i <= R; ++i) {
                        long long overlap = min(i + K - 1, r) - max(i, l) + 1;
                        if (overlap > 0) {
                            st.range_add(i, i, d * overlap);
                        }
                    }
                }
            } else if (type == 2) {
                int l, r;
                cin >> l >> r;
                if (r - l + 1 < K) {
                    cout << 0 << '\n';
                } else {
                    int ql = l;
                    int qr = r - K + 1;
                    long long ans = st.range_max(ql, qr);
                    cout << ans << '\n';
                }
            }
        }
    }
    return 0;
}
