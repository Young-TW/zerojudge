#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        vector<int> w(n);
        for (int i = 0; i < n; ++i) cin >> w[i];

        if (n <= m) {
            int ans = 0;
            for (int x : w) ans = max(ans, x);
            cout << ans << '\n';
            continue;
        }

        // min‑heap of current finishing times
        priority_queue<long long, vector<long long>, greater<long long>> pq;
        for (int i = 0; i < m; ++i) pq.push(w[i]);

        for (int i = m; i < n; ++i) {
            long long t = pq.top(); pq.pop();   // earliest free tap
            t += w[i];                           // new finishing time
            pq.push(t);
        }

        long long answer = 0;
        while (!pq.empty()) {
            answer = max(answer, pq.top());
            pq.pop();
        }
        cout << answer << '\n';
    }
    return 0;
}
