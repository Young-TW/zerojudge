#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <cctype>
#include <algorithm>
#include <utility>

using namespace std;

struct Token {
    enum Type { NUM, VAR, OP, LP, RP } type;
    string str;
    int val;
    Token(Type t, const string& s = "", int v = 0) : type(t), str(s), val(v) {}
};

void trim(string& s) {
    if (s.empty()) return;
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) { s.clear(); return; }
    size_t end = s.find_last_not_of(" \t\r\n");
    s = s.substr(start, end - start + 1);
}

void tokenize(const string& s, vector<Token>& tokens) {
    int n = s.size();
    for (int i = 0; i < n; ) {
        if (isspace(static_cast<unsigned char>(s[i]))) { i++; continue; }
        if (isdigit(static_cast<unsigned char>(s[i]))) {
            int j = i;
            while (j < n && isdigit(static_cast<unsigned char>(s[j]))) j++;
            int val = stoi(s.substr(i, j - i));
            tokens.emplace_back(Token::NUM, "", val);
            i = j;
        } else if (isalpha(static_cast<unsigned char>(s[i]))) {
            int j = i;
            while (j < n && (isalnum(static_cast<unsigned char>(s[j])) || s[j] == '_')) j++;
            string name = s.substr(i, j - i);
            tokens.emplace_back(Token::VAR, name, 0);
            i = j;
        } else {
            char c = s[i];
            if (c == '(') tokens.emplace_back(Token::LP);
            else if (c == ')') tokens.emplace_back(Token::RP);
            else if (c == '+' || c == '-' || c == '*' || c == '/') tokens.emplace_back(Token::OP, string(1, c), 0);
            i++;
        }
    }
}

bool toRPN(const vector<Token>& tokens, vector<Token>& rpn) {
    stack<Token> st;
    auto prec = [](char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    };
    for (const Token& tok : tokens) {
        if (tok.type == Token::NUM || tok.type == Token::VAR) {
            rpn.push_back(tok);
        } else if (tok.type == Token::OP) {
            char op = tok.str[0];
            while (!st.empty() && st.top().type == Token::OP) {
                char topOp = st.top().str[0];
                if (prec(topOp) >= prec(op)) {
                    rpn.push_back(st.top());
                    st.pop();
                } else break;
            }
            st.push(tok);
        } else if (tok.type == Token::LP) {
            st.push(tok);
        } else if (tok.type == Token::RP) {
            while (!st.empty() && st.top().type != Token::LP) {
                rpn.push_back(st.top());
                st.pop();
            }
            if (st.empty()) return false;
            st.pop();
        }
    }
    while (!st.empty()) {
        if (st.top().type == Token::LP || st.top().type == Token::RP) return false;
        rpn.push_back(st.top());
        st.pop();
    }
    return true;
}

bool evaluateRPN(const vector<Token>& rpn, const unordered_map<string, int>& vars, int& result) {
    stack<int> st;
    for (const Token& tok : rpn) {
        if (tok.type == Token::NUM) {
            st.push(tok.val);
        } else if (tok.type == Token::VAR) {
            auto it = vars.find(tok.str);
            if (it == vars.end()) return false;
            st.push(it->second);
        } else if (tok.type == Token::OP) {
            if (st.size() < 2) return false;
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            int res = 0;
            char op = tok.str[0];
            if (op == '+') res = a + b;
            else if (op == '-') res = a - b;
            else if (op == '*') res = a * b;
            else if (op == '/') {
                if (b == 0) return false;
                res = a / b;
            }
            st.push(res);
        }
    }
    if (st.size() != 1) return false;
    result = st.top();
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    const string delimiter = "等於";
    while (T--) {
        int H;
        cin >> H;
        string line;
        getline(cin, line); // consume newline

        unordered_map<string, int> vars;
        for (int i = 0; i < H - 1; ++i) {
            getline(cin, line);
            size_t pos = line.find(delimiter);
            if (pos == string::npos) continue;
            string var = line.substr(0, pos);
            string valStr = line.substr(pos + delimiter.size());
            trim(var);
            trim(valStr);
            if (!valStr.empty()) {
                int val = stoi(valStr);
                vars[var] = val;
            }
        }
        getline(cin, line);
        trim(line);

        size_t eqPos = line.find('=');
        if (eqPos == string::npos) continue;
        string left = line.substr(0, eqPos);
        string right = line.substr(eqPos + 1);
        trim(left);
        trim(right);
        int target = stoi(right);

        size_t qPos = left.find('?');
        if (qPos == string::npos) continue;

        const vector<pair<char, string>> ops = {{'+', "加"}, {'-', "減"}, {'*', "乘"}, {'/', "除"}};
        char foundOp = 0;
        string foundChinese;
        for (const auto& p : ops) {
            char op = p.first;
            const string& chinese = p.second;
            string expr = left;
            expr[qPos] = op;
            vector<Token> tokens;
            tokenize(expr, tokens);
            vector<Token> rpn;
            if (!toRPN(tokens, rpn)) continue;
            int result;
            if (evaluateRPN(rpn, vars, result)) {
                if (result == target) {
                    foundOp = op;
                    foundChinese = chinese;
                    break;
                }
            }
        }
        if (foundOp) {
            cout << foundOp << ' ' << foundChinese << '\n';
        }
    }
    return 0;
}
