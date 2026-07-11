#include <iostream>
#include <string>

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        int count[52] = {0};
        for (char c : line) {
            if (c >= 'A' && c <= 'Z') {
                count[c - 'A']++;
            } else if (c >= 'a' && c <= 'z') {
                count[c - 'a' + 26]++;
            }
        }
        
        int max_count = 0;
        for (int i = 0; i < 52; ++i) {
            if (count[i] > max_count) {
                max_count = count[i];
            }
        }
        
        if (max_count > 0) {
            for (int i = 0; i < 52; ++i) {
                if (count[i] == max_count) {
                    if (i < 26) {
                        std::cout << (char)('A' + i);
                    } else {
                        std::cout << (char)('a' + i - 26);
                    }
                }
            }
            std::cout << " " << max_count << "\n";
        }
    }
    return 0;
}
