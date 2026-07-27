#include <bits/stdc++.h>
using namespace std;

struct Node {
    int l, r;
    mutable long long v;
    bool operator<(Node const& o) const { return l < o.l; }
};

int N, M;
set<Node> odt;

/* split the interval so that an interval starts at pos.
   returns iterator to that interval (or odt.end() if pos > N) */
auto split(int pos) {
    if (pos > N) return odt.end();
    auto it = odt.lower_bound({pos, 0, 0});
    if (it != odt.end() && it->l == pos) return it;
    --it;
    int L = it->l, R = it->r;
    long long V = it->v;
    odt.erase(it);
    odt.insert({L, pos - 1, V});
    return odt.insert({pos, R, V}).first;
}

/* assign value v to [l, r] */
void assign_range(int l, int r, long long v) {
    auto itr = split(r + 1), itl = split(l);
    odt.erase(itl, itr);
    odt.insert({l, r, v});
}

/* add delta to [l, r] */
void add_range(int l, int r, long long delta) {
    auto itr = split(r + 1), itl = split(l);
    for (auto it = itl; it != itr; ++it) it->v += delta;
}

/* k-th smallest in [l, r] (1‑based) */
long long kth_smallest(int l, int r, int k) {
    vector<pair<long long, int>> vec;
    auto itr = split(r + 1), itl = split(l);
    for (auto it = itl; it != itr; ++it)
        vec.emplace_back(it->v, it->r - it->l + 1);
    sort(vec.begin(), vec.end(),
         [](const pair<long long, int>& a,
            const pair<long long, int>& b) { return a.first < b.first; });
    for (auto const& p : vec) {
        if (k <= p.second) return p.first;
        k -= p.second;
    }
    return -1; // never reached
}

/* fast modular exponentiation */
long long pow_mod(long long a, long long e, long long mod) {
    long long res = 1 % mod;
    a %= mod;
    while (e) {
        if (e & 1) res = (__int128)res * a % mod;
        a = (__int128)a * a % mod;
        e >>= 1;
    }
    return res;
}

/* sum of a[i]^x (mod mod) over [l, r] */
long long range_pow_sum(int l, int r, long long x, long long mod) {
    long long ans = 0;
    auto itr = split(r + 1), itl = split(l);
    for (auto it = itl; it != itr; ++it) {
        long long cnt = it->r - it->l + 1;
        long long term = pow_mod(it->v, x, mod);
        ans = (ans + (__int128)(cnt % mod) * term) % mod;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> N >> M) {
        odt.clear();
        for (int i = 1; i <= N; ++i) {
            long long val; cin >> val;
            odt.insert({i, i, val});
        }
        for (int i = 0; i < M; ++i) {
            int op; cin >> op;
            if (op == 1) {
                int L, R; long long V; cin >> L >> R >> V;
                add_range(L, R, V);
            } else if (op == 2) {
                int L, R; long long V; cin >> L >> R >> V;
                assign_range(L, R, V);
            } else if (op == 3) {
                int L, R, K; cin >> L >> R >> K;
                cout << kth_smallest(L, R, K) << '\n';
            } else if (op == 4) {
                int L, R; long long X, MOD; cin >> L >> R >> X >> MOD;
                cout << range_pow_sum(L, R, X, MOD) << '\n';
            }
        }
    }
    return 0;
}
