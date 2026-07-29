#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <functional>
using namespace std;
typedef long long ll;
struct SegNode {
ll sum, max_sub, max_pref, max_suff;
SegNode() : sum(0), max_sub(0), max_pref(0), max_suff(0) {}
SegNode(ll val) : sum(val), max_sub(val), max_pref(val), max_suff(val) {}
};
SegNode merge(const SegNode &L, const SegNode &R) {
SegNode res;
res.sum = L.sum + R.sum;
res.max_pref = max(L.max_pref, L.sum + R.max_pref);
res.max_suff = max(R.max_suff, R.sum + L.max_suff);
res.max_sub = max({L.max_sub, R.max_sub, L.max_suff + R.max_pref});
return res;
}
class SegTree {
public:
int n;
vector<SegNode> tree;
SegTree(int _n) : n(_n), tree(4 * _n) {}
void build(int u, int l, int r, const vector<ll> &D) {
if (l == r) {
tree[u] = SegNode(D[l]);
return;
}
int mid = (l + r) / 2;
build(u*2, l, mid, D);
build(u*2+1, mid+1, r, D);
tree[u] = merge(tree[u*2], tree[u*2+1]);
}
void update(int u, int l, int r, int pos, ll val) {
if (l == r) {
tree[u] = SegNode(val);
return;
}
int mid = (l + r) / 2;
if (pos <= mid) update(u*2, l, mid, pos, val);
else update(u*2+1, mid+1, r, pos, val);
tree[u] = merge(tree[u*2], tree[u*2+1]);
}
SegNode query(int u, int l, int r, int ql, int qr) {
if (ql <= l && r <= qr) return tree[u];
int mid = (l + r) / 2;
if (qr <= mid) return query(u*2, l, mid, ql, qr);
if (ql > mid) return query(u*2+1, mid+1, r, ql, qr);
return merge(query(u*2, l, mid, ql, qr), query(u*2+1, mid+1, r, ql, qr));
}
void update(int pos, ll val) { update(1, 2, n, pos, val); }
ll query_sum(int l, int r) { return query(1, 2, n, l, r).sum; }
ll query_max_sub(int l, int r) { return query(1, 2, n, l, r).max_sub; }
};
struct Seg {
int L, R;
bool operator<(const Seg &o) const { return L < o.L; }
};
template<typename SetType>
typename SetType::iterator find_seg(int i, SetType &segs) {
auto it = segs.upper_bound({i, i});
if (it == segs.begin()) return segs.end();
--it;
if (it->L <= i && i <= it->R) return it;
return segs.end();
}
class Treap {
public:
Treap() : root(nullptr) {}
void insert(ll val) { insert(root, val); }
void erase(ll val) { erase(root, val); }
int query(ll need) { return query(root, need); }
ll total_sum() { return root ? root->sum : 0; }
private:
struct Node {
ll val;
int cnt, size;
ll sum;
int priority;
Node *left, *right;
Node(ll v) : val(v), cnt(1), size(1), sum(v), priority(rand()), left(nullptr), right(nullptr) {}
};
Node *root;
void upd(Node *u) {
if (!u) return;
u->size = u->cnt;
u->sum = u->cnt * u->val;
if (u->left) { u->size += u->left->size; u->sum += u->left->sum; }
if (u->right) { u->size += u->right->size; u->sum += u->right->sum; }
}
void rotate_right(Node *&u) {
Node *v = u->left;
u->left = v->right;
v->right = u;
upd(u); upd(v);
u = v;
}
void rotate_left(Node *&u) {
Node *v = u->right;
u->right = v->left;
v->left = u;
upd(u); upd(v);
u = v;
}
void insert(Node *&u, ll val) {
if (!u) { u = new Node(val); return; }
if (val == u->val) {
u->cnt++;
upd(u);
return;
}
if (val < u->val) {
insert(u->left, val);
if (u->left->priority > u->priority) rotate_right(u);
} else {
insert(u->right, val);
if (u->right->priority > u->priority) rotate_left(u);
}
upd(u);
}
void erase(Node *&u, ll val) {
if (!u) return;
if (val == u->val) {
if (u->cnt > 1) {
u->cnt--;
upd(u);
return;
}
if (!u->left && !u->right) {
delete u; u = nullptr; return;
}
if (!u->left || (u->right && u->right->priority > u->left->priority)) {
rotate_left(u);
erase(u->left, val);
} else {
rotate_right(u);
erase(u->right, val);
}
} else if (val < u->val) {
erase(u->left, val);
} else {
erase(u->right, val);
}
if (u) upd(u);
}
int query(Node *u, ll need) {
if (!u || need <= 0) return 0;
ll right_sum = u->right ? u->right->sum : 0;
if (right_sum >= need) return query(u->right, need);
int ans = u->right ? u->right->size : 0;
need -= right_sum;
ll root_contrib = u->val * u->cnt;
if (root_contrib >= need) {
ll need_cnt = (need + u->val - 1) / u->val;
ans += min((ll)u->cnt, need_cnt);
return ans;
}
ans += u->cnt;
need -= root_contrib;
ans += query(u->left, need);
return ans;
}
};
struct Op {
int type, l, r, c;
};
void solve_case(int n, int q, const vector<ll> &U, const vector<Op> &ops) {
if (n == 1) {
for (auto &op : ops) if (op.type == 1) cout << "0 0\n";
return;
}
vector<ll> D(n + 1);
for (int i = 2; i <= n; ++i) D[i] = U[i] - U[i - 1];
ll sum_pos = 0;
for (int i = 2; i <= n; ++i) sum_pos += max(0LL, D[i]);
SegTree T(n);
if (n >= 2) T.build(1, 2, n, D);
set<Seg> pos_segs, nonpos_segs;
for (int i = 2; i <= n; ) {
if (D[i] > 0) {
int j = i;
while (j <= n && D[j] > 0) ++j;
pos_segs.insert({i, j - 1});
i = j;
} else {
int j = i;
while (j <= n && D[j] <= 0) ++j;
nonpos_segs.insert({i, j - 1});
i = j;
}
}
auto is_gap = [&](int L, int R) -> bool {
if (L > R) return false;
if (L <= 2 || R >= n) return false;
return D[L - 1] > 0 && D[R + 1] > 0;
};
Treap treap;
auto add_gap = [&](int L, int R) {
if (L > R) return;
if (!is_gap(L, R)) return;
ll sum = T.query_sum(L, R);
ll max_sub = T.query_max_sub(L, R);
treap.insert(max_sub - sum);
};
auto remove_gap = [&](int L, int R) {
if (L > R) return;
if (!is_gap(L, R)) return;
ll sum = T.query_sum(L, R);
ll max_sub = T.query_max_sub(L, R);
treap.erase(max_sub - sum);
};
for (auto &seg : nonpos_segs)
if (is_gap(seg.L, seg.R))
add_gap(seg.L, seg.R);
auto update_D_point = [&](int i, ll new_val) {
ll old = D[i];
if (old == new_val) return;
if (old > 0 && new_val > 0) {
D[i] = new_val;
sum_pos += max(0LL, new_val) - max(0LL, old);
T.update(i, new_val);
return;
}
if (old <= 0 && new_val <= 0) {
auto it = find_seg(i, nonpos_segs);
if (it != nonpos_segs.end()) {
Seg seg = *it;
if (is_gap(seg.L, seg.R)) remove_gap(seg.L, seg.R);
}
D[i] = new_val;
sum_pos += max(0LL, new_val) - max(0LL, old);
T.update(i, new_val);
if (it != nonpos_segs.end()) {
Seg seg = *it;
if (is_gap(seg.L, seg.R)) add_gap(seg.L, seg.R);
}
return;
}
if (old > 0) {
auto it = find_seg(i, pos_segs);
if (it == pos_segs.end()) return;
Seg seg = *it;
if (i == seg.L && seg.L > 2 && D[seg.L - 1] <= 0) {
auto left_it = find_seg(seg.L - 1, nonpos_segs);
if (left_it != nonpos_segs.end() && is_gap(left_it->L, left_it->R))
remove_gap(left_it->L, left_it->R);
}
if (i == seg.R && seg.R < n && D[seg.R + 1] <= 0) {
auto right_it = find_seg(seg.R + 1, nonpos_segs);
if (right_it != nonpos_segs.end() && is_gap(right_it->L, right_it->R))
remove_gap(right_it->L, right_it->R);
}
D[i] = new_val;
sum_pos += max(0LL, new_val) - max(0LL, old);
T.update(i, new_val);
pos_segs.erase(it);
int L_non = i, R_non = i;
if (i == seg.L && seg.L > 2 && D[seg.L - 1] <= 0) {
auto left_it = find_seg(seg.L - 1, nonpos_segs);
if (left_it != nonpos_segs.end()) {
L_non = left_it->L;
nonpos_segs.erase(left_it);
}
}
if (i == seg.R && seg.R < n && D[seg.R + 1] <= 0) {
auto right_it = find_seg(seg.R + 1, nonpos_segs);
if (right_it != nonpos_segs.end()) {
R_non = right_it->R;
nonpos_segs.erase(right_it);
}
}
nonpos_segs.insert({L_non, R_non});
if (is_gap(L_non, R_non)) add_gap(L_non, R_non);
if (seg.L <= i - 1) pos_segs.insert({seg.L, i - 1});
if (i + 1 <= seg.R) pos_segs.insert({i + 1, seg.R});
} else {
auto it = find_seg(i, nonpos_segs);
if (it == nonpos_segs.end()) return;
Seg seg = *it;
if (is_gap(seg.L, seg.R)) remove_gap(seg.L, seg.R);
D[i] = new_val;
sum_pos += max(0LL, new_val) - max(0LL, old);
T.update(i, new_val);
nonpos_segs.erase(it);
int L_pos = i, R_pos = i;
if (i == seg.L && seg.L > 2 && D[seg.L - 1] > 0) {
auto left_it = find_seg(seg.L - 1, pos_segs);
if (left_it != pos_segs.end()) {
L_pos = left_it->L;
pos_segs.erase(left_it);
}
}
if (i == seg.R && seg.R < n && D[seg.R + 1] > 0) {
auto right_it = find_seg(seg.R + 1, pos_segs);
if (right_it != pos_segs.end()) {
R_pos = right_it->R;
pos_segs.erase(right_it);
}
}
pos_segs.insert({L_pos, R_pos});
if (seg.L <= i - 1) {
nonpos_segs.insert({seg.L, i - 1});
if (is_gap(seg.L, i - 1)) add_gap(seg.L, i - 1);
}
if (i + 1 <= seg.R) {
nonpos_segs.insert({i + 1, seg.R});
if (is_gap(i + 1, seg.R)) add_gap(i + 1, seg.R);
}
}
};
for (auto &op : ops) {
if (op.type == 0) {
int l = op.l, r = op.r, c = op.c;
if (l > 1) update_D_point(l, D[l] + c);
if (r < n) update_D_point(r + 1, D[r + 1] - c);
} else {
ll D_max = sum_pos;
if (D_max == 0) {
cout << "0 0\n";
} else {
ll total = treap.total_sum();
if (total < D_max) {
cout << D_max << " -1\n";
} else {
int X = treap.query(D_max);
cout << D_max << " " << X << "\n";
}
}
}
}
}
int main() {
ios::sync_with_stdio(false);
cin.tie(0);
srand(time(0));
int T;
cin >> T;
while (T--) {
int n, q;
cin >> n >> q;
vector<ll> U(n + 1);
for (int i = 1; i <= n; ++i) cin >> U[i];
vector<Op> ops(q);
for (int i = 0; i < q; ++i) {
int type; cin >> type;
if (type == 0) {
int l, r, c; cin >> l >> r >> c;
ops[i] = {0, l, r, c};
} else {
ops[i] = {1, 0, 0, 0};
}
}
solve_case(n, q, U, ops);
}
return 0;
}
