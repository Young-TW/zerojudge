#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

std::string trim(const std::string &s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string line1;
    if (!std::getline(std::cin, line1)) return 0;
    
    std::string connector;
    std::getline(std::cin, connector);
    connector = trim(connector);
    
    std::stringstream ss(line1);
    std::string word;
    bool first = true;
    
    while (ss >> word) {
        if (!first) {
            std::cout << " " << connector << " ";
        }
        std::cout << word;
        first = false;
    }
    std::cout << "\n";
    
    return 0;
}
