#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::string s1, s2, name;
    getline(std::cin, s1);
    getline(std::cin, s2);
    std::stringstream ss(s1);
    while (ss >> name) std::cout << s2 << ", " << name << std::endl;
    return 0;
}