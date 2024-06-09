#include <iostream>

int a, b;

int gcd(int a, int b) {
    while (b > 0) {
        if (a > b) {
            a = a % b;
        } else {
            std::swap(a, b);
        }
    }

    return a;
}

int main() {
    std::cin >> a >> b;
    std::cout << gcd(a, b);
    return 0;
}