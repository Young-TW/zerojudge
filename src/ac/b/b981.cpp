#include <iostream>
#include <string>
#include <cctype>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;

        long long total = 0;
        std::size_t i = 0;
        while (i < line.size()) {
            if (std::isspace(static_cast<unsigned char>(line[i]))) {
                ++i;
                continue;
            }

            // Read number (integer part and optional single fractional digit)
            long long intPart = 0;
            int frac = 0; // tenths
            while (i < line.size() && std::isdigit(static_cast<unsigned char>(line[i]))) {
                intPart = intPart * 10 + (line[i] - '0');
                ++i;
            }
            if (i < line.size() && line[i] == '.') {
                ++i;
                if (i < line.size() && std::isdigit(static_cast<unsigned char>(line[i]))) {
                    frac = line[i] - '0';
                    ++i;
                }
            }

            // Read unit letters
            std::string unit;
            while (i < line.size() && std::isalpha(static_cast<unsigned char>(line[i]))) {
                unit += line[i];
                ++i;
            }

            long long unitMs = 0;
            if (unit == "hour" || unit == "h") {
                unitMs = 3600000;
            } else if (unit == "min" || unit == "m") {
                unitMs = 60000;
            } else if (unit == "ms") {
                unitMs = 1;
            } else if (unit == "s") {
                unitMs = 1000;
            }

            total += intPart * unitMs + unitMs * frac / 10;
        }

        std::cout << total << '\n';
    }

    return 0;
}
// YoJudge 預練(時間之章)
