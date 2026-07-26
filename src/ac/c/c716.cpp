#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string name;
    if (std::getline(std::cin, name)) {
        // Remove possible carriage return character (for Windows line endings)
        if (!name.empty() && name.back() == '\r') {
            name.pop_back();
        }
        std::cout << "Go, " << name << ", go go";
    }
    return 0;
}
