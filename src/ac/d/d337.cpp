#include <iostream>
#include <string>
#include <cstdint>

bool is_chinese(uint32_t cp) {
    return (cp >= 0x4E00 && cp <= 0x9FFF) ||
           (cp >= 0x3400 && cp <= 0x4DBF) ||
           (cp >= 0x20000 && cp <= 0x2A6DF) ||
           (cp >= 0x2A700 && cp <= 0x2B73F) ||
           (cp >= 0x2B740 && cp <= 0x2B81F) ||
           (cp >= 0x2B820 && cp <= 0x2CEAF) ||
           (cp >= 0x2CEB0 && cp <= 0x2EBEF) ||
           (cp >= 0xF900 && cp <= 0xFAFF) ||
           (cp >= 0x2F800 && cp <= 0x2FA1F);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string line;
    while (std::getline(std::cin, line)) {
        std::string out;
        for (size_t i = 0; i < line.size(); ) {
            unsigned char c = line[i];
            uint32_t cp = 0;
            size_t len = 0;
            if (c < 0x80) {
                cp = c;
                len = 1;
            } else if ((c & 0xE0) == 0xC0) {
                cp = c & 0x1F;
                len = 2;
            } else if ((c & 0xF0) == 0xE0) {
                cp = c & 0x0F;
                len = 3;
            } else if ((c & 0xF8) == 0xF0) {
                cp = c & 0x07;
                len = 4;
            } else {
                ++i;
                continue;
            }

            if (i + len > line.size()) {
                break;
            }

            bool valid = true;
            for (size_t j = 1; j < len; ++j) {
                if ((static_cast<unsigned char>(line[i + j]) & 0xC0) != 0x80) {
                    valid = false;
                    break;
                }
                cp = (cp << 6) | (line[i + j] & 0x3F);
            }

            if (!valid) {
                ++i;
                continue;
            }

            if (is_chinese(cp)) {
                out.append(line, i, len);
            }
            i += len;
        }
        std::cout << out << "\n";
    }
    return 0;
}
