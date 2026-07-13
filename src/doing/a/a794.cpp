#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cctype>

struct Parser {
    const std::string& s;
    size_t pos;
    double x_val;

    Parser(const std::string& str, double x) : s(str), pos(0), x_val(x) {}

    void skipSpaces() {
        while (pos < s.size() && std::isspace(static_cast<unsigned char>(s[pos]))) ++pos;
    }

    double parseExpr() {
        double res = parseTerm();
        while (true) {
            skipSpaces();
            if (pos < s.size() && (s[pos] == '+' || s[pos] == '-')) {
                char op = s[pos++];
                double rhs = parseTerm();
                if (op == '+') res += rhs;
                else res -= rhs;
            } else break;
        }
        return res;
    }

    double parseTerm() {
        double res = parseUnary();
        while (true) {
            skipSpaces();
            if (pos < s.size() && (s[pos] == '*' || s[pos] == '/')) {
                char op = s[pos++];
                double rhs = parseUnary();
                if (op == '*') res *= rhs;
                else res /= rhs;
            } else break;
        }
        return res;
    }

    double parseUnary() {
        skipSpaces();
        if (pos < s.size() && (s[pos] == '+' || s[pos] == '-')) {
            char op = s[pos++];
            double val = parseUnary();
            return (op == '+') ? val : -val;
        }
        return parsePower();
    }

    double parsePower() {
        double base = parsePrimary();
        skipSpaces();
        if (pos < s.size() && s[pos] == '^') {
            ++pos;
            double exp = parsePower(); // right associative
            return std::pow(base, exp);
        }
        return base;
    }

    double parsePrimary() {
        skipSpaces();
        if (pos >= s.size()) return 0.0;

        if (s[pos] == '(') {
            ++pos;
            double val = parseExpr();
            skipSpaces();
            if (pos < s.size() && s[pos] == ')') ++pos;
            return val;
        } else if (s[pos] == 'x') {
            ++pos;
            return x_val;
        } else if (std::isdigit(static_cast<unsigned char>(s[pos])) || s[pos] == '.') {
            return parseNumber();
        } else if (std::isalpha(static_cast<unsigned char>(s[pos]))) {
            return parseFunction();
        }
        return 0.0;
    }

    double parseNumber() {
        size_t start = pos;
        bool hasDot = false;
        while (pos < s.size()) {
            char c = s[pos];
            if (std::isdigit(static_cast<unsigned char>(c))) {
                ++pos;
            } else if (c == '.' && !hasDot) {
                hasDot = true;
                ++pos;
            } else break;
        }
        return std::stod(s.substr(start, pos - start));
    }

    double parseFunction() {
        size_t start = pos;
        while (pos < s.size() && std::isalpha(static_cast<unsigned char>(s[pos]))) ++pos;
        std::string func = s.substr(start, pos - start);
        skipSpaces();
        if (pos < s.size() && s[pos] == '(') ++pos;
        double arg = parseExpr();
        skipSpaces();
        if (pos < s.size() && s[pos] == ')') ++pos;

        if (func == "sin") return std::sin(arg);
        if (func == "cos") return std::cos(arg);
        if (func == "log10") return std::log10(arg);
        return 0.0;
    }
};

double evaluate(const std::string& expr, double x) {
    Parser parser(expr, x);
    return parser.parseExpr();
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string line;
    while (std::getline(std::cin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back(); // handle CRLF
        size_t eqPos = line.find('=');
        std::string expr = (eqPos != std::string::npos) ? line.substr(eqPos + 1) : line;

        std::vector<std::string> grid(21, std::string(21, '.'));

        for (int x = -10; x <= 10; ++x) {
            double y_val = evaluate(expr, x);
            int y_int = static_cast<int>(y_val); // truncation toward zero
            if (y_int >= -10 && y_int <= 10) {
                int row = 10 - y_int;
                int col = x + 10;
                grid[row][col] = '*';
            }
        }

        for (int r = 0; r < 21; ++r) {
            for (int c = 0; c < 21; ++c) {
                char ch = grid[r][c];
                if (ch == '*') std::cout << '*';
                else if (r == 10 && c == 10) std::cout << '+';
                else if (r == 10) std::cout << '-';
                else if (c == 10) std::cout << '|';
                else std::cout << '.';
            }
            std::cout << '\n';
        }
    }
    return 0;
}
