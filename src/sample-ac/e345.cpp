#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    unsigned int n;
    while (std::cin >> n) {
        if (n == 0) {
            std::cout << 0 << '\n';
        } else {
            std::cout << 1 + (n - 1) % 9 << '\n';
        }
    }
    
    return 0;
}
