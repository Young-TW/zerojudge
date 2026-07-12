#include <iostream>
#include <string>
#include <unordered_set>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string s;
    std::unordered_set<std::string> seen;
    
    while (std::cin >> s) {
        if (seen.find(s) != seen.end()) {
            std::cout << "1\n";
        } else {
            seen.insert(s);
            std::cout << "0\n";
        }
    }
    
    return 0;
}
