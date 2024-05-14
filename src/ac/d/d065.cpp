#include <iostream>

int main() {
    int a, b, c;
    std::cin >> a >> b >> c;
    std::cout << std::max(a, std::max(b, c));
    return 0;
}