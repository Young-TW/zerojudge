#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string s, cmd;
    while (std::getline(std::cin, s)) {
        if (!std::getline(std::cin, cmd)) break;
        
        int pos = 0;
        for (std::size_t i = 0; i < cmd.size(); ++i) {
            char c = cmd[i];
            switch (c) {
                case '0':
                    pos = 0;
                    break;
                case '$':
                    pos = static_cast<int>(s.size());
                    break;
                case 'x':
                    if (pos >= 0 && pos < static_cast<int>(s.size())) {
                        s.erase(pos, 1);
                    }
                    break;
                case 's':
                    if (pos >= 0 && pos + 1 < static_cast<int>(s.size())) {
                        std::swap(s[pos], s[pos + 1]);
                    }
                    break;
                case 'i':
                    if (i + 1 < cmd.size()) {
                        ++i;
                        char ch = cmd[i];
                        if (pos < 0) pos = 0;
                        if (pos > static_cast<int>(s.size())) pos = static_cast<int>(s.size());
                        s.insert(pos, 1, ch);
                        ++pos;
                    }
                    break;
                case 'u':
                    if (pos >= 0 && pos < static_cast<int>(s.size())) {
                        if (std::isalpha(static_cast<unsigned char>(s[pos]))) {
                            s[pos] = std::toupper(static_cast<unsigned char>(s[pos]));
                        }
                    }
                    ++pos;
                    break;
                case '+':
                    ++pos;
                    break;
                case '-':
                    --pos;
                    break;
                default:
                    break;
            }
        }
        std::cout << s << '\n';
    }
    return 0;
}
