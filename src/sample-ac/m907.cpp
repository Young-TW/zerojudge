#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct Linear {
    long long a, b;
};

vector<string> tokens;
int pos;

Linear parseExpr();

Linear parseFactor() {
    const string& t = tokens[pos];
    if (t == "(") {
        pos++;
        Linear r = parseExpr();
        pos++;
        return r;
    } else if (t == "x") {
        pos++;
        return {1, 0};
    } else {
        long long v = 0;
        for (size_t i = 0; i < t.size(); i++) v = v * 10 + (t[i] - '0');
        pos++;
        return {0, v};
    }
}

Linear parseTerm() {
    Linear r = parseFactor();
    while (pos < (int)tokens.size() && tokens[pos] == "*") {
        pos++;
        Linear r2 = parseFactor();
        long long na = r.a * r2.b + r2.a * r.b;
        long long nb = r.b * r2.b;
        r = {na, nb};
    }
    return r;
}

Linear parseExpr() {
    Linear r = parseTerm();
    while (pos < (int)tokens.size() && tokens[pos] == "+") {
        pos++;
        Linear r2 = parseTerm();
        r = {r.a + r2.a, r.b + r2.b};
    }
    return r;
}

Linear parse(const string& line) {
    tokens.clear();
    stringstream ss(line);
    string t;
    while (ss >> t) tokens.push_back(t);
    pos = 0;
    return parseExpr();
}

int main() {
    string line1, line2;
    while (getline(cin, line1) && getline(cin, line2)) {
        Linear e1 = parse(line1);
        Linear e2 = parse(line2);
        long long da = e1.a - e2.a;
        long long db = e2.b - e1.b;
        if (da == 0) {
            cout << 0 << "\n";
        } else {
            cout << db / da << "\n";
        }
    }
    return 0;
}
