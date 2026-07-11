#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
#include <cctype>
#include <map>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

const double PI = 3.14159265358979323846;
const double E = 2.71828182845904523536;

map<string, int> precedence = {
    {"+", 1}, {"-", 1},
    {"*", 2}, {"/", 2},
    {"^", 4},
    {"!", 5},
    {"sin", 6}, {"cos", 6}, {"tan", 6},
    {"ln", 6}, {"log", 6},
    {"abs", 6}, {"sqrt", 6}
};

bool isOperator(const string& token) {
    return precedence.find(token) != precedence.end();
}

bool isFunction(const string& token) {
    return token == "sin" || token == "cos" || token == "tan" ||
           token == "ln" || token == "log" || token == "abs" || token == "sqrt";
}

vector<string> tokenize(const string& expr) {
    vector<string> tokens;
    string num;
    for (size_t i = 0; i < expr.size(); ) {
        if (isspace(expr[i])) {
            i++;
            continue;
        }
        if (isdigit(expr[i]) || expr[i] == '.') {
            num.clear();
            while (i < expr.size() && (isdigit(expr[i]) || expr[i] == '.')) {
                num += expr[i++];
            }
            tokens.push_back(num);
        } else if (isalpha(expr[i])) {
            string func;
            while (i < expr.size() && isalpha(expr[i])) {
                func += expr[i++];
            }
            if (func == "pi" || func == "e") {
                tokens.push_back(func);
            } else {
                tokens.push_back(func);
            }
        } else {
            string op;
            op += expr[i++];
            if (op == "-" && (tokens.empty() || tokens.back() == "(" || isOperator(tokens.back()))) {
                tokens.push_back("0");
            }
            tokens.push_back(op);
        }
    }
    return tokens;
}

vector<string> infixToPostfix(const vector<string>& tokens) {
    vector<string> output;
    stack<string> opStack;

    for (const string& token : tokens) {
        if (isdigit(token[0]) || (token.size() > 1 && isdigit(token[1])) || token == "pi" || token == "e") {
            output.push_back(token);
        } else if (token == "(") {
            opStack.push(token);
        } else if (token == ")") {
            while (!opStack.empty() && opStack.top() != "(") {
                output.push_back(opStack.top());
                opStack.pop();
            }
            opStack.pop();
            if (!opStack.empty() && isFunction(opStack.top())) {
                output.push_back(opStack.top());
                opStack.pop();
            }
        } else if (isOperator(token)) {
            while (!opStack.empty() && opStack.top() != "(" &&
                   precedence[opStack.top()] >= precedence[token]) {
                output.push_back(opStack.top());
                opStack.pop();
            }
            opStack.push(token);
        }
    }

    while (!opStack.empty()) {
        output.push_back(opStack.top());
        opStack.pop();
    }

    return output;
}

double factorial(int n) {
    if (n == 0 || n == 1) return 1;
    double result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

double evaluatePostfix(const vector<string>& postfix) {
    stack<double> valStack;

    for (const string& token : postfix) {
        if (isdigit(token[0]) || (token.size() > 1 && isdigit(token[1]))) {
            valStack.push(stod(token));
        } else if (token == "pi") {
            valStack.push(PI);
        } else if (token == "e") {
            valStack.push(E);
        } else if (isOperator(token)) {
            if (token == "!") {
                double a = valStack.top();
                valStack.pop();
                valStack.push(factorial((int)round(a)));
            } else if (token == "sin") {
                double a = valStack.top();
                valStack.pop();
                valStack.push(sin(a));
            } else if (token == "cos") {
                double a = valStack.top();
                valStack.pop();
                valStack.push(cos(a));
            } else if (token == "tan") {
                double a = valStack.top();
                valStack.pop();
                valStack.push(tan(a));
            } else if (token == "ln") {
                double a = valStack.top();
                valStack.pop();
                valStack.push(log(a));
            } else if (token == "log") {
                double a = valStack.top();
                valStack.pop();
                valStack.push(log10(a));
            } else if (token == "abs") {
                double a = valStack.top();
                valStack.pop();
                valStack.push(abs(a));
            } else if (token == "sqrt") {
                double a = valStack.top();
                valStack.pop();
                valStack.push(sqrt(a));
            } else {
                double b = valStack.top();
                valStack.pop();
                double a = valStack.top();
                valStack.pop();

                if (token == "+") valStack.push(a + b);
                else if (token == "-") valStack.push(a - b);
                else if (token == "*") valStack.push(a * b);
                else if (token == "/") valStack.push(a / b);
                else if (token == "^") valStack.push(pow(a, b));
            }
        }
    }

    return valStack.top();
}

int main() {
    string expr;
    while (getline(cin, expr)) {
        if (expr.empty()) continue;

        vector<string> tokens = tokenize(expr);
        vector<string> postfix = infixToPostfix(tokens);
        double result = evaluatePostfix(postfix);

        cout << fixed << setprecision(5) << result << endl;
    }
    return 0;
}
