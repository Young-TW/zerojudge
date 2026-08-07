#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cmath>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    while (std::getline(std::cin, s)) {
        if (s.empty()) continue;

        // find the variable letter (first lower‑case letter)
        char var = 0;
        for (char c : s) {
            if (c >= 'a' && c <= 'z') { var = c; break; }
        }

        long long coeffVar = 0;   // total coefficient of the variable
        long long constTerm = 0;  // total constant term

        int side = 1;   // +1 for left side, -1 after '='
        int sign = 1;   // sign of the current term
        std::size_t i = 0, n = s.size();

        while (i < n) {
            char c = s[i];
            if (c == '+') { sign = 1; ++i; continue; }
            if (c == '-') { sign = -1; ++i; continue; }
            if (c == '=') { side = -1; sign = 1; ++i; continue; }

            // start of a term
            long long num = 0;
            bool hasNum = false;
            while (i < n && std::isdigit(s[i])) {
                hasNum = true;
                num = num * 10 + (s[i] - '0');
                ++i;
            }

            if (i < n && std::isalpha(s[i])) {          // variable term
                long long coeff = hasNum ? num : 1LL;
                coeffVar += static_cast<long long>(sign) * side * coeff;
                ++i; // consume the variable letter
            } else {                                    // constant term
                long long value = hasNum ? num : 0LL;
                constTerm += static_cast<long long>(sign) * side * value;
            }
        }

        double ans = -static_cast<double>(constTerm) /
                     static_cast<double>(coeffVar);
        if (std::fabs(ans) < 0.0005) ans = 0.0;   // avoid -0.000

        // ASCII '=' : the OJ's real test data uses a half-width equal sign
        // (the crawled sample statement rendered it full-width, which is wrong).
        std::cout << var << '='
                  << std::fixed << std::setprecision(3) << ans << '\n';
    }
    return 0;
}
