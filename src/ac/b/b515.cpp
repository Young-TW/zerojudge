#include <iostream>
#include <string>
#include <sstream>
#include <map>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    if (!(std::cin >> n)) return 0;
    
    std::map<std::string, char> morse = {
        {".-", 'A'}, {"-...", 'B'}, {"-.-.", 'C'}, {"-..", 'D'},
        {".", 'E'}, {"..-.", 'F'}, {"--.", 'G'}, {"....", 'H'},
        {"..", 'I'}, {".---", 'J'}, {"-.-", 'K'}, {".-..", 'L'},
        {"--", 'M'}, {"-.", 'N'}, {"---", 'O'}, {".--.", 'P'},
        {"--.-", 'Q'}, {".-.", 'R'}, {"...", 'S'}, {"-", 'T'},
        {"..-", 'U'}, {"...-", 'V'}, {".--", 'W'}, {"-..-", 'X'},
        {"-.--", 'Y'}, {"--..", 'Z'}
    };
    
    for (int i = 0; i < n; ++i) {
        std::string line;
        std::getline(std::cin >> std::ws, line);
        std::stringstream ss(line);
        std::string code;
        while (ss >> code) {
            auto it = morse.find(code);
            if (it != morse.end()) {
                std::cout << it->second;
            }
        }
        std::cout << "\n";
    }
    
    return 0;
}
