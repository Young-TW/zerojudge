#include <iomanip>
#include <iostream>

int main() {
    double h, w, ans;
    std::cin >> w >> h;
    h = h / 100;
    h = h * h;
    ans = w / h;
    std::cout << std::fixed << std::setprecision(1) << ans;
    return 0;
}