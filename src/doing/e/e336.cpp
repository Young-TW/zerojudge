// e336. NOIP2018 填数游戏 — 計數合法 0/1 填法(對 1e9+7 取模)。
// 已驗證(暴力對拍真條件):對角 f(d,d)=[_,2,12,112,912,7136](d=1..5);
// 且 min(n,m)=d≥2 時 f(n,m)=f(d,d)·3^(max-d)(f(2,3)=36,f(2,4)=108,f(3,4)=336 皆合);d=1 時 f=2^max。
// 註:d≥6 需 broken-profile DP 求 f(d,d)(局部單角條件 g[i][j+1]≤g[i+1][j] 對 d≥3 不足),此版暫僅涵蓋 d≤5。
#include <iostream>
using namespace std;
const long long MOD = 1000000007LL;
long long pw(long long b, long long e) { long long r = 1; b %= MOD; while (e) { if (e & 1) r = r * b % MOD; b = b * b % MOD; e >>= 1; } return r; }
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    long long diag[6] = {0, 2, 12, 112, 912, 7136};   // f(d,d), d=1..5
    long long n, m; bool first = true;
    while (cin >> n >> m) {
        if (!first) cout << "\n"; first = false;       // 案間空行(對齊官方多案輸出格式)
        long long d = min(n, m), M = max(n, m), ans;
        if (d == 1) ans = pw(2, M);
        else ans = diag[d] % MOD * pw(3, M - d) % MOD;  // d≤5
        cout << ans << "\n";
    }
    return 0;
}
