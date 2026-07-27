#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstdint>
using namespace std;

struct Node {
    int l, r;
    uint64_t hash;
    Node() : l(0), r(0), hash(0) {}
    Node(int _l, int _r, uint64_t _h) : l(_l), r(_r), hash(_h) {}
};

vector<Node> seg;

int new_node() {
    seg.emplace_back(0, 0, 0);
    return (int)seg.size() - 1;
}

int update(int prev, int l, int r, int pos, uint64_t h) {
    int cur = new_node();
    seg[cur] = seg[prev];
    if (l == r) {
        seg[cur].hash ^= h;
        return cur;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) {
        seg[cur].l = update(seg[prev].l, l, mid, pos, h);
    } else {
        seg[cur].r = update(seg[prev].r, mid + 1, r, pos, h);
    }
    seg[cur].hash = seg[seg[cur].l].hash ^ seg[seg[cur].r].hash;
    return cur;
}

int query_max(int u, int v, int l, int r) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    uint64_t right_xor = seg[seg[u].r].hash ^ seg[seg[v].r].hash;
    if (right_xor != 0) {
        return query_max(seg[u].r, seg[v].r, mid + 1, r);
    } else {
        return query_max(seg[u].l, seg[v].l, l, mid);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, Q, O;
    while (cin >> N >> Q >> O) {
        vector<int> S(N + 1);
        for (int i = 1; i <= N; ++i) cin >> S[i];
        
        vector<int> vals(S.begin() + 1, S.end());
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        int M = (int)vals.size();
        
        vector<int> idx(N + 1);
        for (int i = 1; i <= N; ++i) {
            idx[i] = lower_bound(vals.begin(), vals.end(), S[i]) - vals.begin();
        }
        
        vector<uint64_t> hash_val(M);
        mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        for (int i = 0; i < M; ++i) {
            hash_val[i] = rng();
        }
        
        seg.clear();
        int max_nodes = N * 20 + 5;
        seg.reserve(max_nodes);
        seg.emplace_back(0, 0, 0);
        
        vector<int> root(N + 1);
        root[0] = 0;
        for (int i = 1; i <= N; ++i) {
            root[i] = update(root[i - 1], 0, M - 1, idx[i], hash_val[idx[i]]);
        }
        
        long long ans = 0;
        for (int qi = 0; qi < Q; ++qi) {
            long long l, r;
            cin >> l >> r;
            if (O == 1) {
                l = (l + ans) % N + 1;
                r = (r + ans) % N + 1;
            }
            int L = (int)l, R = (int)r;
            if (L > R) swap(L, R);
            uint64_t total_xor = seg[root[R]].hash ^ seg[root[L - 1]].hash;
            if (total_xor == 0) {
                ans = 0;
            } else {
                int id = query_max(root[R], root[L - 1], 0, M - 1);
                ans = vals[id];
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
