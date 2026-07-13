#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cctype>
#include <map>
#include <algorithm>
#include <cmath>
using namespace std;

string removeSpaces(const string &s) {
    string res;
    for (char c : s) {
        if (!isspace(c)) {
            res += c;
        }
    }
    return res;
}

int precedence(char op) {
    if (op == '^') return 4;
    if (op == '*') return 3;
    if (op == '+' || op == '-') return 2;
    return 0;
}

string infixToPostfix(const string &infix) {
    string postfix;
    stack<char> opStack;
    for (size_t i = 0; i < infix.size(); ++i) {
        char c = infix[i];
        if (c == 'a' || isdigit(c)) {
            postfix += c;
            while (i + 1 < infix.size() && isdigit(infix[i+1])) {
                postfix += infix[++i];
            }
            postfix += ' ';
        } else if (c == '(') {
            opStack.push(c);
        } else if (c == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                postfix += opStack.top();
                postfix += ' ';
                opStack.pop();
            }
            opStack.pop();
        } else {
            while (!opStack.empty() && precedence(opStack.top()) >= precedence(c)) {
                postfix += opStack.top();
                postfix += ' ';
                opStack.pop();
            }
            opStack.push(c);
        }
    }
    while (!opStack.empty()) {
        postfix += opStack.top();
        postfix += ' ';
        opStack.pop();
    }
    return postfix;
}

long long evaluatePostfix(const string &postfix, long long a) {
    stack<long long> valStack;
    for (size_t i = 0; i < postfix.size(); ) {
        if (postfix[i] == ' ') {
            ++i;
            continue;
        }
        if (postfix[i] == 'a') {
            valStack.push(a);
            ++i;
        } else if (isdigit(postfix[i])) {
            long long num = 0;
            while (i < postfix.size() && isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                ++i;
            }
            valStack.push(num);
        } else {
            long long b = valStack.top(); valStack.pop();
            long long a_val = valStack.top(); valStack.pop();
            if (postfix[i] == '+') {
                valStack.push(a_val + b);
            } else if (postfix[i] == '-') {
                valStack.push(a_val - b);
            } else if (postfix[i] == '*') {
                valStack.push(a_val * b);
            } else if (postfix[i] == '^') {
                valStack.push(pow(a_val, b));
            }
            ++i;
        }
    }
    return valStack.top();
}

bool isEquivalent(const string &expr1, const string &expr2) {
    for (int a = 0; a <= 10; ++a) {
        string post1 = infixToPostfix(expr1);
        string post2 = infixToPostfix(expr2);
        long long val1 = evaluatePostfix(post1, a);
        long long val2 = evaluatePostfix(post2, a);
        if (val1 != val2) {
            return false;
        }
    }
    return true;
}

int main() {
    string target;
    while (getline(cin, target)) {
        target = removeSpaces(target);
        int n;
        cin >> n;
        cin.ignore();
        vector<string> options(n);
        for (int i = 0; i < n; ++i) {
            getline(cin, options[i]);
            options[i] = removeSpaces(options[i]);
        }
        string result;
        for (int i = 0; i < n; ++i) {
            if (isEquivalent(target, options[i])) {
                result += 'A' + i;
            }
        }
        cout << result << endl;
    }
    return 0;
}
