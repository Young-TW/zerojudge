#include <iostream>

int main() {
    int f, l, n;
    std::cin >> f >> l >> n;
    for (int i=f; i<=l; i+=n) {
        std::cout << i << " ";
    }

    return 0;
}