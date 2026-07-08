#include <iomanip>
#include <iostream>

int main() {
    double h, w, ans;
    std::cin >> w >> h;
    ans = w / (h * h);
    std::cout << std::fixed << std::setprecision(1) << ans;
    return 0;
}
