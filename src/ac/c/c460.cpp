#include <iostream>
#include <cstdint>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long N;
    while (std::cin >> N) {
        // cnt[race][mask], race = 1..3, mask = 0..7
        long long cnt[4][8] = {};   // initialise to zero

        for (long long i = 0; i < N; ++i) {
            int c, a, r, d;
            std::cin >> c >> a >> r >> d;
            int mask = (a << 2) | (r << 1) | d;   // 0 .. 7
            ++cnt[c][mask];
        }

        long long ans = 0;
        for (int m1 = 0; m1 < 8; ++m1) if (cnt[1][m1])
            for (int m2 = 0; m2 < 8; ++m2) if (cnt[2][m2])
                for (int m3 = 0; m3 < 8; ++m3) if (cnt[3][m3]) {
                    if ( (m1 | m2 | m3) == 7 )
                        ans += cnt[1][m1] * cnt[2][m2] * cnt[3][m3];
                }

        std::cout << ans << '\n';
    }
    return 0;
}
