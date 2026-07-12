#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string s;
    std::unordered_map<std::string, int> seen;
    seen.reserve(10000);
    
    int idx = 1;
    while (std::cin >> s) {
        auto it = seen.find(s);
        if (it != seen.end()) {
            std::cout << it->second << " " << idx << "\n";
            return 0;
        }
        seen.emplace(s, idx);
        ++idx;
    }
    
    return 0;
}
