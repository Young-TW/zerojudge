#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long N, L, R;
    while (std::cin >> N >> L >> R) {
        const long long len = R - L + 1;
        std::vector<long long> f(len);
        std::vector<int> h(len, 0); // h[v - L] for v in [L, R-1]

        long long base = 0;

        // Iterate over intervals where floor(N/x) is constant
        for (long long x = 1, q, R_q; x <= N; x = R_q + 1) {
            q = N / x;
            R_q = N / q;
            const long long L_q = x;

            // Contribution to base = f(L)
            long long max_x = (L - 1) / q; // floor((L-1)/q)
            if (max_x >= L_q) {
                long long cnt = std::min(R_q, max_x) - L_q + 1;
                if (cnt > 0) base += cnt;
            }

            // Fill h for v in [L, R-1]
            long long x_min = (L + q - 1) / q;     // ceil(L/q)
            long long x_max = (R - 1) / q;         // floor((R-1)/q)
            if (x_min < L_q) x_min = L_q;
            if (x_max > R_q) x_max = R_q;
            if (x_min <= x_max) {
                for (long long xx = x_min; xx <= x_max; ++xx) {
                    long long v = q * xx; // v = T_x
                    h[static_cast<size_t>(v - L)]++;
                }
            }
        }

        f[0] = base;
        for (long long i = L + 1; i <= R; ++i) {
            f[static_cast<size_t>(i - L)] = f[static_cast<size_t>(i - L - 1)] + h[static_cast<size_t>(i - 1 - L)];
        }

        for (size_t i = 0; i < f.size(); ++i) {
            if (i) std::cout << ' ';
            std::cout << f[i];
        }
        std::cout << '\n';
    }
    return 0;
}
