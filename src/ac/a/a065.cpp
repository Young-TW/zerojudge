#include <iostream>

int main() {
    char pw[7];
    std::cin >> pw;
    for (int i = 0; i < 6; i++) {
        std::cout << abs(pw[i] - pw[i + 1]);
    }

    return 0;
}