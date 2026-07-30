#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    while (cin >> m >> n) {
        uint32_t init = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int x;
                cin >> x;
                if (x) init |= (uint32_t(1) << (i * n + j));
            }
        }

        vector<uint32_t> ops;
        for (int r = 0; r + 2 < m; ++r) {
            for (int c = 0; c + 2 < n; ++c) {
                uint32_t mask = 0;
                for (int dr = 0; dr < 3; ++dr) {
                    for (int dc = 0; dc < 3; ++dc) {
                        mask |= (uint32_t(1) << ((r + dr) * n + (c + dc)));
                    }
                }
                ops.push_back(mask);
            }
        }

        int k = (int)ops.size();
        int total = 1 << k;
        int ans = k + 1;

        for (int mask = 0; mask < total; ++mask) {
            uint32_t state = init;
            for (int b = 0; b < k; ++b) {
                if (mask & (1 << b)) state ^= ops[b];
            }
            if (state == 0) {
                int pc = __builtin_popcount(mask);
                if (pc < ans) ans = pc;
            }
        }

        if (ans == k + 1) cout << -1 << '\n';
        else cout << ans << '\n';
    }

    return 0;
}
