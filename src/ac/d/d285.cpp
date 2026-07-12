#include <iostream>
#include <string>
#include <cctype>
#include <stack>

using namespace std;

int prec(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    if (!getline(cin, line)) return 0;
    int T = 0;
    for (char c : line) {
        if (isdigit(c)) {
            T = T * 10 + (c - '0');
        }
    }

    for (int t = 0; t < T; ++t) {
        string expr = "";
        while (getline(cin, line)) {
            if (line.empty()) {
                if (!expr.empty()) break;
                else continue;
            }
            char c = '\0';
            for (char ch : line) {
                if (!isspace(ch)) {
                    c = ch;
                    break;
                }
            }
            if (c != '\0') {
                expr += c;
            } else {
                if (!expr.empty()) break;
                else continue;
            }
        }

        if (expr.empty() && cin.eof()) break;

        if (t > 0) cout << "\n";

        stack<char> ops;
        for (char c : expr) {
            if (isdigit(c)) {
                cout << c;
            } else if (c == '(') {
                ops.push(c);
            } else if (c == ')') {
                while (!ops.empty() && ops.top() != '(') {
                    cout << ops.top();
                    ops.pop();
                }
                if (!ops.empty()) {
                    ops.pop();
                }
            } else {
                while (!ops.empty() && ops.top() != '(' && prec(ops.top()) >= prec(c)) {
                    cout << ops.top();
                    ops.pop();
                }
                ops.push(c);
            }
        }
        while (!ops.empty()) {
            cout << ops.top();
            ops.pop();
        }
        cout << "\n";
    }

    return 0;
}
