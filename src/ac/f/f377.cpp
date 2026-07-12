#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>

using namespace std;

int precedence(const string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
}

bool isOperator(const string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string token;
        vector<string> output;
        stack<string> ops;

        while (ss >> token) {
            if (isOperator(token)) {
                while (!ops.empty() && precedence(ops.top()) >= precedence(token)) {
                    output.push_back(ops.top());
                    ops.pop();
                }
                ops.push(token);
            } else if (token == "(") {
                ops.push(token);
            } else if (token == ")") {
                while (!ops.empty() && ops.top() != "(") {
                    output.push_back(ops.top());
                    ops.pop();
                }
                if (!ops.empty()) {
                    ops.pop(); // pop "("
                }
            } else {
                output.push_back(token);
            }
        }

        while (!ops.empty()) {
            output.push_back(ops.top());
            ops.pop();
        }

        for (size_t i = 0; i < output.size(); ++i) {
            if (i > 0) cout << " ";
            cout << output[i];
        }
        cout << "\n";
    }

    return 0;
}
