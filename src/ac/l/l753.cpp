#include <bits/stdc++.h>
using namespace std;

using i128 = __int128_t;

/* ---------- fraction ---------- */
struct Fraction {
    i128 n, d;                     // d > 0, reduced
    Fraction(i128 _n = 0, i128 _d = 1) : n(_n), d(_d) { normalize(); }
    static i128 abs128(i128 x) { return x >= 0 ? x : -x; }
    static i128 gcd128(i128 a, i128 b) {
        a = abs128(a); b = abs128(b);
        while (b != 0) { i128 t = a % b; a = b; b = t; }
        return a;
    }
    void normalize() {
        if (d < 0) { n = -n; d = -d; }
        if (n == 0) { d = 1; return; }
        i128 g = gcd128(n, d);
        n /= g; d /= g;
    }
    bool operator<(const Fraction& o) const {
        if (n != o.n) return n < o.n;
        return d < o.d;
    }
    bool operator==(const Fraction& o) const { return n == o.n && d == o.d; }
};

/* ---------- arithmetic on fractions ---------- */
Fraction add(const Fraction& a, const Fraction& b) {
    return Fraction(a.n * b.d + b.n * a.d, a.d * b.d);
}
Fraction subf(const Fraction& a, const Fraction& b) {
    return Fraction(a.n * b.d - b.n * a.d, a.d * b.d);
}
Fraction mul(const Fraction& a, const Fraction& b) {
    return Fraction(a.n * b.n, a.d * b.d);
}
Fraction divide(const Fraction& a, const Fraction& b) {
    // b.n != 0 guaranteed by caller
    return Fraction(a.n * b.d, a.d * b.n);
}

/* ---------- expression tree ---------- */
struct Node {
    bool isNum;
    string txt;          // for leaf
    char op;             // for inner node
    Node *l, *r;
    Node(const string& s) : isNum(true), txt(s), op(0), l(nullptr), r(nullptr) {}
    Node(char o, Node* L, Node* R) : isNum(false), txt(), op(o), l(L), r(R) {}
};

/* ---------- precedence ---------- */
int prec(char op) {
    if (op == '+' || op == '-') return 1;
    return 2;               // * or /
}

/* ---------- build string with minimal parentheses ---------- */
string build(Node* nd, char parentOp = 0, bool rightChild = false) {
    if (nd->isNum) return nd->txt;
    string L = build(nd->l, nd->op, false);
    string R = build(nd->r, nd->op, true);
    string cur = L + nd->op + R;
    bool need = false;
    if (parentOp) {
        int pc = prec(nd->op), pp = prec(parentOp);
        if (pc < pp) need = true;
        else if (pc == pp && rightChild && (parentOp == '-' || parentOp == '/'))
            need = true;
    }
    if (need) return "(" + cur + ")";
    return cur;
}

/* ---------- global data for one test case ---------- */
string N;                     // digit string
vector<char> ops;             // size t
i128 targetScaled;            // target * 100, truncated towards zero
string targetOrig;            // original target string (for output)
string answer;
bool solved;

/* ---------- DP for a fixed splitting ---------- */
bool solve_one_split(const vector<string>& parts) {
    int m = (int)parts.size();               // = t+1
    vector<vector< map<Fraction, Node*> > > dp(m,
            vector< map<Fraction, Node*> >(m));

    // leaves
    for (int i = 0; i < m; ++i) {
        i128 v = 0;
        for (char c : parts[i]) v = v * 10 + (c - '0');
        Fraction f(v, 1);
        dp[i][i][f] = new Node(parts[i]);
    }

    // intervals
    for (int len = 2; len <= m; ++len) {
        for (int i = 0; i + len - 1 < m; ++i) {
            int j = i + len - 1;
            for (int k = i; k < j; ++k) {
                char op = ops[k];
                const auto& leftMap = dp[i][k];
                const auto& rightMap = dp[k + 1][j];
                for (const auto& L : leftMap) {
                    for (const auto& R : rightMap) {
                        if (op == '/' && R.first.n == 0) continue; // division by zero
                        Fraction v;
                        if (op == '+') v = add(L.first, R.first);
                        else if (op == '-') v = subf(L.first, R.first);
                        else if (op == '*') v = mul(L.first, R.first);
                        else v = divide(L.first, R.first); // '/'
                        if (dp[i][j].find(v) == dp[i][j].end())
                            dp[i][j][v] = new Node(op, L.second, R.second);
                    }
                }
            }
        }
    }

    // check target
    for (const auto& it : dp[0][m - 1]) {
        const Fraction& f = it.first;
        i128 scaled = (f.n * 100) / f.d;          // truncates towards zero
        if (scaled == targetScaled) {
            answer = build(it.second) + "=" + targetOrig;
            return true;
        }
    }
    return false;
}

/* ---------- enumerate all splits of N ---------- */
void dfs(int pos, int partsLeft, vector<string>& cur) {
    if (solved) return;
    if (partsLeft == 1) {
        string sub = N.substr(pos);
        if (sub.size() > 1 && sub[0] == '0') return;
        cur.push_back(sub);
        if (solve_one_split(cur)) solved = true;
        cur.pop_back();
        return;
    }
    int maxEnd = (int)N.size() - (partsLeft - 1);
    for (int end = pos + 1; end <= maxEnd; ++end) {
        string sub = N.substr(pos, end - pos);
        if (sub.size() > 1 && sub[0] == '0') continue;
        cur.push_back(sub);
        dfs(end, partsLeft - 1, cur);
        cur.pop_back();
        if (solved) return;
    }
}

/* ---------- helper: read target as scaled integer ---------- */
i128 parseTargetScaled(const string& s) {
    bool neg = false;
    int i = 0;
    if (s[i] == '-') { neg = true; ++i; }
    i128 intPart = 0;
    while (i < (int)s.size() && isdigit(s[i])) {
        intPart = intPart * 10 + (s[i] - '0');
        ++i;
    }
    i128 fracPart = 0;
    int digits = 0;
    if (i < (int)s.size() && s[i] == '.') {
        ++i;
        while (i < (int)s.size() && isdigit(s[i]) && digits < 2) {
            fracPart = fracPart * 10 + (s[i] - '0');
            ++i; ++digits;
        }
    }
    while (digits < 2) { fracPart *= 10; ++digits; }
    i128 scaled = intPart * 100 + fracPart;
    if (neg) scaled = -scaled;
    return scaled;
}

/* ---------- main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> N) {
        int T; if (!(cin >> T)) break;
        ops.assign(T, 0);
        for (int i = 0; i < T; ++i) cin >> ops[i];
        cin >> targetOrig;
        targetScaled = parseTargetScaled(targetOrig);

        solved = false;
        answer.clear();
        vector<string> cur;
        dfs(0, T + 1, cur);
        cout << answer << '\n';
    }
    return 0;
}
