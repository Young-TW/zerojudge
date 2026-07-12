#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string x, y;
    if (std::cin >> x >> y) {
        std::cout << y << " " << x << "\n";
    }
    
    return 0;
}
