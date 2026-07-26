#include <iomanip>
#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    double w, h;
    while (std::cin >> w >> h) {
        double bmi = w / (h * h);
        std::cout << std::fixed << std::setprecision(1) << bmi << "\n";
    }

    return 0;
}
