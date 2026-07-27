// ZeroJudge a235 - APIO2009 抢掠计划
// SCC (Tarjan, 迭代) 縮點 -> DAG 上最長路 DP (Kahn 拓撲)
// 每個 SCC 內部可任意繞行，故 SCC 值 = 內部所有 ATM 金額和。
// 從起點所在 SCC 出發沿 DAG 前進，最終停在含酒吧的 SCC，求最大金額。
// 迭代式避免 N,M<=500000 時遞迴爆棧。複雜度 O(N+M)。
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, M;
    while (scanf("%d %d", &N, &M) == 2) {
        vector<vector<int>> adj(N + 1);
        vector<int> eu(M), ev(M);
        for (int i = 0; i < M; ++i) {
            scanf("%d %d", &eu[i], &ev[i]);
            adj[eu[i]].push_back(ev[i]);
        }
        vector<long long> atm(N + 1);
        for (int i = 1; i <= N; ++i) scanf("%lld", &atm[i]);
        int S, P;
        scanf("%d %d", &S, &P);
        vector<int> bars(P);
        for (int i = 0; i < P; ++i) scanf("%d", &bars[i]);

        // --- 迭代式 Tarjan SCC ---
        vector<int> dfn(N + 1, 0), low(N + 1, 0), comp(N + 1, -1);
        vector<char> onstk(N + 1, 0);
        vector<int> stk;              // Tarjan 棧
        vector<int> callStk, iterIdx; // 顯式遞迴棧: 節點 + 鄰接遍歷索引
        int idx = 0, sccCount = 0;
        stk.reserve(N);

        for (int s = 1; s <= N; ++s) {
            if (dfn[s]) continue;
            callStk.push_back(s);
            iterIdx.push_back(0);
            while (!callStk.empty()) {
                int u = callStk.back();
                int &ci = iterIdx.back();
                if (ci == 0) {
                    dfn[u] = low[u] = ++idx;
                    stk.push_back(u);
                    onstk[u] = 1;
                }
                bool pushed = false;
                while (ci < (int)adj[u].size()) {
                    int v = adj[u][ci++];
                    if (!dfn[v]) {
                        callStk.push_back(v);
                        iterIdx.push_back(0);
                        pushed = true;
                        break;
                    } else if (onstk[v]) {
                        if (dfn[v] < low[u]) low[u] = dfn[v];
                    }
                }
                if (pushed) continue;
                if (low[u] == dfn[u]) {
                    while (true) {
                        int w = stk.back(); stk.pop_back();
                        onstk[w] = 0;
                        comp[w] = sccCount;
                        if (w == u) break;
                    }
                    ++sccCount;
                }
                callStk.pop_back();
                iterIdx.pop_back();
                if (!callStk.empty()) {
                    int parent = callStk.back();
                    if (low[u] < low[parent]) low[parent] = low[u];
                }
            }
        }

        // --- SCC 值 + 縮點建圖 ---
        vector<long long> sccVal(sccCount, 0);
        for (int i = 1; i <= N; ++i) sccVal[comp[i]] += atm[i];
        vector<char> isBar(sccCount, 0);
        for (int b : bars) isBar[comp[b]] = 1;

        vector<vector<int>> dag(sccCount);
        vector<int> indeg(sccCount, 0);
        for (int i = 0; i < M; ++i) {
            int cu = comp[eu[i]], cv = comp[ev[i]];
            if (cu != cv) { dag[cu].push_back(cv); ++indeg[cv]; }
        }

        // --- Kahn 拓撲排序 + 最長路 DP ---
        const long long NEG = -1;
        vector<long long> dp(sccCount, NEG);
        dp[comp[S]] = sccVal[comp[S]];

        vector<int> q;
        q.reserve(sccCount);
        for (int c = 0; c < sccCount; ++c) if (indeg[c] == 0) q.push_back(c);
        for (size_t h = 0; h < q.size(); ++h) {
            int u = q[h];
            if (dp[u] != NEG) {
                for (int v : dag[u]) {
                    if (dp[u] + sccVal[v] > dp[v]) dp[v] = dp[u] + sccVal[v];
                }
            }
            for (int v : dag[u]) {
                if (--indeg[v] == 0) q.push_back(v);
            }
        }

        long long ans = 0;
        for (int c = 0; c < sccCount; ++c)
            if (isBar[c] && dp[c] != NEG && dp[c] > ans) ans = dp[c];
        printf("%lld\n", ans);
    }
    return 0;
}
