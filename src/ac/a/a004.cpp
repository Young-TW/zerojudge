#include <iostream>

int main() {
    int x;
    while (std::cin >> x) {
        if ((x % 4 == 0 && x % 100 != 0) || x % 400 == 0) {
            std::cout << "閏年\n";
        } else {
            std::cout << "平年\n";
        }
    }

    return 0;
}