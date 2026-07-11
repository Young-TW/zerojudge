#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string line;
    while (std::getline(std::cin, line)) {
        line += '\n';

        std::cout << "___________\n";

        for (unsigned char c : line) {
            int ascii = c;
            int high5 = (ascii >> 3) & 0x1F;
            int low3 = ascii & 0x7;

            std::string middle;
            middle.reserve(9);
            for (int i = 4; i >= 0; --i) {
                middle += (high5 & (1 << i)) ? 'o' : ' ';
            }
            middle += '.';
            for (int i = 2; i >= 0; --i) {
                middle += (low3 & (1 << i)) ? 'o' : ' ';
            }

            std::cout << '|' << middle << "|\n";
        }

        std::cout << "___________\n";
    }
    return 0;
}
