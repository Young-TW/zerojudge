#include <iostream>
#include <cstdint>
#include <limits>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long X, Y;
    while (std::cin >> X >> Y) {
        int N;
        if (!(std::cin >> N)) break;

        long long bestX = 0, bestY = 0;
        __int128 bestDist = -1;               // -1 means “not set yet”

        for (int i = 0; i < N; ++i) {
            long long x, y;
            std::cin >> x >> y;

            long long dx = x - X;
            long long dy = y - Y;
            __int128 dist = (__int128)dx * dx + (__int128)dy * dy;

            if (bestDist == -1 || dist < bestDist) {
                bestDist = dist;
                bestX = x;
                bestY = y;
            } else if (dist == bestDist) {
                if (x < bestX || (x == bestX && y < bestY)) {
                    bestX = x;
                    bestY = y;
                }
            }
        }

        std::cout << bestX << ' ' << bestY << '\n';
    }
    return 0;
}
