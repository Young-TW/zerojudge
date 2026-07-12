#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>

using namespace std;

long long evaluate(const string& expr) {
    size_t pos = expr.find("**");
    if (pos != string::npos) {
        string left_str = expr.substr(0, pos);
        string right_str = expr.substr(pos + 2);
        long long left = stoll(left_str);
        long long right = stoll(right_str);
        if (right == 0) return 1;
        long long result = 1;
        for (long long i = 0; i < right; ++i) {
            result *= left;
        }
        return result;
    }

    pos = expr.find("x");
    if (pos != string::npos) {
        string left_str = expr.substr(0, pos);
        string right_str = expr.substr(pos + 1);
        long long left = stoll(left_str);
        long long right = stoll(right_str);
        return left * right;
    }

    return stoll(expr);
}

int main() {
    int T;
    cin >> T;
    cin.ignore();

    while (T--) {
        string expr;
        getline(cin, expr);

        size_t start = expr.find_first_not_of(" ");
        if (start != string::npos) {
            expr = expr.substr(start);
        }
        size_t end = expr.find_last_not_of(" ");
        if (end != string::npos) {
            expr = expr.substr(0, end + 1);
        }

        cout << evaluate(expr) << endl;
    }

    return 0;
}
