#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, m, k, x;
    while (cin >> n >> m >> k >> x) {
        vector<int> g(n);
        for (long long i = 0; i < n; ++i) cin >> g[i];

        long long maxHealth = m;          // current maximum health
        long long level = 1;              // current level
        long long need = level * k;       // experience needed for next level

        long long curExp = 0;             // accumulated experience for this level
        long long curCost = 0;            // accumulated health loss for this level
        priority_queue<int, vector<int>, greater<int>> minHeap; // smallest weight on top

        for (long long i = 0; i < n; ++i) {
            int w = g[i];
            minHeap.push(w);
            curExp += w;
            curCost += 1LL * w * w;

            // Remove smallest weights while we still satisfy the experience requirement
            while (!minHeap.empty() && curExp - minHeap.top() >= need) {
                int t = minHeap.top();
                minHeap.pop();
                curExp -= t;
                curCost -= 1LL * t * t;
            }

            // If we can level up now, do it
            if (curExp >= need && curCost <= maxHealth) {
                ++level;
                maxHealth += x;
                need = level * k;
                // reset for the next level
                while (!minHeap.empty()) minHeap.pop();
                curExp = 0;
                curCost = 0;
            }
        }
        cout << level << '\n';
    }
    return 0;
}
