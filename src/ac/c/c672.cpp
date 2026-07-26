#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string token;
    while (std::cin >> token) {
        if (!token.empty() && token[0] == '#') {
            // HEX -> RGB
            unsigned int r = std::stoi(token.substr(1, 2), nullptr, 16);
            unsigned int g = std::stoi(token.substr(3, 2), nullptr, 16);
            unsigned int b = std::stoi(token.substr(5, 2), nullptr, 16);
            std::cout << r << ' ' << g << ' ' << b << '\n';
        } else {
            // RGB -> HEX
            int r = std::stoi(token);
            int g, b;
            std::cin >> g >> b;

            std::cout << '#'
                      << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << r
                      << std::setw(2) << std::setfill('0') << g
                      << std::setw(2) << std::setfill('0') << b
                      << std::dec << std::nouppercase << '\n';
        }
    }
    return 0;
}
