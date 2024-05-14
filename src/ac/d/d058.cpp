#include <iostream>

int main() {
    int n;
    std::cin >> n;
    if (n > 0) {
        std::cout << "1";
    } else if (n == 0) {
        std::cout << "0";
    } else {
        std::cout << "-1";
    }
    return 0;
}