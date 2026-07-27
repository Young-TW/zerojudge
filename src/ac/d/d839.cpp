#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cstdint>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, p;
    while (cin >> n >> p) {
        vector<long long> initC(n + 1);
        vector<long long> U(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> initC[i] >> U[i];
        }

        vector<vector<pair<int, int>>> adj(n + 1);
        vector<int> indeg(n + 1, 0);
        vector<int> outdeg(n + 1, 0);
        for (int k = 0; k < p; ++k) {
            int i, j, w;
            cin >> i >> j >> w;
            adj[i].push_back({j, w});
            ++indeg[j];
            ++outdeg[i];
        }

        vector<__int128> sumIn(n + 1, 0);          // accumulated weighted inputs
        vector<long long> C(n + 1, 0);            // final states (non‑negative)

        queue<int> q;
        for (int i = 1; i <= n; ++i) {
            if (indeg[i] == 0) {
                C[i] = initC[i];                  // input neurons (may be 0)
                q.push(i);
            }
        }

        while (!q.empty()) {
            int v = q.front(); q.pop();

            for (auto &e : adj[v]) {
                int to = e.first;
                int w  = e.second;
                if (C[v] > 0) {
                    sumIn[to] += (__int128)C[v] * w;
                }
                --indeg[to];
                if (indeg[to] == 0) {
                    __int128 val = sumIn[to] - U[to];
                    C[to] = (val > 0) ? (long long)val : 0;
                    q.push(to);
                }
            }
        }

        bool any = false;
        for (int i = 1; i <= n; ++i) {
            if (outdeg[i] == 0 && C[i] > 0) {
                any = true;
                cout << i << ' ' << C[i] << '\n';
            }
        }
        if (!any) {
            cout << "NULL\n";
        }
    }
    return 0;
}
