#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string s;
int pos;

long long parseExpression();

long long parseFactor() {
    while (pos < s.length() && s[pos] == ' ') pos++;
    if (pos < s.length() && s[pos] == 'f') {
        pos++; // skip 'f'
        while (pos < s.length() && s[pos] == ' ') pos++;
        if (pos < s.length() && s[pos] == '(') {
            pos++; // skip '('
            vector<long long> args;
            while (true) {
                while (pos < s.length() && s[pos] == ' ') pos++;
                if (pos < s.length() && s[pos] == ')') {
                    pos++;
                    break;
                }
                long long val = parseExpression();
                args.push_back(val);
                while (pos < s.length() && s[pos] == ' ') pos++;
                if (pos < s.length() && s[pos] == ',') {
                    pos++;
                } else if (pos < s.length() && s[pos] == ')') {
                    pos++;
                    break;
                }
            }
            if (args.empty()) return 0;
            long long min_val = *min_element(args.begin(), args.end());
            long long max_val = *max_element(args.begin(), args.end());
            return max_val - min_val;
        }
    } else {
        long long val = 0;
        while (pos < s.length() && s[pos] >= '0' && s[pos] <= '9') {
            val = val * 10 + (s[pos] - '0');
            pos++;
        }
        return val;
    }
    return 0;
}

long long parseTerm() {
    long long val = parseFactor();
    while (true) {
        while (pos < s.length() && s[pos] == ' ') pos++;
        if (pos < s.length() && s[pos] == '+') {
            pos++;
            val += parseFactor();
        } else {
            break;
        }
    }
    return val;
}

long long parseExpression() {
    long long val = parseTerm();
    while (true) {
        while (pos < s.length() && s[pos] == ' ') pos++;
        if (pos < s.length() && s[pos] == '*') {
            pos++;
            val *= parseTerm();
        } else {
            break;
        }
    }
    return val;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (getline(cin, s)) {
        while (!s.empty() && (s.back() == '\r' || s.back() == ' ')) {
            s.pop_back();
        }
        if (s.empty()) continue;
        pos = 0;
        cout << parseExpression() << "\n";
    }
    return 0;
}
