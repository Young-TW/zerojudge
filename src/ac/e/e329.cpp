// e329. NOIP2018 摆渡车 — n 人於 t_i 到站,車往返一趟 m 分鐘,任意安排發車時刻,最小化總等待。
//
// DP:dp[t] = 「最後一班車在時刻 t 發車、且所有 t_i≤t 的人都已送走」的最小總等待。
//   一班車在 t 發車,服務上一班發車(prev)之後到 t 為止到站的人,各等 (t - t_i)。
//   Σ_{prev<t_i≤t}(t-t_i) = (t·C[t]-S[t]) - (t·C[prev]-S[prev]),C=前綴人數,S=前綴到站時刻和。
//   關鍵引理:相鄰兩班發車間隔可 WLOG <2m(否則中間插一班空車不增等待且維持間隔≥m),
//   故 prev ∈ [t-2m+1, t-m](窗寬 m)。另 dp[t] 亦可為「本班即首班,送走所有 ≤t」= t·C[t]-S[t]。
//   時間 O(maxT·m),用滾動陣列(存最近 2m 個時刻的 dp/C/S)→ 記憶體 O(m)。答案 = dp[maxT]。
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    bool first = true;
    while (cin >> n >> m) {
        if (!first) cout << "\n";                // 案間空一行(對齊官方 1.out:0\n\n4),末案無尾空行
        first = false;
        vector<int> t(n);
        int maxT = 0;
        for (int i = 0; i < n; ++i) { cin >> t[i]; maxT = max(maxT, t[i]); }
        sort(t.begin(), t.end());

        const long long INF = (long long)4e18;
        int W = 2 * m + 1;                       // 滾動窗大小(需覆蓋 prev∈[t-2m+1,t-m])
        vector<long long> rdp(W), rS(W);
        vector<long long> rC(W);
        // 初始化為「不可用」
        for (int i = 0; i < W; ++i) { rdp[i] = INF; rC[i] = 0; rS[i] = 0; }

        long long C = 0, S = 0;                  // 目前 C[t], S[t]
        int idx = 0;                             // 已納入的到站人數指標
        long long ans = INF;

        // 迴圈需延伸過 maxT:最後一班車可能被 m 間隔強制發在 maxT 之後(前一班太晚)。
        // 上界 maxT+n·m 足夠(至多 n 班、各間隔 m)。答案取 t≥maxT 的 dp[t] 最小值(此時全員已可服務)。
        long long LIM = (long long)maxT + (long long)n * m + 1;
        for (long long tt = 0; tt <= LIM; ++tt) {
            while (idx < n && t[idx] == tt) { C += 1; S += tt; ++idx; }
            long long ft = tt * C - S;                   // t·C[t]-S[t]
            long long best = ft;                         // 本班為首班,送走所有 ≤tt

            // 轉移:prev ∈ [tt-2m+1, tt-m]
            long long hi = tt - m;
            if (hi >= 0) {
                long long lo = tt - 2 * m + 1;
                if (lo < 0) lo = 0;
                for (long long prev = lo; prev <= hi; ++prev) {
                    int j = (int)(prev % W);
                    if (rdp[j] >= INF) continue;
                    long long cand = rdp[j] + ft - (tt * rC[j] - rS[j]);
                    if (cand < best) best = cand;
                }
            }

            int cj = (int)(tt % W);
            rdp[cj] = best; rC[cj] = C; rS[cj] = S;      // 記錄 dp[tt],C[tt],S[tt]
            if (tt >= maxT && best < ans) ans = best;    // 全員可服務後,取最小
        }
        cout << ans << "\n";
    }
    return 0;
}
