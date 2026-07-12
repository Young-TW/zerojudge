#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int MAXN = 3000000;

vector<int> fact, inv_fact;

int modpow(int a, int e) {
    long long res = 1, cur = a;
    while (e) {
        if (e & 1) res = res * cur % MOD;
        cur = cur * cur % MOD;
        e >>= 1;
    }
    return (int)res;
}

void init_fact(int n) {
    fact.resize(n + 1);
    inv_fact.resize(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) fact[i] = (long long)fact[i - 1] * i % MOD;
    inv_fact[n] = modpow(fact[n], MOD - 2);
    for (int i = n; i >= 1; --i) inv_fact[i - 1] = (long long)inv_fact[i] * i % MOD;
}

inline int C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return (long long)fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init_fact(MAXN);

    int N;
    while (cin >> N) {
        vector<int> pos(N + 1);
        for (int i = 1; i <= N; ++i) {
            int x; cin >> x;
            pos[x] = i;
        }

        vector<int> left(N + 1, 0), right(N + 1, 0);
        vector<int> stk(N + 1);
        int top = 0;
        for (int i = 1; i <= N; ++i) {
            int last = 0;
            while (top > 0 && pos[stk[top]] > pos[i]) {
                last = stk[top];
                --top;
            }
            if (top > 0) {
                right[stk[top]] = i;
            }
            if (last != 0) {
                left[i] = last;
            }
            stk[++top] = i;
        }
        int root = stk[1];

        vector<int> sz(N + 1, 0);
        vector<char> vis(N + 1, 0);
        vector<int> dfs_stk;
        dfs_stk.reserve(N);
        dfs_stk.push_back(root);
        while (!dfs_stk.empty()) {
            int u = dfs_stk.back();
            if (vis[u]) {
                dfs_stk.pop_back();
                sz[u] = 1;
                if (left[u]) sz[u] += sz[left[u]];
                if (right[u]) sz[u] += sz[right[u]];
            } else {
                vis[u] = 1;
                if (right[u]) dfs_stk.push_back(right[u]);
                if (left[u]) dfs_stk.push_back(left[u]);
            }
        }

        long long ans = 1;
        for (int i = 1; i <= N; ++i) {
            int l = left[i], r = right[i];
            int sz_l = l ? sz[l] : 0;
            int sz_r = r ? sz[r] : 0;
            ans = ans * C(sz_l + sz_r, sz_l) % MOD;
        }
        cout << ans << '\n';
    }
    return 0;
}
