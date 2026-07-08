#include <iostream>
#include <string>

int main() {
    std::string a;
    while (std::getline(std::cin, a)) {
        if (!a.empty() && a.back() == '\r') a.pop_back();
        for (char c : a) {
            std::cout << char(c - 7);
        }
        std::cout << "\r\n";
    }
    return 0;
}

