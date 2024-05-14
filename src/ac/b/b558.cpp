#include <iostream>

int f(int i) {
    if (i == 1 || i == 0) {
        return 1;
    }
    return (i - 1 + f(i - 1));
}

int main() {
    int n;
    while (std::cin >> n) {
        std::cout << f(n) << std::endl;
    }
    return 0;
}