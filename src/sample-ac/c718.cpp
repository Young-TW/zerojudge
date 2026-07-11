#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstdint>
#include <utility>

using namespace std;

struct TreapNode {
    int left = 0, right = 0;
    uint32_t prio = 0;
    int h = 0;
    int id = 0;
    long long val = 0;
    long long sum = 0;
};

struct Edge {
    int u, v;
    int h;
    long long val;
};

vector<TreapNode> treap;
vector<int> seg_tree;
vector<int> parent, depth, heavy, head, pos, edge_id, edge_pos, sz;
vector<Edge> edges;
vector<vector<pair<int,int>>> adj;
int N, Q;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int new_treap_node(int h, int id, long long val) {
    treap.push_back({});
    int idx = treap.size() - 1;
    treap[idx].prio = rng();
    treap[idx].h = h;
    treap[idx].id = id;
    treap[idx].val = val;
    treap[idx].sum = val;
    return idx;
}

inline void treap_pull(int idx) {
    if (idx == 0) return;
    treap[idx].sum = treap[idx].val;
    if (treap[idx].left) treap[idx].sum += treap[treap[idx].left].sum;
    if (treap[idx].right) treap[idx].sum += treap[treap[idx].right].sum;
}

int treap_insert(int root, int h, int id, long long val) {
    if (root == 0) return new_treap_node(h, id, val);
    if (h < treap[root].h || (h == treap[root].h && id < treap[root].id)) {
        treap[root].left = treap_insert(treap[root].left, h, id, val);
        if (treap[treap[root].left].prio > treap[root].prio) {
            int left = treap[root].left;
            treap[root].left = treap[left].right;
            treap[left].right = root;
            treap_pull(root);
            treap_pull(left);
            return left;
        }
    } else {
        treap[root].right = treap_insert(treap[root].right, h, id, val);
        if (treap[treap[root].right].prio > treap[root].prio) {
            int right = treap[root].right;
            treap[root].right = treap[right].left;
            treap[right].left = root;
            treap_pull(root);
            treap_pull(right);
            return right;
        }
    }
    treap_pull(root);
    return root;
}

int treap_erase(int root, int h, int id) {
    if (root == 0) return 0;
    if (h == treap[root].h && id == treap[root].id) {
        if (treap[root].left == 0 && treap[root].right == 0) {
            return 0;
        }
        if (treap[root].left == 0) {
            int right = treap[root].right;
            treap[root].right = treap[right].left;
            treap[right].left = root;
            treap_pull(root);
            treap[right].left = treap_erase(treap[right].left, h, id);
            treap_pull(right);
            return right;
        } else if (treap[root].right == 0) {
            int left = treap[root].left;
            treap[root].left = treap[left].right;
            treap[left].right = root;
            treap_pull(root);
            treap[left].right = treap_erase(treap[left].right, h, id);
            treap_pull(left);
            return left;
        } else {
            if (treap[treap[root].left].prio > treap[treap[root].right].prio) {
                int left = treap[root].left;
                treap[root].left = treap[left].right;
                treap[left].right = root;
                treap_pull(root);
                treap[left].right = treap_erase(treap[left].right, h, id);
                treap_pull(left);
                return left;
            } else {
                int right = treap[root].right;
                treap[root].right = treap[right].left;
                treap[right].left = root;
                treap_pull(root);
                treap[right].left = treap_erase(treap[right].left, h, id);
                treap_pull(right);
                return right;
            }
        }
    } else if (h < treap[root].h || (h == treap[root].h && id < treap[root].id)) {
        treap[root].left = treap_erase(treap[root].left, h, id);
    } else {
        treap[root].right = treap_erase(treap[root].right, h, id);
    }
    treap_pull(root);
    return root;
}

long long treap_query(int root, int d) {
    if (root == 0) return 0;
    if (treap[root].h > d) {
        long long res = treap[root].val;
        if (treap[root].right) res += treap[treap[root].right].sum;
        res += treap_query(treap[root].left, d);
        return res;
    } else {
        return treap_query(treap[root].right, d);
    }
}

void seg_update(int node, int l, int r, int pos, int h, int id, long long val, bool insert) {
    if (insert) {
        seg_tree[node] = treap_insert(seg_tree[node], h, id, val);
    } else {
        seg_tree[node] = treap_erase(seg_tree[node], h, id);
    }
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (pos <= mid) seg_update(node<<1, l, mid, pos, h, id, val, insert);
    else seg_update(node<<1|1, mid+1, r, pos, h, id, val, insert);
}

long long seg_query(int node, int l, int r, int ql, int qr, int d) {
    if (ql <= l && r <= qr) {
        return treap_query(seg_tree[node], d);
    }
    int mid = (l + r) >> 1;
    long long res = 0;
    if (ql <= mid) res += seg_query(node<<1, l, mid, ql, qr, d);
    if (qr > mid) res += seg_query(node<<1|1, mid+1, r, ql, qr, d);
    return res;
}

long long query_path(int u, int v, int d) {
    long long res = 0;
    while (head[u] != head[v]) {
        if (depth[head[u]] < depth[head[v]]) swap(u, v);
        res += seg_query(1, 1, N, pos[head[u]], pos[u], d);
        u = parent[head[u]];
    }
    if (depth[u] > depth[v]) swap(u, v);
    if (u != v) {
        res += seg_query(1, 1, N, pos[u]+1, pos[v], d);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (cin >> N >> Q) {
        adj.assign(N+1, {});
        edges.resize(N);
        parent.assign(N+1, 0);
        depth.assign(N+1, 0);
        heavy.assign(N+1, -1);
        head.assign(N+1, 0);
        pos.assign(N+1, 0);
        edge_id.assign(N+1, 0);
        edge_pos.assign(N, 0);
        sz.assign(N+1, 0);
        
        for (int i = 1; i < N; i++) {
            int a, b, h, v;
            cin >> a >> b >> h >> v;
            edges[i] = {a, b, h, v};
            adj[a].push_back({b, i});
            adj[b].push_back({a, i});
        }
        
        vector<int> order;
        order.reserve(N);
        stack<int> st;
        st.push(1);
        parent[1] = 0;
        depth[1] = 0;
        while (!st.empty()) {
            int u = st.top(); st.pop();
            order.push_back(u);
            for (auto &e : adj[u]) {
                int v = e.first;
                int id = e.second;
                if (v == parent[u]) continue;
                parent[v] = u;
                depth[v] = depth[u] + 1;
                edge_id[v] = id;
                st.push(v);
            }
        }
        for (int i = N-1; i >= 0; i--) {
            int u = order[i];
            sz[u] = 1;
            heavy[u] = -1;
            for (auto &e : adj[u]) {
                int v = e.first;
                int id = e.second;
                if (v == parent[u]) continue;
                sz[u] += sz[v];
                if (heavy[u] == -1 || sz[v] > sz[heavy[u]]) {
                    heavy[u] = v;
                }
            }
        }
        
        int cur_pos = 0;
        stack<pair<int,int>> st2;
        st2.push({1, 1});
        while (!st2.empty()) {
            int u = st2.top().first;
            int h = st2.top().second;
            st2.pop();
            head[u] = h;
            pos[u] = ++cur_pos;
            if (u != 1) {
                edge_pos[edge_id[u]] = pos[u];
            }
            for (auto &e : adj[u]) {
                int v = e.first;
                int id = e.second;
                if (v == parent[u] || v == heavy[u]) continue;
                st2.push({v, v});
            }
            if (heavy[u] != -1) {
                st2.push({heavy[u], h});
            }
        }
        
        treap.clear();
        treap.push_back({});
        treap.reserve(4000000);
        seg_tree.assign(4*N + 5, 0);
        
        for (int i = 1; i < N; i++) {
            int p = edge_pos[i];
            seg_update(1, 1, N, p, edges[i].h, i, edges[i].val, true);
        }
        
        for (int i = 0; i < Q; i++) {
            int type;
            cin >> type;
            if (type == 0) {
                int S, T, d;
                cin >> S >> T >> d;
                cout << query_path(S, T, d) << '\n';
            } else {
                int x, h, v;
                cin >> x >> h >> v;
                int p = edge_pos[x];
                seg_update(1, 1, N, p, edges[x].h, x, edges[x].val, false);
                seg_update(1, 1, N, p, h, x, v, true);
                edges[x].h = h;
                edges[x].val = v;
            }
        }
    }
    return 0;
}
