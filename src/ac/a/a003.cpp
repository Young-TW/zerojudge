#include <iostream>

int main() {
    int m, d, s;
    std::cin >> m >> d;
    s = (m * 2 + d) % 3;
    if (s == 0) {
        std::cout << "普通";
    } else if (s == 1) {
        std::cout << "吉";
    } else if (s == 2) {
        std::cout << "大吉";
    }

    return 0;
}