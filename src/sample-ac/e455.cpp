#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string s;
    while (std::cin >> s) {
        int val = 0;
        for (char c : s) {
            val = (val << 1) | (c - '0');
        }
        if (val & 32768) {
            val = 65536 - val;
        }
        std::cout << val << '\n';
    }
    
    return 0;
}
