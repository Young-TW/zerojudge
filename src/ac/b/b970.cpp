#include <iostream>

int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cout << i + 1 << ". I don't say swear words!" << std::endl;
    }
    return 0;
}