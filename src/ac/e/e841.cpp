#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

struct SegTree {
    int n;
    vector<long long> lazy;
    SegTree(int n_) : n(n_), lazy(4 * n_, 1) {}
    
    inline void update(int node, int l, int r, int ql, int qr, long long val) {
        if (ql <= l && r <= qr) {
            lazy[node] *= val;
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid) update(node << 1, l, mid, ql, qr, val);
        if (qr > mid) update(node << 1 | 1, mid + 1, r, ql, qr, val);
    }
    
    inline void collect(int node, int l, int r, long long cur, vector<long long>& res) {
        cur *= lazy[node];
        if (l == r) {
            res[l] = cur;
            return;
        }
        int mid = (l + r) >> 1;
        collect(node << 1, l, mid, cur, res);
        collect(node << 1 | 1, mid + 1, r, cur, res);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M) {
        vector<long long> diff(N + 2, 0);
        struct Mult { int l, r; long long s; };
        vector<Mult> mults;
        mults.reserve(M);
        
        for (int i = 0; i < M; ++i) {
            int P, Q, R;
            long long S;
            cin >> P >> Q >> R >> S;
            if (R == 1) {
                diff[P] += S;
                diff[Q + 1] -= S;
            } else {
                mults.push_back({P, Q, S});
            }
        }
        
        vector<long long> A(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            A[i] = A[i - 1] + diff[i];
        }
        
        vector<int> active;
        vector<long long> A_active;
        active.reserve(N);
        A_active.reserve(N);
        for (int i = 1; i <= N; ++i) {
            if (A[i] > 0) {
                active.push_back(i);
                A_active.push_back(A[i]);
            }
        }
        
        int K = active.size();
        if (K == 0) {
            cout << 1 << ' ' << 0 << '\n';
            continue;
        }
        
        SegTree st(K);
        for (const auto& m : mults) {
            auto itL = lower_bound(active.begin(), active.end(), m.l);
            auto itR = upper_bound(active.begin(), active.end(), m.r);
            if (itL == itR) continue;
            int L = itL - active.begin();
            int R = itR - active.begin() - 1;
            st.update(1, 0, K - 1, L, R, m.s);
        }
        
        vector<long long> B_active(K);
        st.collect(1, 0, K - 1, 1, B_active);
        
        long long max_val = -1;
        int best_idx = -1;
        for (int i = 0; i < K; ++i) {
            long long val = A_active[i] * B_active[i];
            if (val > max_val) {
                max_val = val;
                best_idx = active[i];
            }
        }
        cout << best_idx << ' ' << max_val << '\n';
    }
    return 0;
}
