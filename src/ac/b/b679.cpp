#include <iostream>
#include <cstdint>

using int64 = long long;
using i128  = __int128_t;

// floor(sqrt(y)) for y >= 0, using 128‑bit arithmetic
static uint64_t isqrt(i128 y) {
    uint64_t lo = 0;
    uint64_t hi = (1ULL << 63);          // hi^2 > any possible y
    while (lo <= hi) {
        uint64_t mid = lo + (hi - lo) / 2;
        i128 sq = (i128)mid * (i128)mid;
        if (sq <= y) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return hi;                          // hi = floor(sqrt(y))
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint64_t X;
    while (std::cin >> X) {
        i128 D = (i128)1 + (i128)8 * (i128)X;   // D = 1 + 8X
        uint64_t s = isqrt(D);                 // s = sqrt(D) = 2H+1
        uint64_t H = (s - 1) / 2;
        std::cout << H << '\n';
    }
    return 0;
}
