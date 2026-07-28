#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <cctype>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // mapping of special words (lower case) to their abbreviations
    const std::unordered_map<std::string, std::string> abbrev = {
        {"for", "4"},
        {"to",  "2"},
        {"and", "n"},
        {"you", "u"}
    };

    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string word, result;
        while (iss >> word) {
            std::string low;
            low.reserve(word.size());
            for (char ch : word)
                low.push_back(static_cast<char>(std::tolower(
                    static_cast<unsigned char>(ch))));

            auto it = abbrev.find(low);
            if (it != abbrev.end()) {
                result += it->second;
            } else {
                char first = word[0];
                result += static_cast<char>(std::toupper(
                    static_cast<unsigned char>(first)));
            }
        }
        std::cout << result << '\n';
    }
    return 0;
}
