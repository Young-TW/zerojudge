#include <bits/stdc++.h>
using namespace std;

const int INF_NEG = -1000000000;          // -1e9, smaller than any possible answer

int N, M;
vector<int> children[1005];
int c[1005], dcost[1005];
int subtree_sum[1005];                    // Σ c[x] in the subtree

/*---------------------------------------------------------------*/
/*  first DFS : compute subtree_sum                               */
void dfs_sum(int u) {
    subtree_sum[u] = c[u];
    for (int v : children[u]) {
        dfs_sum(v);
        subtree_sum[u] += subtree_sum[v];
    }
}

/*---------------------------------------------------------------*/
/*  DP on a subtree, returns vector<int> of size M+1            */
vector<int> solve(int u) {
    // cur holds the best value using only children (no u yet)
    vector<int> cur(M + 1, INF_NEG);
    cur[0] = 0;

    for (int v : children[u]) {
        vector<int> child = solve(v);
        vector<int> nxt(M + 1, INF_NEG);
        for (int i = 0; i <= M; ++i) if (cur[i] > INF_NEG) {
            for (int j = 0; j + i <= M; ++j) if (child[j] > INF_NEG) {
                int w = i + j;
                int val = cur[i] + child[j];
                if (val > nxt[w]) nxt[w] = val;
            }
        }
        cur.swap(nxt);
    }

    // dp_u will store the final table for node u
    vector<int> dp_u(M + 1, INF_NEG);

    // 1) ignore u
    for (int w = 0; w <= M; ++w) dp_u[w] = cur[w];

    // 2) buy u individually
    if (c[u] <= M) {
        for (int w = M; w >= c[u]; --w) {
            if (cur[w - c[u]] > INF_NEG) {
                int val = cur[w - c[u]] + c[u];
                if (val > dp_u[w]) dp_u[w] = val;
            }
        }
    }

    // 3) buy whole subtree as a bundle
    if (dcost[u] <= M) {
        int w = dcost[u];
        if (subtree_sum[u] > dp_u[w]) dp_u[w] = subtree_sum[u];
    }

    return dp_u;
}

/*---------------------------------------------------------------*/
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> N >> M) {
        // clear previous data
        for (int i = 0; i < N; ++i) children[i].clear();

        vector<int> roots;
        for (int i = 0; i < N; ++i) {
            int p; cin >> p;
            if (p == -1) roots.push_back(i);
            else children[p].push_back(i);
        }
        for (int i = 0; i < N; ++i) cin >> c[i] >> dcost[i];

        // compute subtree sums
        for (int r : roots) dfs_sum(r);

        // global answer for the whole forest
        vector<int> ans(M + 1, INF_NEG);
        ans[0] = 0;

        for (int r : roots) {
            vector<int> dp_root = solve(r);
            vector<int> nxt(M + 1, INF_NEG);
            for (int i = 0; i <= M; ++i) if (ans[i] > INF_NEG) {
                for (int j = 0; j + i <= M; ++j) if (dp_root[j] > INF_NEG) {
                    int w = i + j;
                    int val = ans[i] + dp_root[j];
                    if (val > nxt[w]) nxt[w] = val;
                }
            }
            ans.swap(nxt);
        }

        int best = 0;
        for (int w = 0; w <= M; ++w) if (ans[w] > best) best = ans[w];
        cout << best << '\n';
    }
    return 0;
}
