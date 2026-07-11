#include <iostream>
#include <string>
#include <sstream>
#include <map>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string line1, line2;
    while (std::getline(std::cin, line1)) {
        if (!std::getline(std::cin, line2)) {
            line2 = "";
        }

        std::istringstream iss1(line1);
        std::string word;
        std::map<std::string, int> required;
        while (iss1 >> word) {
            required[word]++;
        }

        std::istringstream iss2(line2);
        std::map<std::string, int> collected;
        while (iss2 >> word) {
            if (required.find(word) != required.end()) {
                collected[word]++;
            }
        }

        int ans = -1;
        for (const auto& p : required) {
            int count = 0;
            std::map<std::string, int>::const_iterator it = collected.find(p.first);
            if (it != collected.end()) {
                count = it->second / p.second;
            }
            if (ans == -1 || count < ans) {
                ans = count;
            }
        }

        if (ans == -1) {
            ans = 0;
        }
        std::cout << ans << "\n";
    }

    return 0;
}
