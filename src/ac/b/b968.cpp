#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string girl, boy;
    if (!std::getline(std::cin, girl)) return 0;   // no input
    if (!std::getline(std::cin, boy)) return 0;    // incomplete input

    std::cout << girl << " and " << boy << " sitting in the tree\n";
    return 0;
}
