#include <iostream>

int main() {
    int a, b, c;
    std::cin >> a >> b >> c;
    std::cout << ((a + b + c) / 2) * ((a + b + c) / 2 - a) * ((a + b + c) / 2 - b) *
                ((a + b + c) / 2 - c);
    return 0;
}