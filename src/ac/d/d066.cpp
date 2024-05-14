#include <iostream>

int main() {
    int a, b;
    std::cin >> a >> b;
    a = (a * 60) + b;
    if (450 <= a && a < 1020) {
        std::cout << "At School";
    } else {
        std::cout << "Off School";
    }
    return 0;
}