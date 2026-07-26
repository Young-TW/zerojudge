#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    while (std::cin >> n) {
        for (int i = 0; i < n; ++i) {
            long long m, p;
            std::cin >> m >> p;
            long long diff = p - m;                     // profit (can be negative)

            // decision: dispose if profit rate >= 10% or <= -7%
            bool dispose = (diff * 100LL >= 10LL * m) ||
                           (diff * 100LL <= -7LL * m);

            // rounded profit rate (hundredths of percent)
            __int128 num = (__int128)diff * 10000;      // diff * 100 * 100
            long long q = static_cast<long long>(num / m);   // truncated toward 0
            long long r = static_cast<long long>(num % m);   // remainder, same sign as diff

            long long abs_r = r >= 0 ? r : -r;
            if (abs_r * 2LL >= m) {
                if (q >= 0) ++q;
                else        --q;
            }

            double x = q / 100.0;                       // now exactly rounded
            std::printf("%6.2f%% %s\n", x, dispose ? "dispose" : "keep");
        }
    }
    return 0;
}
