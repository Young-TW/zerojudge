#include <iostream>

int main() {
    int n;
    while (std::cin >> n) {
        n = n * n - n + 2;
        std::cout << n << std::endl;
    }

    return 0;
}