#include <iostream>
#include <string>

int main() {
    std::string a, b, choice;
    while (std::getline(std::cin, a) && std::getline(std::cin, b) && std::getline(std::cin, choice)) {
        if (choice == "yes") {
            std::cout << a << "想和" << b << "絕交\n";
        } else {
            std::cout << a << "不想和" << b << "絕交\n";
        }
    }
    return 0;
}
