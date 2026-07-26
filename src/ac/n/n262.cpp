#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n_ll, m_ll;
    while (cin >> n_ll >> m_ll) {
        int n = static_cast<int>(n_ll);
        int m = static_cast<int>(m_ll);

        /* ---------- 1. reconstruct wallet ---------- */
        int cnt1000 = n / 1000;
        int r = n % 1000;

        int cnt500 = (r >= 500) ? 1 : 0;
        r -= cnt500 * 500;

        int cnt100 = min(4, r / 100);
        r -= cnt100 * 100;

        int cnt50 = (r >= 50) ? 1 : 0;
        r -= cnt50 * 50;

        int cnt10 = min(4, r / 10);
        r -= cnt10 * 10;

        int cnt5 = (r >= 5) ? 1 : 0;
        r -= cnt5 * 5;

        int cnt1 = r;                 // 0 .. 4

        int original = cnt1 + cnt5 + cnt10 + cnt50 + cnt100 + cnt500 + cnt1000;

        /* ---------- 2. bounded knapsack (min pieces) ---------- */
        vector<int> dp(n + 1, INF);
        dp[0] = 0;

        struct Item { int value, count; };
        vector<Item> items = {
            {1, cnt1},
            {5, cnt5},
            {10, cnt10},
            {50, cnt50},
            {100, cnt100},
            {500, cnt500},
            {1000, cnt1000}
        };

        for (auto it : items) {
            int v = it.value;
            int c = it.count;
            int k = 1;
            while (c > 0) {
                int use = min(k, c);
                int w = use * v;
                for (int amt = n; amt >= w; --amt) {
                    if (dp[amt - w] + use < dp[amt])
                        dp[amt] = dp[amt - w] + use;
                }
                c -= use;
                k <<= 1;
            }
        }

        /* ---------- 3. evaluate every payable amount ---------- */
        int bestTotal = INF;
        int bestP = -1;
        const int denChange[7] = {1000, 500, 100, 50, 10, 5, 1};

        for (int p = m; p <= n; ++p) {
            if (dp[p] == INF) continue;          // cannot pay this amount
            int change = p - m;
            int changeCoins = 0;
            int tmp = change;
            for (int d : denChange) {
                changeCoins += tmp / d;
                tmp %= d;
            }
            int total = original - dp[p] + changeCoins;
            if (total < bestTotal || (total == bestTotal && p < bestP)) {
                bestTotal = total;
                bestP = p;
            }
        }

        cout << bestP << '\n';
    }
    return 0;
}
