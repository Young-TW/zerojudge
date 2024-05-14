#include <iostream>

int main() {
    int a, b;
    std::cin >> a >> b;
    if (a > b)
        std::cout << 100 + b - a;
    else
        std::cout << b - a;
    return 0;
}