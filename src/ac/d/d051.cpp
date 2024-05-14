#include <iomanip>
#include <iostream>

int main() {
    double F, C;
    std::cin >> F;
    C = (F - 32) * 5 / 9;
    std::cout << std::fixed << std::setprecision(3) << C;
    return 0;
}