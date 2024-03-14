#include <iostream>

int main() {
    int n;
    std::cin >> n;
    if(n >= 40)
        std::cout << "100";
    else if(n <= 10)
        std::cout << 6 * n;
    else if(n <= 20)
        std::cout << 60 + ((n - 10) * 2);
    else if(n < 40)
        std::cout << 80 + (n - 20);
    return 0;
}