#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string line;
    while (std::getline(std::cin, line)) {
        // Handle "SAMPLE INPUT" labels by converting to "SAMPLE OUTPUT"
        size_t pos = line.find("INPUT");
        if (pos != std::string::npos) {
            line.replace(pos, 5, "OUTPUT");
            std::cout << line << "\n";
            continue;
        }
        
        // Count leading dashes
        size_t i = 0;
        while (i < line.size() && line[i] == '-') ++i;
        size_t cnt = i;
        std::string num = line.substr(i);
        
        // If no number part, pass through
        if (num.empty()) {
            std::cout << line << "\n";
            continue;
        }
        
        // Check if K is zero
        bool isZero = true;
        for (char c : num) {
            if (c != '0') { isZero = false; break; }
        }
        
        if (isZero) {
            std::cout << '0' << '\n';
        } else if (cnt % 2 == 1) {
            std::cout << '-' << num << '\n';
        } else {
            std::cout << num << '\n';
        }
    }
    return 0;
}
