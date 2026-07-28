#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdint>

using namespace std;

using int128 = __int128_t;

// convert decimal string (may contain sign and at most two fractional digits)
// to scaled integer value = real_value * 100
int128 parseScaled(const string &s) {
    bool neg = false;
    size_t i = 0;
    if (i < s.size() && (s[i] == '-' || s[i] == '+')) {
        if (s[i] == '-') neg = true;
        ++i;
    }
    int128 intPart = 0;
    while (i < s.size() && isdigit(s[i])) {
        intPart = intPart * 10 + (s[i] - '0');
        ++i;
    }
    int128 frac = 0;
    int cnt = 0;
    if (i < s.size() && s[i] == '.') {
        ++i;
        while (i < s.size() && isdigit(s[i]) && cnt < 2) {
            frac = frac * 10 + (s[i] - '0');
            ++i;
            ++cnt;
        }
    }
    while (cnt < 2) {          // pad missing fractional digits with zeros
        frac *= 10;
        ++cnt;
    }
    int128 total = intPart * 100 + frac;
    if (neg) total = -total;
    return total;
}

// value of substring n[l .. r-1] (digits only) as scaled integer
int128 segmentScaled(const string &n, int l, int r) {
    int128 v = 0;
    for (int i = l; i < r; ++i) {
        v = v * 10 + (n[i] - '0');
    }
    return v * 100;            // scale by 100
}

// apply operator s to scaled operands a and b, store result in res.
// return false if operation is illegal (division by zero)
bool applyOp(char op, int128 a, int128 b, int128 &res) {
    switch (op) {
        case '+': res = a + b; return true;
        case '-': res = a - b; return true;
        case '*': res = (a * b) / 100; return true;          // (a/100)*(b/100)
        case '/':
            if (b == 0) return false;
            res = (a * 100) / b; return true;                // (a/100)/(b/100)
    }
    return false;
}

string n;
char op;
int t;
int128 target;
string targetStr;

vector<int> splits;          // positions after each part, last one = n.size()
bool found;

void dfs(int pos, int used, int128 cur) {
    if (found) return;
    int len = (int)n.size();

    if (used == t) {                     // last part must be the rest
        if (pos >= len) return;
        int128 seg = segmentScaled(n, pos, len);
        int128 val;
        if (used == 0) {                 // t == 0 case
            val = seg;
        } else {
            if (!applyOp(op, cur, seg, val)) return;
        }
        if (val == target) {
            splits.push_back(len);
            found = true;
        }
        return;
    }

    // we need at least (t - used) more operators -> at least that many digits left
    for (int end = pos + 1; end <= len - (t - used); ++end) {
        int128 seg = segmentScaled(n, pos, end);
        int128 nxt;
        if (used == 0) {
            nxt = seg;                    // first number, no operator yet
        } else {
            if (!applyOp(op, cur, seg, nxt)) continue; // division by zero
        }
        splits.push_back(end);
        dfs(end, used + 1, nxt);
        if (found) return;
        splits.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> op >> t >> targetStr) {
        target = parseScaled(targetStr);
        found = false;
        splits.clear();

        if (t == 0) {
            int128 whole = segmentScaled(n, 0, (int)n.size());
            if (whole == target) {
                cout << n << "=" << targetStr << "\n";
            } else {
                cout << "No solution\n";
            }
            continue;
        }

        if (t > (int)n.size() - 1) {          // impossible, but problem guarantees a solution
            cout << "No solution\n";
            continue;
        }

        dfs(0, 0, 0);
        if (found) {
            string expr;
            int prev = 0;
            for (size_t i = 0; i < splits.size(); ++i) {
                if (i > 0) expr += op;
                expr.append(n, prev, splits[i] - prev);
                prev = splits[i];
            }
            cout << expr << "=" << targetStr << "\n";
        } else {
            cout << "No solution\n";
        }
    }
    return 0;
}
