#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string s;
    while (std::cin >> s && s != "0") {
        int sum = 0;
        for (size_t i = 0; i < s.length(); ++i) {
            int digit = s[i] - '0';
            if (i % 2 == 0) {
                sum += digit;
            } else {
                sum -= digit;
            }
        }
        
        if (sum % 11 == 0) {
            std::cout << s << " is a multiple of 11.\n";
        } else {
            std::cout << s << " is not a multiple of 11.\n";
        }
    }
    
    return 0;
}
