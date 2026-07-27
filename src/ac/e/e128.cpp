#include <iostream>
#include <cmath>
#include <cstdint>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    long long N;
    while (std::cin >> N) {
        if (N == 0) break;

        // smallest k with k^2 >= N
        long long k = static_cast<long long>(std::sqrt(static_cast<double>(N)));
        while (k * k < N) ++k;          // ceil
        while ((k - 1) * (k - 1) >= N) --k; // safety

        long long prev = (k - 1) * (k - 1);
        long long pos = N - prev;       // 1 .. 2k-1

        long long x, y;
        if (pos == k) {
            x = k; y = k;
        } else if (pos < k) {
            if (k & 1) {                // k odd
                x = k; y = pos;
            } else {                    // k even
                x = pos; y = k;
            }
        } else { // pos > k
            if (k & 1) {                // k odd
                x = 2 * k - pos;
                y = k;
            } else {                    // k even
                x = k;
                y = 2 * k - pos;
            }
        }
        std::cout << x << ' ' << y << '\n';
    }
    return 0;
}
