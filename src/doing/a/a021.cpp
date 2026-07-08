#include <bits/stdc++.h>
using namespace std;

string strip(const string &s) {
    size_t i = 0;
    while (i < s.size() && s[i] == '0') i++;
    if (i == s.size()) return "0";
    return s.substr(i);
}

string addStr(string a, string b) {
    a = strip(a); b = strip(b);
    if (a.size() < b.size()) swap(a, b);
    string r(a.size() + 1, '0');
    int carry = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        int av = a[a.size() - 1 - i] - '0';
        int bv = i < (int)b.size() ? b[b.size() - 1 - i] - '0' : 0;
        int s = av + bv + carry;
        r[r.size() - 1 - i] = char('0' + (s % 10));
        carry = s / 10;
    }
    if (carry) r[0] = char('0' + carry);
    else r.erase(r.begin());
    return r;
}

string subStr(string a, string b) {
    a = strip(a); b = strip(b);
    int cmp = (int)a.size() - (int)b.size();
    if (cmp == 0) cmp = (a < b) ? -1 : (a == b ? 0 : 1);
    bool neg = cmp < 0;
    if (neg) swap(a, b);
    string r(a.size(), '0');
    int borrow = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        int av = a[a.size() - 1 - i] - '0' - borrow;
        int bv = i < (int)b.size() ? b[b.size() - 1 - i] - '0' : 0;
        if (av < bv) { av += 10; borrow = 1; } else borrow = 0;
        r[r.size() - 1 - i] = char('0' + (av - bv));
    }
    return strip(r);
}

string mulStr(const string &a, const string &b) {
    string x = strip(a), y = strip(b);
    if (x == "0" || y == "0") return "0";
    vector<int> r(x.size() + y.size(), 0);
    for (int i = (int)x.size() - 1; i >= 0; i--) {
        for (int j = (int)y.size() - 1; j >= 0; j--) {
            int p = (x[i] - '0') * (y[j] - '0');
            int lo = i + j;
            int hi = i + j + 1;
            int sum = p + r[hi];
            r[hi] = sum % 10;
            r[lo] += sum / 10;
        }
    }
    string out;
    int i = 0;
    while (i < (int)r.size() && r[i] == 0) i++;
    for (; i < (int)r.size(); i++) out.push_back(char('0' + r[i]));
    return out;
}

int cmpMag(const string &a, const string &b) {
    if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
    if (a == b) return 0;
    return a < b ? -1 : 1;
}

string divStr(string a, string b) {
    a = strip(a); b = strip(b);
    if (b == "0") return "0";
    if (cmpMag(a, b) < 0) return "0";
    string q;
    string cur;
    for (char c : a) {
        cur.push_back(c);
        cur = strip(cur);
        if (cmpMag(cur, b) < 0) { q.push_back('0'); continue; }
        int lo = 0, hi = 10;
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (cmpMag(mulStr(b, to_string(mid)), cur) <= 0) lo = mid;
            else hi = mid - 1;
        }
        q.push_back(char('0' + lo));
        cur = subStr(cur, mulStr(b, to_string(lo)));
    }
    return strip(q);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string A, op, B;
    while (cin >> A >> op >> B) {
        if (op == "+") cout << addStr(A, B) << "\n";
        else if (op == "-") cout << subStr(A, B) << "\n";
        else if (op == "*") cout << mulStr(A, B) << "\n";
        else if (op == "/") cout << divStr(A, B) << "\n";
    }
    return 0;
}
