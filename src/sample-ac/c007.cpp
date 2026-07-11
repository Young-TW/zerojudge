#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    char c;
    bool left_quote = true;
    
    while (std::cin.get(c)) {
        if (c == '"') {
            if (left_quote) {
                std::cout << "``";
            } else {
                std::cout << "''";
            }
            left_quote = !left_quote;
        } else {
            std::cout << c;
        }
    }
    
    return 0;
}
