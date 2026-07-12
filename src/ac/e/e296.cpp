#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const long long MOD = 998244353;

vector<vector<int>> adj;
vector<long long> subtree_size;
vector<long long> edge_contribution;
int n, m;

void dfs(int u, int p) {
    subtree_size[u] = 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        subtree_size[u] += subtree_size[v];
        long long count = (long long)subtree_size[v] * (n - subtree_size[v]);
        edge_contribution.push_back(count % MOD);
    }
}

void solve() {
    cin >> n >> m;
    adj.assign(n + 1, vector<int>());
    subtree_size.assign(n + 1, 0);
    edge_contribution.clear();

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<long long> costs(m);
    for (int i = 0; i < m; ++i) {
        cin >> costs[i];
    }

    dfs(1, -1);

    sort(edge_contribution.begin(), edge_contribution.end(), greater<long long>());
    sort(costs.begin(), costs.end(), greater<long long>());

    long long total_sum = 0;
    
    // Assign largest costs to edges with smallest contributions? 
    // No, we want to minimize sum(cost * contribution).
    // So we should assign largest costs to SMALLEST contributions.
    // And smallest costs (or 0) to LARGEST contributions.
    
    // We have m costs to assign to m distinct edges.
    // The remaining (n-1-m) edges will have cost 0.
    // To minimize the sum, we should pick the m edges with the SMALLEST contributions
    // and assign the given costs to them.
    // Furthermore, among these m edges, we should assign the LARGEST cost to the SMALLEST contribution,
    // the second largest cost to the second smallest contribution, etc. (Rearrangement inequality).
    
    // So:
    // 1. Sort all edge contributions in ascending order.
    // 2. Take the first m (smallest) contributions.
    // 3. Sort costs in descending order.
    // 4. Multiply corresponding pairs.
    
    // Let's re-sort edge_contribution in ascending order
    sort(edge_contribution.begin(), edge_contribution.end());
    
    // Costs are currently sorted descending. That's what we want for the smallest contributions.
    // edge_contribution[0] is smallest, costs[0] is largest -> product is minimized relative to other pairings?
    // Wait. Sum = c1*x1 + c2*x2. If c1 > c2 and x1 < x2.
    // Option A: c1*x1 + c2*x2
    // Option B: c1*x2 + c2*x1
    // A - B = c1(x1-x2) + c2(x2-x1) = (c1-c2)(x1-x2).
    // Since c1>c2 (pos) and x1<x2 (neg), A-B is negative. So A < B.
    // Yes, largest cost with smallest contribution is correct.
    
    long long ans = 0;
    for (int i = 0; i < m; ++i) {
        long long term = (edge_contribution[i] % MOD) * (costs[i] % MOD);
        term %= MOD;
        ans = (ans + term) % MOD;
    }

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
