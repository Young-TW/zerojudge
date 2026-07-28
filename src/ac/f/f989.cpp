#include <bits/stdc++.h>
using namespace std;

struct FenwickND {
    int n;                              // number of dimensions
    vector<int> m;                      // size of each dimension (1‑based)
    vector<int> stride;                 // stride for linear index
    vector<int> bit;                    // 1‑dimensional storage

    FenwickND() {}
    FenwickND(const vector<int>& dims) { init(dims); }

    void init(const vector<int>& dims) {
        n = (int)dims.size();
        m = dims;
        stride.assign(n, 0);
        stride[0] = 1;
        for (int i = 1; i < n; ++i)
            stride[i] = stride[i - 1] * (m[i - 1] + 1);
        long long total = (long long)stride[n - 1] * (m[n - 1] + 1);
        bit.assign((size_t)total, 0);
    }

    // internal recursive update
    void updateRec(int dim, int idx, const vector<int>& coord, int delta) {
        if (dim == n) {
            bit[idx] += delta;
            return;
        }
        for (int i = coord[dim]; i <= m[dim]; i += i & -i) {
            updateRec(dim + 1, idx + i * stride[dim], coord, delta);
        }
    }

    // public update: coord are 1‑based
    void add(const vector<int>& coord, int delta) {
        updateRec(0, 0, coord, delta);
    }

    // internal recursive prefix sum
    int queryRec(int dim, int idx, const vector<int>& coord) const {
        if (dim == n) return bit[idx];
        int sum = 0;
        for (int i = coord[dim]; i > 0; i -= i & -i) {
            sum += queryRec(dim + 1, idx + i * stride[dim], coord);
        }
        return sum;
    }

    // prefix sum over [1..coord] (coord may contain zeros)
    int prefixSum(const vector<int>& coord) const {
        for (int v : coord) if (v == 0) return 0;
        return queryRec(0, 0, coord);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n, q;
        cin >> n >> q;
        vector<int> m(n);
        for (int i = 0; i < n; ++i) cin >> m[i];

        // Fenwick tree
        FenwickND ft(m);

        // state array: linear index (0‑based) of the cell itself
        long long totalCells = 1;
        for (int i = 0; i < n; ++i) totalCells *= m[i];
        vector<char> state((size_t)totalCells, 0);

        // helper: linear index of a coordinate (1‑based) in the state array
        auto linearIndex = [&](const vector<int>& coord) -> size_t {
            size_t idx = 0;
            for (int i = 0; i < n; ++i) {
                idx = idx * (size_t)m[i] + (size_t)(coord[i] - 1);
            }
            return idx;
        };

        for (int qq = 0; qq < q; ++qq) {
            int type;
            cin >> type;
            if (type == 1) {
                vector<int> x(n);
                for (int i = 0; i < n; ++i) cin >> x[i];
                size_t lin = linearIndex(x);
                if (state[lin] == 0) {
                    state[lin] = 1;
                    ft.add(x, +1);
                } else {
                    state[lin] = 0;
                    ft.add(x, -1);
                }
            } else { // type == 2
                vector<int> l(n), r(n);
                for (int i = 0; i < n; ++i) cin >> l[i];
                for (int i = 0; i < n; ++i) cin >> r[i];
                long long ans = 0;
                int masks = 1 << n;
                vector<int> point(n);
                for (int mask = 0; mask < masks; ++mask) {
                    for (int d = 0; d < n; ++d) {
                        if (mask & (1 << d))
                            point[d] = l[d] - 1;
                        else
                            point[d] = r[d];
                    }
                    int sign = (__builtin_popcount(mask) % 2 == 0) ? 1 : -1;
                    ans += sign * ft.prefixSum(point);
                }
                cout << ans << '\n';
            }
        }
    }
    return 0;
}
