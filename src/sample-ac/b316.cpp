#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    long long K;
    while (cin >> N >> M >> K) {
        vector<vector<int>> adj(N);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<vector<int>> E(N);
        for (int i = 0; i < N; ++i) {
            for (int v : adj[i]) {
                if (v > i) {
                    E[i].push_back(v);
                }
            }
            sort(E[i].begin(), E[i].end());
        }

        vector<long long> cnt(N, 0);
        cnt[0] = K;

        for (int u = 0; u < N; ++u) {
            if (cnt[u] == 0) continue;
            int d = E[u].size();
            if (d == 0) continue;
            long long q = cnt[u] / d;
            long long r = cnt[u] % d;
            for (int j = 0; j < d; ++j) {
                int v = E[u][j];
                cnt[v] += q;
                if (j < r) {
                    cnt[v] += 1;
                }
            }
        }

        vector<int> last(N, -1);
        for (int u = N - 1; u >= 0; --u) {
            int d = E[u].size();
            if (d == 0) {
                last[u] = u;
            } else {
                if (cnt[u] > 0) {
                    long long idx = (cnt[u] - 1) % d;
                    int v = E[u][idx];
                    last[u] = last[v];
                } else {
                    last[u] = u;
                }
            }
        }

        cout << last[0] << "\n";
    }

    return 0;
}
