#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdint>
#include <climits>

using namespace std;

using ull = unsigned long long;

// shift src left by 'shift' bits and OR into dst
static void shift_or(const vector<ull>& src, vector<ull>& dst, int shift) {
    int wordShift = shift >> 6;          // divide by 64
    int bitShift  = shift & 63;          // remainder
    size_t n = src.size();

    if (bitShift == 0) {
        for (size_t i = 0; i + wordShift < n; ++i) {
            dst[i + wordShift] |= src[i];
        }
    } else {
        for (size_t i = 0; i + wordShift < n; ++i) {
            ull low = src[i] << bitShift;
            dst[i + wordShift] |= low;
            if (i + wordShift + 1 < n) {
                ull high = src[i] >> (64 - bitShift);
                dst[i + wordShift + 1] |= high;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m) {
        vector<int> w(n + 1);
        for (int i = 1; i <= n; ++i) cin >> w[i];

        vector<vector<int>> adj(n + 1);
        adj.reserve(n + 1);
        for (int i = 0; i < m; ++i) {
            int a, b; cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        vector<int> colour(n + 1, -1);
        vector<pair<int,int>> comps;          // (sum0 , sum1)
        bool ok = true;

        queue<int> q;
        for (int v = 1; v <= n && ok; ++v) {
            if (colour[v] != -1) continue;
            long long sum0 = 0, sum1 = 0;
            colour[v] = 0;
            q.push(v);
            while (!q.empty() && ok) {
                int u = q.front(); q.pop();
                if (colour[u] == 0) sum0 += w[u];
                else                sum1 += w[u];
                for (int nb : adj[u]) {
                    if (colour[nb] == -1) {
                        colour[nb] = colour[u] ^ 1;
                        q.push(nb);
                    } else if (colour[nb] == colour[u]) {
                        ok = false;
                        break;
                    }
                }
            }
            if (ok) comps.emplace_back((int)sum0, (int)sum1);
        }

        if (!ok) {
            cout << "Bye Bye Cruel World!\n";
            continue;
        }

        long long totalLL = 0;
        for (int i = 1; i <= n; ++i) totalLL += w[i];
        int total = (int)totalLL;                 // ≤ 6·10⁶ fits in int

        int bitsCnt = (total >> 6) + 1;
        vector<ull> dp(bitsCnt, 0), ndp(bitsCnt, 0);
        dp[0] = 1ULL;                             // sum 0 reachable

        for (auto &pr : comps) {
            int a = pr.first;
            int b = pr.second;
            fill(ndp.begin(), ndp.end(), 0ULL);
            shift_or(dp, ndp, a);
            shift_or(dp, ndp, b);
            dp.swap(ndp);
        }

        int best = 0;
        int bestDiff = INT_MAX;
        for (int s = 0; s <= total; ++s) {
            if (dp[s >> 6] & (1ULL << (s & 63))) {
                int diff = abs(2 * s - total);
                if (diff < bestDiff) {
                    bestDiff = diff;
                    best = s;
                }
            }
        }

        long long X = best;
        long long Y = totalLL - best;
        if (X > Y) swap(X, Y);
        cout << X << ' ' << Y << '\n';
    }
    return 0;
}
