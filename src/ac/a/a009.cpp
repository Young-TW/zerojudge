#include <iostream>

int main() {
    std::string a;
    while (std::getline(std::cin, a)) {
        for (int x = 0; x < a.length(); x++) {
            std::cout << char(a[x]-7);
        }

        std::cout << std::endl;
    }

    return 0;
}
