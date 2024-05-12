#include <iostream>

void check(bool a, bool b, bool c) {
    bool or_g = 0, and_g = 0, xor_g = 0, flag = 0;
    if (a || b) or_g = 1;
    if (a && b) and_g = 1;
    if (a != b) xor_g = 1;

    if (c == and_g) {
        std::cout << "AND" << std::endl;
        flag = 1;
    }

    if (c == or_g) {
        std::cout << "OR" << std::endl;
        flag = 1;
    }

    if (c == xor_g) {
        std::cout << "XOR" << std::endl;
        flag = 1;
    }

    if (!flag) std::cout << "IMPOSSIBLE" << std::endl;
    return;
}

int main() {
    int a, b, c;
    std::cin >> a >> b >> c;
    bool a1, b1, c1;
    a1 = bool(a);
    b1 = bool(b);
    c1 = bool(c);
    check(a1, b1, c1);
    return 0;
}