#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    while (cin >> N >> M) {
        vector<int> C(N + 1);
        for (int i = 1; i <= N; ++i) cin >> C[i];

        // pos[d] = indices i where C[i] is divisible by d
        vector<vector<int>> pos(N + 1);
        for (int i = 1; i <= N; ++i) {
            int v = C[i];
            int sq = (int)std::sqrt(v);
            for (int d = 1; d <= sq; ++d) {
                if (v % d == 0) {
                    pos[d].push_back(i);
                    int other = v / d;
                    if (other != d) pos[other].push_back(i);
                }
            }
        }

        // answer queries
        for (int q = 0; q < M; ++q) {
            int l, r, k;
            cin >> l >> r >> k;
            if (k > N) {
                cout << 0 << '\n';
                continue;
            }
            const vector<int> &vec = pos[k];
            auto itL = lower_bound(vec.begin(), vec.end(), l);
            auto itR = upper_bound(vec.begin(), vec.end(), r);
            cout << (itR - itL) << '\n';
        }
    }
    return 0;
}
