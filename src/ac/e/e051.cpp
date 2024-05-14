#include <iostream>
#include <string>

int main() {
    std::string str;
    std::cin >> str;
    std::cout << str.front();
    for (int i = 0; i < str.length() - 2; i++) {
        std::cout << '_';
    }
    std::cout << str.back();
    return 0;
}
