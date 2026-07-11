#include <iostream>
#include <string>

int main() {
    std::string s;
    while (std::cin >> s) {
        if (s == "Sunday") {
            std::cout << 0 << std::endl;
        } else if (s == "Monday") {
            std::cout << 1 << std::endl;
        } else if (s == "Tuesday") {
            std::cout << 2 << std::endl;
        } else if (s == "Wednesday") {
            std::cout << 3 << std::endl;
        } else if (s == "Thursday") {
            std::cout << 4 << std::endl;
        } else if (s == "Friday") {
            std::cout << 5 << std::endl;
        } else if (s == "Saturday") {
            std::cout << 6 << std::endl;
        } else {
            std::cout << "error" << std::endl;
        }
    }
    return 0;
}
