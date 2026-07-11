#include <iostream>
#include <string>

int main() {
    std::string word;
    while (std::cin >> word) {
        for (size_t i = 0; i < word.length(); ++i) {
            std::cout << word[i];
            if (i < word.length() - 1) {
                std::cout << '-';
            }
        }
        std::cout << '\n';
    }
    return 0;
}
