#include <iostream>

int main() {
    int a, b, x;
    std::cin >> a >> b;
    bool c;
    c = a % 2 == 1 && b % 2 == 1;
    x = (b - a) / 2 + 1 - c;
    std::cout << x;
    return 0;
}