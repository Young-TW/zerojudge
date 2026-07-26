#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N) {
        int words = (N + 63) >> 6;                 // ceil(N/64)
        vector<vector<unsigned long long>> adj(N, vector<unsigned long long>(words, 0ULL));

        for (int i = 0; i < N; ++i) {
            int m;  cin >> m;
            for (int t = 0; t < m; ++t) {
                int v;  cin >> v;
                --v;                                 // to 0‑based
                adj[i][v >> 6] |= 1ULL << (v & 63);
            }
        }

        long long ans = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                bool common = false;
                for (int w = 0; w < words; ++w) {
                    if (adj[i][w] & adj[j][w]) {
                        common = true;
                        break;
                    }
                }
                if (common) ++ans;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
