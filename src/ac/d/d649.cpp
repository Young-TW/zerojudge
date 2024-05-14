#include <iostream>

int main() {
    int n, m;
    while (std::cin >> n) {
        if (n == 0) break;
        for (int i = 0; i < n; i++) {
            m = n - i - 1;
            for (int a = 0; a < m; a++) {
                std::cout << "_";
            }
            for (int b = 0; b < i + 1; b++) {
                std::cout << "+";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    return 0;
}