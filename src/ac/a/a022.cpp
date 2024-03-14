#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::string str;
    std::cin >> str;
    std::string str2 = str;
    reverse(str2.begin(), str2.end());
    if (str == str2) {
        std::cout << "yes";
    } else {
        std::cout << "no";
    }

    return 0;
}