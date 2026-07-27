#include <iostream>
#include <cstdint>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long x1, y1, x2, y2, x3, y3;
    while (std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3) {
        // squared distances
        long long d12 = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
        long long d23 = (x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3);
        long long d31 = (x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1);

        long long xa, ya, xb, yb, xc, yc; // diagonal endpoints (xa,ya)-(xb,yb), other (xc,yc)

        if (d12 >= d23 && d12 >= d31) {          // 1-2 is diagonal
            xa = x1; ya = y1;
            xb = x2; yb = y2;
            xc = x3; yc = y3;
        } else if (d23 >= d12 && d23 >= d31) {   // 2-3 is diagonal
            xa = x2; ya = y2;
            xb = x3; yb = y3;
            xc = x1; yc = y1;
        } else {                                 // 3-1 is diagonal
            xa = x3; ya = y3;
            xb = x1; yb = y1;
            xc = x2; yc = y2;
        }

        long long xs = xa + xb - xc;
        long long ys = ya + yb - yc;
        std::cout << xs << ' ' << ys << '\n';
    }
    return 0;
}
