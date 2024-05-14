#include <iostream>

int main() {
    int n, reg, max = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> reg;
        if (reg > max) {
            max = reg;
        }
    }
    std::cout << max;
    return 0;
}