#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <utility>

using namespace std;

struct Event {
    int l, r;
    long long v;
};

class SegTree {
public:
    struct Node {
        priority_queue<long long> add, del;
        inline void add_val(long long x) { add.push(x); }
        inline void del_val(long long x) { del.push(x); }
        inline long long get_max() {
            while (!del.empty() && !add.empty() && del.top() == add.top()) {
                del.pop();
                add.pop();
            }
            return add.empty() ? LLONG_MIN : add.top();
        }
    };
private:
    int n;
    vector<Node> tree;
public:
    SegTree(int n) : n(n), tree(4 * n + 5) {}
    void update(int node, int l, int r, int ql, int qr, long long val, bool is_add) {
        if (ql <= l && r <= qr) {
            if (is_add) tree[node].add_val(val);
            else tree[node].del_val(val);
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid) update(node << 1, l, mid, ql, qr, val, is_add);
        if (qr > mid) update((node << 1) | 1, mid + 1, r, ql, qr, val, is_add);
    }
    long long query(int pos) {
        long long res = LLONG_MIN;
        int node = 1, l = 1, r = n;
        while (true) {
            long long cur = tree[node].get_max();
            if (cur != LLONG_MIN && cur > res) res = cur;
            if (l == r) break;
            int mid = (l + r) >> 1;
            if (pos <= mid) {
                node = node << 1;
                r = mid;
            } else {
                node = (node << 1) | 1;
                l = mid + 1;
            }
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    while (cin >> N >> M) {
        vector<long long> a(N + 1);
        vector<long long> vals;
        vals.reserve(N);
        for (int i = 1; i <= N; ++i) {
            cin >> a[i];
            vals.push_back(a[i]);
        }
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        int V = vals.size();
        vector<vector<int>> pos_lists(V);
        for (int i = 1; i <= N; ++i) {
            int id = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
            pos_lists[id].push_back(i);
        }
        vector<int> prev(N + 2, 0), next(N + 2, N + 1);
        for (int id = 0; id < V; ++id) {
            const auto& vec = pos_lists[id];
            int sz = vec.size();
            for (int j = 0; j < sz; ++j) {
                int idx = vec[j];
                if (j > 0) prev[idx] = vec[j - 1];
                else prev[idx] = 0;
                if (j < sz - 1) next[idx] = vec[j + 1];
                else next[idx] = N + 1;
            }
        }
        vector<vector<Event>> add_events(N + 2), remove_events(N + 2);
        for (int i = 1; i <= N; ++i) {
            int L = prev[i] + 1;
            int R = next[i] - 1;
            if (L <= i && i <= R) {
                add_events[L].push_back({i, R, a[i]});
                remove_events[i + 1].push_back({i, R, a[i]});
            }
        }
        vector<vector<pair<int, int>>> queries(N + 1);
        for (int i = 0; i < M; ++i) {
            int l, r;
            cin >> l >> r;
            if (l > r) swap(l, r);
            queries[l].emplace_back(r, i);
        }
        SegTree seg(N);
        vector<long long> ans(M, LLONG_MIN);
        for (int l = 1; l <= N; ++l) {
            for (const auto& e : add_events[l]) {
                seg.update(1, 1, N, e.l, e.r, e.v, true);
            }
            for (const auto& e : remove_events[l]) {
                seg.update(1, 1, N, e.l, e.r, e.v, false);
            }
            for (const auto& q : queries[l]) {
                long long res = seg.query(q.first);
                ans[q.second] = res;
            }
        }
        for (int i = 0; i < M; ++i) {
            if (ans[i] == LLONG_MIN) cout << 0 << '\n';
            else cout << ans[i] << '\n';
        }
    }
    return 0;
}
