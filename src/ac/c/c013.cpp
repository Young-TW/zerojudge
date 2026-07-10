#include <iostream>

int main() {
    int n;
    std::cin >> n;
    bool first = true;
    for (int t = 0; t < n; t++) {
        int a, f;
        std::cin >> a >> f;
        for (int w = 0; w < f; w++) {
            if (!first) std::cout << '\n';
            first = false;
            for (int k = 1; k <= a; k++) {
                for (int i = 0; i < k; i++) std::cout << k;
                std::cout << '\n';
            }
            for (int k = a - 1; k >= 1; k--) {
                for (int i = 0; i < k; i++) std::cout << k;
                std::cout << '\n';
            }
        }
    }
    return 0;
}

// 00488 - Triangle Wave
