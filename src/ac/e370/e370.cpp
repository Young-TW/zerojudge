// e370. 翻牌  (self-written)
//
// Model: each distinct value is a node; each card is an edge between its two
// values. Orienting a card toward a value = that value shown by the card.
// A value goes in the bag iff at least one card is oriented toward it.
// Score = sum of distinct values in the bag. Maximize.
//
// Total in-degree over a component = E (edges). Every node needs in-degree>=1
// to be collected. For a connected component with V nodes and E edges:
//   - E >= V  (has a cycle): can orient so every node has in-degree>=1
//             -> collect all V values -> add full sum.
//   - E == V-1 (tree): can collect at most V-1 nodes; leave out the minimum
//             value -> add (sum - min).
// A self-loop card (a==b) counts as an edge and always collects its value.
//
// Answer = sum over components. N up to 1e6, values up to 1e9.
#include <bits/stdc++.h>
using namespace std;

static int par[2000006];
static int rnk[2000006];

int find(int x) {
    while (par[x] != x) { par[x] = par[par[x]]; x = par[x]; }
    return x;
}
void uni(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return;
    if (rnk[a] < rnk[b]) swap(a, b);
    par[b] = a;
    if (rnk[a] == rnk[b]) rnk[a]++;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    vector<int> A(n), B(n);
    vector<int> vals;
    vals.reserve((size_t)n * 2);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &A[i], &B[i]);
        vals.push_back(A[i]);
        vals.push_back(B[i]);
    }

    // Coordinate compression via sort + unique (no map: keep constant small).
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int m = (int)vals.size();

    auto idx = [&](int v) -> int {
        return (int)(lower_bound(vals.begin(), vals.end(), v) - vals.begin());
    };
    vector<int> ia(n), ib(n);
    for (int i = 0; i < n; ++i) { ia[i] = idx(A[i]); ib[i] = idx(B[i]); }

    for (int i = 0; i < m; ++i) { par[i] = i; rnk[i] = 0; }
    for (int i = 0; i < n; ++i) uni(ia[i], ib[i]);

    // Per-component aggregates keyed by root.
    vector<long long> comp_sum(m, 0);
    vector<int> comp_nodes(m, 0);
    vector<int> comp_edges(m, 0);
    vector<int> comp_min(m, INT_MAX);

    for (int i = 0; i < m; ++i) {
        int r = find(i);
        comp_sum[r] += vals[i];
        comp_nodes[r]++;
        if (vals[i] < comp_min[r]) comp_min[r] = vals[i];
    }
    for (int i = 0; i < n; ++i) {
        comp_edges[find(ia[i])]++;   // ia,ib share a root; count the card once
    }

    long long ans = 0;
    for (int i = 0; i < m; ++i) {
        if (find(i) != i) continue;                 // only roots
        if (comp_edges[i] >= comp_nodes[i]) ans += comp_sum[i];   // cycle -> all
        else ans += comp_sum[i] - comp_min[i];                    // tree -> drop min
    }

    printf("%lld\n", ans);
    return 0;
}
