#include <iostream>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

typedef long long ll;

static int prec(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

static void applyOp(stack<ll>& vals, stack<char>& ops) {
    ll b = vals.top(); vals.pop();
    ll a = vals.top(); vals.pop();
    char op = ops.top(); ops.pop();
    ll r = 0;
    switch (op) {
        case '+': r = a + b; break;
        case '-': r = a - b; break;
        case '*': r = a * b; break;
        case '/': r = a / b; break;
    }
    vals.push(r);
}

static ll eval(const string& s) {
    stack<ll> vals;
    stack<char> ops;
    for (size_t i = 0; i < s.size(); ) {
        char c = s[i];
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n') { i++; continue; }
        if (isdigit((unsigned char)c)) {
            ll num = 0;
            while (i < s.size() && isdigit((unsigned char)s[i])) {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            vals.push(num);
        } else if (c == '(') {
            ops.push(c);
            i++;
        } else if (c == ')') {
            while (!ops.empty() && ops.top() != '(') applyOp(vals, ops);
            if (!ops.empty()) ops.pop();
            i++;
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!ops.empty() && ops.top() != '(' && prec(ops.top()) >= prec(c))
                applyOp(vals, ops);
            ops.push(c);
            i++;
        } else {
            i++;
        }
    }
    while (!ops.empty()) applyOp(vals, ops);
    return vals.top();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if (!(cin >> n)) return 0;
    cin.ignore();
    for (int i = 0; i < n; i++) {
        string line;
        while (getline(cin, line)) {
            bool hasContent = false;
            for (size_t k = 0; k < line.size(); k++)
                if (line[k] != ' ' && line[k] != '\t' && line[k] != '\r') { hasContent = true; break; }
            if (hasContent) break;
            if (cin.eof()) break;
        }
        cout << eval(line) << "\n";
    }
    return 0;
}
