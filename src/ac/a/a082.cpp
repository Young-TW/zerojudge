#include <bits/stdc++.h>
using namespace std;

/*
 * a082 - NOI2000 算符破译
 * 13 ancient symbols a..m map bijectively to modern {0..9, +, *, =}.
 * Each equation line has exactly one '='; both sides evaluate equal
 * (decimal, '*' before '+', no leading zero on multi-digit numbers).
 * Output every mapping that is the SAME in every valid assignment,
 * sorted by ancient symbol. If no assignment works -> "noway".
 */

int N;
vector<string> raw;

int eqSym, plusSym, starSym;          // ancient symbol indices for = + *
bool cantZero[13];                    // symbol cannot be digit 0 (leading of multi-digit number)
int val[13];                          // assigned digit for a digit-symbol, -1 unknown
bool usedDigit[10];
bool possible[13][13];                // possible[ancient][modern] seen in some valid solution
bool anySolution;                     // at least one valid assignment exists

struct Number { vector<int> sym; };
struct Term   { vector<Number> nums; };
struct Expr   { vector<Term> terms; };
struct Equation { Expr left, right; };
vector<Equation> eqs;

inline char modernChar(int id) {
    if (id < 10) return char('0' + id);
    if (id == 10) return '+';
    if (id == 11) return '*';
    return '=';
}

inline bool isOp(int s) { return s == eqSym || s == plusSym || s == starSym; }

/* structural validity of a line under current operator interpretation */
bool structuralOK(const string &line) {
    int len = (int)line.size();
    int eqCnt = 0;
    for (int i = 0; i < len; ++i) {
        int s = line[i] - 'a';
        if (s == eqSym) ++eqCnt;
        bool op = isOp(s);
        if ((i == 0 || i == len - 1) && op) return false;   // no leading/trailing operator
        if (i > 0) {
            int prev = line[i - 1] - 'a';
            if (isOp(prev) && op) return false;             // no two adjacent operators
        }
    }
    return eqCnt == 1;
}

void parseSide(const string &side, Expr &expr) {
    expr.terms.clear();
    Term curTerm; Number curNum;
    auto flushNum = [&]() {
        if (!curNum.sym.empty()) { curTerm.nums.push_back(curNum); curNum.sym.clear(); }
    };
    for (char ch : side) {
        int s = ch - 'a';
        if (s == plusSym) { flushNum(); expr.terms.push_back(curTerm); curTerm.nums.clear(); }
        else if (s == starSym) { flushNum(); }
        else curNum.sym.push_back(s);
    }
    flushNum();
    expr.terms.push_back(curTerm);
}

void parseLine(const string &line) {
    int pos = -1;
    for (int i = 0; i < (int)line.size(); ++i)
        if (line[i] - 'a' == eqSym) { pos = i; break; }
    Equation e;
    parseSide(line.substr(0, pos), e.left);
    parseSide(line.substr(pos + 1), e.right);
    eqs.push_back(e);
}

/* ---- interval bounds for pruning ---- */
void numberBound(const Number &num, long long &mn, long long &mx) {
    mn = 0; mx = 0;
    int len = (int)num.sym.size();
    for (int i = 0; i < len; ++i) {
        int s = num.sym[i];
        int lo, hi;
        if (val[s] != -1) lo = hi = val[s];
        else { lo = (cantZero[s] && i == 0) ? 1 : 0; hi = 9; }
        mn = mn * 10 + lo;
        mx = mx * 10 + hi;
    }
}
void termBound(const Term &t, long long &mn, long long &mx) {
    mn = 1; mx = 1;
    for (const Number &num : t.nums) { long long a, b; numberBound(num, a, b); mn *= a; mx *= b; }
}
void exprBound(const Expr &ex, long long &mn, long long &mx) {
    mn = 0; mx = 0;
    for (const Term &tr : ex.terms) { long long a, b; termBound(tr, a, b); mn += a; mx += b; }
}
bool feasible() {
    for (const Equation &e : eqs) {
        long long Lmn, Lmx, Rmn, Rmx;
        exprBound(e.left, Lmn, Lmx);
        exprBound(e.right, Rmn, Rmx);
        if (Lmx < Rmn || Rmx < Lmn) return false;
    }
    return true;
}

/* ---- exact evaluation (all appearing digit-symbols assigned) ---- */
long long numberValue(const Number &num) {
    long long v = 0;
    for (int s : num.sym) v = v * 10 + val[s];
    return v;
}
long long termValue(const Term &t) {
    long long p = 1;
    for (const Number &num : t.nums) p *= numberValue(num);
    return p;
}
long long exprValue(const Expr &ex) {
    long long s = 0;
    for (const Term &tr : ex.terms) s += termValue(tr);
    return s;
}
bool allEqual() {
    for (const Equation &e : eqs)
        if (exprValue(e.left) != exprValue(e.right)) return false;
    return true;
}

vector<int> digitSymbols;             // appearing digit-symbols (to be permuted)
vector<int> nonAppearing;             // digit-symbols not appearing in any number

void recordSolution() {
    anySolution = true;
    possible[eqSym][12] = true;
    possible[plusSym][10] = true;
    possible[starSym][11] = true;
    for (int s : digitSymbols) possible[s][val[s]] = true;
    // non-appearing digit-symbols can take any leftover digit freely
    if (!nonAppearing.empty()) {
        for (int d = 0; d <= 9; ++d)
            if (!usedDigit[d])
                for (int s : nonAppearing) possible[s][d] = true;
    }
}

void dfs(int idx) {
    if (idx == (int)digitSymbols.size()) {
        if (allEqual()) recordSolution();
        return;
    }
    int sym = digitSymbols[idx];
    for (int d = 0; d <= 9; ++d) {
        if (usedDigit[d]) continue;
        if (d == 0 && cantZero[sym]) continue;
        val[sym] = d; usedDigit[d] = true;
        if (feasible()) dfs(idx + 1);
        val[sym] = -1; usedDigit[d] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (!(cin >> N)) return 0;
    raw.resize(N);
    for (int i = 0; i < N; ++i) cin >> raw[i];

    // candidates for '=' : appears exactly once in every line
    vector<int> eqCandidates;
    for (int s = 0; s < 13; ++s) {
        bool ok = true;
        for (int i = 0; i < N && ok; ++i) {
            int cnt = 0;
            for (char c : raw[i]) if (c - 'a' == s) ++cnt;
            if (cnt != 1) ok = false;
        }
        if (ok) eqCandidates.push_back(s);
    }

    memset(possible, 0, sizeof(possible));
    anySolution = false;

    for (int eq : eqCandidates) {
        eqSym = eq;
        for (int plus = 0; plus < 13; ++plus) if (plus != eqSym) {
            plusSym = plus;
            for (int star = 0; star < 13; ++star) if (star != eqSym && star != plusSym) {
                starSym = star;

                bool allStruct = true;
                for (const string &ln : raw)
                    if (!structuralOK(ln)) { allStruct = false; break; }
                if (!allStruct) continue;

                // parse; compute cantZero and appearing digit-symbols
                eqs.clear();
                fill(cantZero, cantZero + 13, false);
                bool appear[13]; fill(appear, appear + 13, false);
                for (const string &ln : raw) parseLine(ln);
                for (const Equation &e : eqs) {
                    for (const Expr *ex : {&e.left, &e.right})
                        for (const Term &t : ex->terms)
                            for (const Number &num : t.nums) {
                                if (num.sym.size() >= 2) cantZero[num.sym[0]] = true;
                                for (int s : num.sym) appear[s] = true;
                            }
                }

                // frequency for ordering (better pruning)
                int freq[13]; fill(freq, freq + 13, 0);
                for (const Equation &e : eqs)
                    for (const Expr *ex : {&e.left, &e.right})
                        for (const Term &t : ex->terms)
                            for (const Number &num : t.nums)
                                for (int s : num.sym) ++freq[s];

                digitSymbols.clear();
                nonAppearing.clear();
                for (int s = 0; s < 13; ++s) {
                    if (s == eqSym || s == plusSym || s == starSym) continue;
                    if (appear[s]) digitSymbols.push_back(s);
                    else nonAppearing.push_back(s);
                }
                sort(digitSymbols.begin(), digitSymbols.end(),
                     [&](int a, int b) { return freq[a] > freq[b]; });

                fill(val, val + 13, -1);
                fill(usedDigit, usedDigit + 10, false);
                dfs(0);
            }
        }
    }

    if (!anySolution) { cout << "noway\n"; return 0; }

    for (int s = 0; s < 13; ++s) {
        int cnt = 0, m = -1;
        for (int j = 0; j < 13; ++j) if (possible[s][j]) { ++cnt; m = j; }
        if (cnt == 1) cout << char('a' + s) << modernChar(m) << "\n";
    }
    return 0;
}
