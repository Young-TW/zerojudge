#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct Parser {
    vector<string> tokens;
    int pos = 0;

    string peek() { return pos < (int)tokens.size() ? tokens[pos] : ""; }
    string next() { return pos < (int)tokens.size() ? tokens[pos++] : ""; }

    long long parseExpr() {
        long long v = parseTerm();
        while (true) {
            string op = peek();
            if (op == "+" || op == "-") {
                next();
                long long r = parseTerm();
                v = (op == "+") ? v + r : v - r;
            } else break;
        }
        return v;
    }

    long long parseTerm() {
        long long v = parseFactor();
        while (true) {
            string op = peek();
            if (op == "*" || op == "/" || op == "%") {
                next();
                long long r = parseFactor();
                if (op == "*") v *= r;
                else if (op == "/") v /= r;
                else v %= r;
            } else break;
        }
        return v;
    }

    long long parseFactor() {
        string t = peek();
        if (t == "(") {
            next();
            long long v = parseExpr();
            if (peek() == ")") next();
            return v;
        }
        next();
        return stoll(t);
    }
};

int main() {
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        vector<string> toks;
        string t;
        while (ss >> t) toks.push_back(t);
        Parser p{toks, 0};
        cout << p.parseExpr() << "\n";
    }
    return 0;
}
