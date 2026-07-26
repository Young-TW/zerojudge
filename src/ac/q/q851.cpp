#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string line;
    while (std::getline(std::cin, line)) {
        std::string result;
        int space_count = 0;
        
        for (char c : line) {
            if (c == ' ') {
                ++space_count;
            } else {
                if (space_count > 0) {
                    result.append(space_count - 1, '*');
                    result += ' ';
                    space_count = 0;
                }
                result += c;
            }
        }
        // 處理結尾連續空白
        if (space_count > 0) {
            result.append(space_count - 1, '*');
            result += ' ';
        }
        
        // 首尾若仍為空白，轉為 '*'
        if (!result.empty() && result[0] == ' ') {
            result[0] = '*';
        }
        if (!result.empty() && result.back() == ' ') {
            result.back() = '*';
        }
        
        std::cout << result << '\n';
    }
    
    return 0;
}
