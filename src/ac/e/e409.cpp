#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MaxN = 1000000 + 5;
const int MaxQ = 100000 + 5;
const int MaxTree = 2100000 + 5;
const int INF = 1000000000;

int A[MaxN];
bool C[MaxQ];
int X[MaxQ], Y[MaxQ];
int k, m, N, Q;

void gen_dat() {
    int i, j;
    for (i = k + 1; i <= max(Q, N); ++i)
        A[i] = (A[i - 2] * 97 + A[i - 1] * 3) % m + 1;
    for (i = 1, j = max(Q, N); i <= Q; ++i, --j) {
        C[i] = A[i] & 1;
        X[i] = (A[i] + A[j]) % N + 1;
        if (C[i]) Y[i] = X[i] + ((A[i] << 3) + (A[j] << 5) + m) % (N - X[i] + 1);
        else Y[i] = ((A[i] << 3) + (A[j] << 5)) % m + 1;
    }
}

int seg_max[MaxTree];
int seg_min[MaxTree];
int tree_n;

void build() {
    tree_n = 1;
    while (tree_n < N) tree_n <<= 1;
    
    for (int i = 1; i <= N; ++i) {
        seg_max[tree_n + i] = A[i];
        seg_min[tree_n + i] = A[i];
    }
    for (int i = tree_n + N + 1; i < 2 * tree_n; ++i) {
        seg_max[i] = 0;
        seg_min[i] = INF;
    }
    for (int i = tree_n - 1; i > 0; --i) {
        seg_max[i] = max(seg_max[i << 1], seg_max[i << 1 | 1]);
        seg_min[i] = min(seg_min[i << 1], seg_min[i << 1 | 1]);
    }
}

void update(int idx, int val) {
    idx += tree_n;
    seg_max[idx] = val;
    seg_min[idx] = val;
    for (idx >>= 1; idx > 0; idx >>= 1) {
        seg_max[idx] = max(seg_max[idx << 1], seg_max[idx << 1 | 1]);
        seg_min[idx] = min(seg_min[idx << 1], seg_min[idx << 1 | 1]);
    }
}

int query_max(int l, int r) {
    l += tree_n;
    r += tree_n;
    int res = 0;
    while (l <= r) {
        if (l & 1) res = max(res, seg_max[l++]);
        if (!(r & 1)) res = max(res, seg_max[r--]);
        l >>= 1;
        r >>= 1;
    }
    return res;
}

int query_min(int l, int r) {
    l += tree_n;
    r += tree_n;
    int res = INF;
    while (l <= r) {
        if (l & 1) res = min(res, seg_min[l++]);
        if (!(r & 1)) res = min(res, seg_min[r--]);
        l >>= 1;
        r >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while (cin >> k >> m) {
        for (int i = 1; i <= k; ++i) {
            cin >> A[i];
        }
        cin >> N >> Q;
        gen_dat();
        
        build();
        
        for (int i = 1; i <= Q; ++i) {
            if (C[i] == 0) {
                update(X[i], Y[i]);
            } else {
                int mx = query_max(X[i], Y[i]);
                int mn = query_min(X[i], Y[i]);
                cout << mx - mn << "\n";
            }
        }
    }
    
    return 0;
}
