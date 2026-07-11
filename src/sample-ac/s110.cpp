#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <functional>
#include <map>
#include <set>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 5;
const int MAXA = 1e6 + 5;

vector<int> primes;
bool is_prime[MAXA];
int min_prime_factor[MAXA];
int prime_id[MAXA];
vector<int> factors[MAXA];

void sieve() {
    memset(is_prime, true, sizeof(is_prime));
    is_prime[0] = is_prime[1] = false;
    min_prime_factor[0] = min_prime_factor[1] = 1;
    for (int i = 2; i < MAXA; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            min_prime_factor[i] = i;
            prime_id[i] = primes.size() - 1;
        }
        for (int p : primes) {
            if (p > min_prime_factor[i] || i * p >= MAXA) break;
            is_prime[i * p] = false;
            min_prime_factor[i * p] = p;
        }
    }
    for (int i = 2; i < MAXA; ++i) {
        int x = i;
        while (x > 1) {
            int p = min_prime_factor[x];
            factors[i].push_back(prime_id[p]);
            while (x % p == 0) x /= p;
        }
    }
}

vector<int> adj[MAXN];
int parent[MAXN], depth[MAXN];
int heavy[MAXN], head[MAXN], pos[MAXN];
int cur_pos = 0;
int val[MAXN];

void dfs(int u) {
    int max_size = 0;
    heavy[u] = -1;
    for (int v : adj[u]) {
        if (v == parent[u]) continue;
        parent[v] = u;
        depth[v] = depth[u] + 1;
        dfs(v);
        if (max_size < (int)adj[v].size()) {
            max_size = adj[v].size();
            heavy[u] = v;
        }
    }
}

void decompose(int u, int h) {
    head[u] = h;
    pos[u] = cur_pos++;
    if (heavy[u] != -1) {
        decompose(heavy[u], h);
    }
    for (int v : adj[u]) {
        if (v == parent[u] || v == heavy[u]) continue;
        decompose(v, v);
    }
}

struct Node {
    vector<int> primes;
    Node() {}
    Node(int x) {
        for (int p : factors[x]) {
            primes.push_back(p);
        }
    }
};

Node tree[4 * MAXN];
bool has_prime[4 * MAXN][64];

Node merge(const Node& a, const Node& b) {
    Node res;
    int i = 0, j = 0;
    while (i < a.primes.size() && j < b.primes.size()) {
        if (a.primes[i] < b.primes[j]) {
            res.primes.push_back(a.primes[i]);
            i++;
        } else if (a.primes[i] > b.primes[j]) {
            res.primes.push_back(b.primes[j]);
            j++;
        } else {
            res.primes.push_back(a.primes[i]);
            i++;
            j++;
        }
    }
    while (i < a.primes.size()) {
        res.primes.push_back(a.primes[i]);
        i++;
    }
    while (j < b.primes.size()) {
        res.primes.push_back(b.primes[j]);
        j++;
    }
    return res;
}

void build(int node, int l, int r) {
    if (l == r) {
        tree[node] = Node(val[l]);
        memset(has_prime[node], false, sizeof(has_prime[node]));
        for (int p : tree[node].primes) {
            has_prime[node][p] = true;
        }
        return;
    }
    int mid = (l + r) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    for (int i = 0; i < 64; ++i) {
        has_prime[node][i] = has_prime[2 * node][i] || has_prime[2 * node + 1][i];
    }
}

Node query(int node, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) {
        return Node();
    }
    if (ql <= l && r <= qr) {
        return tree[node];
    }
    int mid = (l + r) / 2;
    Node left = query(2 * node, l, mid, ql, qr);
    Node right = query(2 * node + 1, mid + 1, r, ql, qr);
    return merge(left, right);
}

long long query_path(int u, int v) {
    Node res;
    while (head[u] != head[v]) {
        if (depth[head[u]] > depth[head[v]]) {
            swap(u, v);
        }
        Node cur = query(1, 0, cur_pos - 1, pos[head[v]], pos[v]);
        res = merge(res, cur);
        v = parent[head[v]];
    }
    if (depth[u] > depth[v]) {
        swap(u, v);
    }
    Node cur = query(1, 0, cur_pos - 1, pos[u], pos[v]);
    res = merge(res, cur);
    long long ans = 1;
    for (int p : res.primes) {
        ans = (ans * primes[p]) % MOD;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve();

    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> val[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    parent[1] = 0;
    depth[1] = 0;
    dfs(1);
    decompose(1, 1);

    for (int i = 1; i <= n; ++i) {
        val[pos[i]] = val[i];
    }
    build(1, 0, cur_pos - 1);

    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << query_path(u, v) << '\n';
    }

    return 0;
}
