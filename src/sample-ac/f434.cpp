#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string line;
    while (std::getline(std::cin, line)) {
        for (char &c : line) {
            c -= 7;
        }
        std::cout << line << "\n";
    }
    
    return 0;
}
