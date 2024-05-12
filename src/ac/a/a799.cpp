#include <iostream>

int main() {
    int n;
    std::cin >> n;
    if (n < 0) {
        n = -n;
    }

    std::cout << n;
    return 0;
}