#include <iostream>
#include <string>
#include <utility>
using namespace std;

const int MOD = 10007;

string s;
int pos;
int n;

pair<int,int> parseExpr();

pair<int,int> parseFactor() {
    if (pos < n && s[pos] == '(') {
        pos++;
        pair<int,int> r = parseExpr();
        if (pos < n && s[pos] == ')') pos++;
        return r;
    }
    return {1, 1};
}

pair<int,int> parseTerm() {
    pair<int,int> left = parseFactor();
    while (pos < n && s[pos] == '*') {
        pos++;
        pair<int,int> right = parseFactor();
        int l0 = left.first, l1 = left.second;
        int r0 = right.first, r1 = right.second;
        int lt = (l0 + l1) % MOD;
        int rt = (r0 + r1) % MOD;
        int w1 = (l1 * r1) % MOD;
        int w0 = ((lt * rt) % MOD - w1 + MOD) % MOD;
        left = {w0, w1};
    }
    return left;
}

pair<int,int> parseExpr() {
    pair<int,int> left = parseTerm();
    while (pos < n && s[pos] == '+') {
        pos++;
        pair<int,int> right = parseTerm();
        int l0 = left.first, l1 = left.second;
        int r0 = right.first, r1 = right.second;
        int lt = (l0 + l1) % MOD;
        int rt = (r0 + r1) % MOD;
        int w0 = (l0 * r0) % MOD;
        int w1 = ((lt * rt) % MOD - w0 + MOD) % MOD;
        left = {w0, w1};
    }
    return left;
}

int main() {
    int L;
    while (cin >> L >> s) {
        pos = 0;
        n = (int)s.size();
        pair<int,int> r = parseExpr();
        cout << r.first % MOD << "\n";
    }
    return 0;
}
