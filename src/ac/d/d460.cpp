#include <iostream>

int main() {
    int n;
    std::cin >> n;
    std::cout << (n / 6 == 1) * 590 + (n / 6 == 2) * 790 +
                (n / 6 >= 3 && n / 6 <= 9) * 890 + (n / 6 >= 10) * 399;
    return 0;
}