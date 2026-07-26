#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll NEG_INF = LLONG_MIN / 4;          // safe negative infinity

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        vector<int> out(n + 1, 0);
        vector<int> wout(n + 1, 0);
        vector<int> indeg(n + 1, 0);
        for (int i = 0; i < m; ++i) {
            int a, b, w;
            cin >> a >> b >> w;
            out[a] = b;
            wout[a] = w;
            ++indeg[b];
        }

        vector<char> removed(n + 1, 0);
        vector<ll> bestSuf(n + 1, NEG_INF);   // best non‑empty suffix ending in v
        vector<ll> bestPath(n + 1, NEG_INF);  // best sub‑path inside processed part
        queue<int> q;
        for (int v = 1; v <= n; ++v)
            if (indeg[v] == 0) q.push(v);

        ll answer = NEG_INF;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            removed[u] = 1;
            int v = out[u];
            if (v == 0) continue;

            ll cand1 = (ll)wout[u];                     // start exactly at u
            ll cand2 = (bestSuf[u] == NEG_INF) ? NEG_INF : bestSuf[u] + wout[u];
            ll newSuf = max(cand1, cand2);               // best suffix ending in v
            bestSuf[v] = newSuf;                         // unique predecessor

            ll newPath = max(bestPath[u], newSuf);
            bestPath[v] = newPath;
            answer = max(answer, newPath);

            if (--indeg[v] == 0) q.push(v);
        }

        // ----- process remaining cycles -----
        vector<char> visCycle(n + 1, 0);
        for (int start = 1; start <= n; ++start) {
            if (removed[start] || visCycle[start]) continue;
            // collect one directed cycle
            vector<int> cyc;
            int cur = start;
            while (!visCycle[cur]) {
                visCycle[cur] = 1;
                cyc.push_back(cur);
                cur = out[cur];
            }

            int L = (int)cyc.size();
            if (L == 0) continue;

            // arrays for the cycle
            vector<ll> w(L);
            vector<ll> p(L);
            for (int i = 0; i < L; ++i) {
                int v = cyc[i];
                w[i] = wout[v];
                ll bs = bestSuf[v];
                p[i] = max(0LL, bs == NEG_INF ? 0LL : bs);
            }

            // prefix sums of doubled array
            vector<ll> pref(2 * L + 1, 0);
            for (int i = 1; i <= 2 * L; ++i)
                pref[i] = pref[i - 1] + w[(i - 1) % L];

            deque<int> dq;
            // initialise window for i = 0  (indices 1 .. L)
            for (int k = 1; k <= L; ++k) {
                while (!dq.empty() && pref[dq.back()] <= pref[k]) dq.pop_back();
                dq.push_back(k);
            }

            for (int i = 0; i < L; ++i) {
                while (!dq.empty() && dq.front() <= i) dq.pop_front();
                ll bestPref = pref[dq.front()];
                ll cand = (p[i] - pref[i]) + bestPref;
                answer = max(answer, cand);

                int newIdx = i + L + 1;
                if (newIdx <= 2 * L) {
                    while (!dq.empty() && pref[dq.back()] <= pref[newIdx]) dq.pop_back();
                    dq.push_back(newIdx);
                }
            }
        }

        cout << answer << '\n';
    }
    return 0;
}
