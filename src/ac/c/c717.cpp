#include <iostream>
#include <string>

int main() {
    std::string a;
    getline(std::cin, a);
    std::cout << a << " " << a;
    return 0;
}