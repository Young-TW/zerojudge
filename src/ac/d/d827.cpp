#include <iostream>

int main() {
    int n, m = 0;
    std::cin >> n;
    m += 5 * (n % 12);
    m += 50 * (n / 12);
    std::cout << m << std::endl;
    return 0;
}