#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

long long modpow(long long a, long long e) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N) {
        vector<int> P(N);
        for (int i = 0; i < N; ++i) cin >> P[i];

        // pre‑compute factorials
        vector<long long> fact(N + 1), invfact(N + 1);
        fact[0] = 1;
        for (int i = 1; i <= N; ++i) fact[i] = fact[i - 1] * i % MOD;
        invfact[N] = modpow(fact[N], MOD - 2);
        for (int i = N; i > 0; --i) invfact[i - 1] = invfact[i] * i % MOD;

        auto C = [&](int n, int k) -> long long {
            if (k < 0 || k > n) return 0;
            return fact[n] * invfact[k] % MOD * invfact[n - k] % MOD;
        };

        struct Node {
            int key;
            int left = -1, right = -1;
        };
        vector<Node> nodes;
        nodes.reserve(N);
        int root = -1;

        // build BST according to insertion order P
        for (int x : P) {
            if (root == -1) {
                nodes.push_back({x, -1, -1});
                root = 0;
                continue;
            }
            int cur = root;
            while (true) {
                if (x < nodes[cur].key) {
                    if (nodes[cur].left == -1) {
                        nodes.push_back({x, -1, -1});
                        nodes[cur].left = (int)nodes.size() - 1;
                        break;
                    } else cur = nodes[cur].left;
                } else { // x > key, all keys are distinct
                    if (nodes[cur].right == -1) {
                        nodes.push_back({x, -1, -1});
                        nodes[cur].right = (int)nodes.size() - 1;
                        break;
                    } else cur = nodes[cur].right;
                }
            }
        }

        // DFS to compute answer
        function<pair<int,long long>(int)> dfs = [&](int u) -> pair<int,long long> {
            if (u == -1) return {0, 1LL};
            auto left = dfs(nodes[u].left);
            auto right = dfs(nodes[u].right);
            int szL = left.first;
            int szR = right.first;
            long long ways = left.second * right.second % MOD;
            ways = ways * C(szL + szR, szL) % MOD;
            return {szL + szR + 1, ways};
        };

        long long answer = dfs(root).second % MOD;
        cout << answer << "\n";
    }
    return 0;
}
