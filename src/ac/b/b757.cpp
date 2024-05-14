#include <iostream>

int main() {
    double r;
    while (std::cin >> r) {
        r *= 9;
        r /= 5;
        r += 32;
        std::cout << r << std::endl;
    }
    return 0;
}