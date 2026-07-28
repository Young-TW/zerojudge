#include <iostream>
#include <algorithm>
#include <cmath>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int R, G, B;
    while (std::cin >> R >> G >> B) {
        double r = R / 255.0;
        double g = G / 255.0;
        double b = B / 255.0;

        double mx = std::max(r, std::max(g, b));
        double mn = std::min(r, std::min(g, b));
        double L = (mx + mn) / 2.0;

        double H, S;
        if (mx == mn) {
            H = 0.0;
            S = 0.0;
        } else {
            double delta = mx - mn;

            // hue
            if (mx == r) {
                H = 60.0 * (g - b) / delta;
                if (H < 0.0) H += 360.0;
            } else if (mx == g) {
                H = 60.0 * (b - r) / delta + 120.0;
            } else { // mx == b
                H = 60.0 * (r - g) / delta + 240.0;
            }

            // saturation
            if (L <= 0.5)
                S = delta / (2.0 * L);
            else
                S = delta / (2.0 - 2.0 * L);
        }

        int outH = static_cast<int>(std::round(H));
        if (outH == 360) outH = 0;          // keep hue in [0,359]
        int outS = static_cast<int>(std::round(S * 255.0));
        int outL = static_cast<int>(std::round(L * 255.0));

        std::cout << outH << ' ' << outS << ' ' << outL << '\n';
    }
    return 0;
}
