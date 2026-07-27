#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>

using namespace std;

struct Girl1 {
    int s;                 // required time
    long long v;           // goodwill
};

bool cmp_ratio(const Girl1& a, const Girl1& b) {
    // a.v / a.s  >  b.v / b.s   <=>   a.v * b.s > b.v * a.s
    return (__int128)a.v * b.s > (__int128)b.v * a.s;
}

/*  fractional value of type‑1 girls with capacity cap (0 ≤ cap ≤ T) */
long double fractional_value(const vector<Girl1>& g1,
                             const vector<long long>& prefS,
                             const vector<long double>& prefV,
                             int cap)
{
    int m = (int)g1.size();
    if (m == 0 || cap == 0) return 0.0L;

    int lo = 0, hi = m;                 // prefS[0]=0, prefS[m]=total
    while (lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if (prefS[mid] <= cap) lo = mid;
        else hi = mid - 1;
    }

    long double val = prefV[lo];
    long long used = prefS[lo];
    long long rest = cap - used;

    if (lo < m && rest > 0) {
        const Girl1& nxt = g1[lo];      // next girl (0‑based)
        val += (long double)rest * ((long double)nxt.v / nxt.s);
    }
    return val;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, T;
    while (cin >> n >> T) {
        vector<Girl1> type1;
        vector<pair<int, long long>> type2;   // (s , v)

        for (int i = 0; i < n; ++i) {
            int s, p;
            long long v;
            cin >> s >> v >> p;
            if (p == 1) {
                type1.push_back({s, v});
            } else {
                type2.emplace_back(s, v);
            }
        }

        /* ---------- type 1 : sort by decreasing v/s ---------- */
        sort(type1.begin(), type1.end(), cmp_ratio);
        int m = (int)type1.size();

        vector<long long> prefS(m + 1, 0);
        vector<long double> prefV(m + 1, 0.0L);
        for (int i = 1; i <= m; ++i) {
            prefS[i] = prefS[i - 1] + type1[i - 1].s;
            prefV[i] = prefV[i - 1] + (long double)type1[i - 1].v;
        }

        /* ---------- DP for type 2 (0/1 knapsack) ---------- */
        const long long NEG = std::numeric_limits<long long>::min() / 4;
        vector<long long> dp(T + 1, NEG);
        dp[0] = 0;

        for (auto &it : type2) {
            int s = it.first;
            long long v = it.second;
            for (int t = T; t >= s; --t) {
                if (dp[t - s] != NEG) {
                    long long cand = dp[t - s] + v;
                    if (cand > dp[t]) dp[t] = cand;
                }
            }
        }

        /* ---------- combine ---------- */
        long double best = 0.0L;
        for (int t = 0; t <= T; ++t) {
            if (dp[t] == NEG) continue;
            long double cur = (long double)dp[t] +
                              fractional_value(type1, prefS, prefV, T - t);
            if (cur > best) best = cur;
        }

        long long answer = llround(best);   // round to nearest integer
        cout << answer << '\n';
    }
    return 0;
}
