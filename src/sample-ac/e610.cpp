#include <iostream>
#include <string>
#include <cctype>

int hexToInt(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string line;
    while (std::getline(std::cin, line)) {
        std::string result;
        result.reserve(line.length());
        
        for (size_t i = 0; i < line.length(); ++i) {
            if (line[i] == '%' && i + 2 < line.length() && 
                std::isxdigit(static_cast<unsigned char>(line[i+1])) && 
                std::isxdigit(static_cast<unsigned char>(line[i+2]))) {
                
                char c = static_cast<char>((hexToInt(line[i+1]) << 4) | hexToInt(line[i+2]));
                result += c;
                i += 2;
            } else {
                result += line[i];
            }
        }
        std::cout << result << "\n";
    }
    
    return 0;
}
