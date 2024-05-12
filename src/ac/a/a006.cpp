#include <cmath>
#include <iostream>

int main() {
    int a, b, c, x1, x2, f, g;
    while (std::cin >> a >> b >> c) {
        f = (b * b) - (4 * (a * c));
        g = sqrt(f);
        x1 = ((-b) + g) / (2 * a);
        x2 = ((-b) - g) / (2 * a);
        if (f > 0) {
            std::cout << "Two different roots x1=" << x1 << " , x2=" << x2
                      << std::endl;
        } else if (f == 0) {
            std::cout << "Two same roots x=" << x1 << std::endl;
        } else {
            std::cout << "No real root";
        }
    }

    return 0;
}