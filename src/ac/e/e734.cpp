// e734 - The Power Monitor System (2019 ICPC Asia Taipei-Hsinchu Regional)
// Minimum Power Dominating Set on a TREE.
//
// A PMU observes its node and all neighbours (domination). Then propagation
// (zero forcing): an observed node with exactly one unobserved neighbour forces
// that neighbour to become observed. Key fact: every observed node can force at
// most ONE neighbour over the whole process.
//
// Tree DP.  For the subtree rooted at v (all internal propagation applied) we
// track three states describing what v offers to / needs from its parent:
//   dp[v][0]: v is UNOBSERVED and waits for the parent to force it (the still
//             unobserved part of the subtree forms a single downward chain).
//   dp[v][1]: whole subtree observed, v observed AND v still has a spare force
//             that can force the parent ("provides").
//   dp[v][2]: whole subtree observed, v observed but NO spare force ("neutral").
//
// Answer = min(dp[root][1], dp[root][2]).

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<vector<int>> adj(n + 1);
    for (int e = 0; e < n - 1; ++e) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    const int INF = 1e8;

    // iterative BFS from node 1 to get parent + processing order
    vector<int> parent(n + 1, 0), order;
    order.reserve(n);
    vector<char> vis(n + 1, 0);
    {
        queue<int> q;
        q.push(1);
        vis[1] = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            order.push_back(u);
            for (int w : adj[u]) if (!vis[w]) {
                vis[w] = 1;
                parent[w] = u;
                q.push(w);
            }
        }
    }

    vector<array<int, 3>> dp(n + 1);

    // process in reverse BFS order => children before parents
    for (int idx = (int)order.size() - 1; idx >= 0; --idx) {
        int v = order[idx];

        // gather children (neighbours except parent)
        // aggregate the quantities we need
        long long base2 = 0;          // sum of c2 over children (all children in state2)
        long long base12 = 0;         // sum of min(c1,c2)
        long long minAll3 = 0;        // sum of min(c0,c1,c2)  (for PMU option)
        bool hasChild = false;
        bool anyState1Free = false;   // some child with c1 <= c2
        long long minB_minusD = INF;  // min(c1 - c2)   (make one child state1)
        long long bestSwapTo0 = 0;    // min(0, min(c0 - c2))  (one child -> state0)

        // for z1_option in dp[v][2]: min over i!=j of (a_i - d_i) + (b_j - d_j)
        // where a=c0, b=c1, d=c2.
        // track two smallest A=c0-c2 and two smallest B=c1-c2 with indices.
        const long long BIG = INF;
        long long A1 = BIG, A2 = BIG; int A1i = -1;
        long long B1 = BIG, B2 = BIG; int B1i = -1;
        int childCount = 0;

        for (int w : adj[v]) {
            if (w == parent[v]) continue;
            hasChild = true;
            int c0 = dp[w][0], c1 = dp[w][1], c2 = dp[w][2];
            base2   += c2;
            base12  += min(c1, c2);
            minAll3 += min(c0, min(c1, c2));
            if (c1 <= c2) anyState1Free = true;
            minB_minusD = min(minB_minusD, (long long)c1 - c2);
            bestSwapTo0 = min(bestSwapTo0, (long long)c0 - c2);

            long long A = (long long)c0 - c2;
            long long B = (long long)c1 - c2;
            if (A < A1) { A2 = A1; A1 = A; A1i = childCount; }
            else if (A < A2) { A2 = A; }
            if (B < B1) { B2 = B1; B1 = B; B1i = childCount; }
            else if (B < B2) { B2 = B; }
            ++childCount;
        }

        // ---- PMU at v : always feasible, result state 1 ----
        long long pmu = minAll3 + 1;

        // ---- dp[v][0] : v unobserved, waits for parent ----
        // all children in state2, optionally ONE child in state0.
        long long s0 = base2 + min(0LL, bestSwapTo0);

        // ---- dp[v][1] : v observed WITH spare (no state0 child) ----
        long long noPmu1;
        if (!hasChild) {
            noPmu1 = INF;              // a leaf cannot observe itself without a PMU
        } else {
            long long ensure1 = anyState1Free ? 0 : minB_minusD;
            noPmu1 = base12 + ensure1;
        }
        long long s1 = min(pmu, noPmu1);

        // ---- dp[v][2] : v observed (spare may be spent) ----
        long long s2 = s1;            // state1 capability also satisfies state2
        if (childCount >= 2) {
            // one child state0 (A) + one different child state1 (B) + rest state2
            long long best = BIG;
            if (A1i != B1i) best = A1 + B1;
            else {
                if (A2 != BIG) best = min(best, A2 + B1);
                if (B2 != BIG) best = min(best, A1 + B2);
            }
            if (best < BIG) s2 = min(s2, base2 + best);
        }

        dp[v][0] = (int)min((long long)INF, s0);
        dp[v][1] = (int)min((long long)INF, s1);
        dp[v][2] = (int)min((long long)INF, s2);
    }

    cout << min(dp[1][1], dp[1][2]) << "\n";
    return 0;
}
