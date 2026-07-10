#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <functional>
#include <numeric>
using namespace std;

static const int BASE = 10000;

struct BigInt {
    vector<int> mag;
    bool neg;

    BigInt() : neg(false) { mag.push_back(0); }

    bool isZero() const { return mag.size() == 1 && mag[0] == 0; }

    void normalize() {
        while (mag.size() > 1 && mag.back() == 0) mag.pop_back();
        if (isZero()) neg = false;
    }

    int cmpMag(const BigInt& o) const {
        if (mag.size() != o.mag.size()) return mag.size() < o.mag.size() ? -1 : 1;
        for (int i = (int)mag.size() - 1; i >= 0; i--)
            if (mag[i] != o.mag[i]) return mag[i] < o.mag[i] ? -1 : 1;
        return 0;
    }

    static vector<int> addMag(const vector<int>& a, const vector<int>& b) {
        vector<int> r;
        int carry = 0;
        size_t n = max(a.size(), b.size());
        r.reserve(n + 1);
        for (size_t i = 0; i < n; i++) {
            int s = carry;
            if (i < a.size()) s += a[i];
            if (i < b.size()) s += b[i];
            r.push_back(s % BASE);
            carry = s / BASE;
        }
        if (carry) r.push_back(carry);
        return r;
    }

    static vector<int> subMag(const vector<int>& a, const vector<int>& b) {
        vector<int> r;
        int borrow = 0;
        r.reserve(a.size());
        for (size_t i = 0; i < a.size(); i++) {
            int d = a[i] - borrow - (i < b.size() ? b[i] : 0);
            if (d < 0) { d += BASE; borrow = 1; } else borrow = 0;
            r.push_back(d);
        }
        while (r.size() > 1 && r.back() == 0) r.pop_back();
        return r;
    }

    BigInt operator+(const BigInt& o) const {
        BigInt r;
        if (neg == o.neg) {
            r.mag = addMag(mag, o.mag);
            r.neg = neg;
        } else {
            int c = cmpMag(o);
            if (c == 0) { r.mag.clear(); r.mag.push_back(0); r.neg = false; return r; }
            if (c > 0) { r.mag = subMag(mag, o.mag); r.neg = neg; }
            else { r.mag = subMag(o.mag, mag); r.neg = o.neg; }
        }
        r.normalize();
        return r;
    }

    BigInt operator-() const {
        BigInt r = *this;
        if (!r.isZero()) r.neg = !r.neg;
        return r;
    }

    BigInt operator-(const BigInt& o) const { return *this + (-o); }

    BigInt operator*(const BigInt& o) const {
        BigInt r;
        if (isZero() || o.isZero()) { r.mag.clear(); r.mag.push_back(0); r.neg = false; return r; }
        r.mag.assign(mag.size() + o.mag.size(), 0);
        for (size_t i = 0; i < mag.size(); i++) {
            long long carry = 0;
            for (size_t j = 0; j < o.mag.size(); j++) {
                long long cur = (long long)mag[i] * o.mag[j] + r.mag[i + j] + carry;
                r.mag[i + j] = (int)(cur % BASE);
                carry = cur / BASE;
            }
            r.mag[i + o.mag.size()] += (int)carry;
        }
        r.neg = (neg != o.neg);
        r.normalize();
        return r;
    }

    BigInt mulSmall(int x) const {
        BigInt r;
        if (x == 0 || isZero()) { r.mag.clear(); r.mag.push_back(0); r.neg = false; return r; }
        r.neg = neg;
        r.mag.clear();
        r.mag.reserve(mag.size() + 2);
        int carry = 0;
        for (size_t i = 0; i < mag.size(); i++) {
            long long cur = (long long)mag[i] * x + carry;
            r.mag.push_back((int)(cur % BASE));
            carry = (int)(cur / BASE);
        }
        while (carry) { r.mag.push_back(carry % BASE); carry /= BASE; }
        r.normalize();
        return r;
    }

    BigInt addSmall(int x) const {
        if (x == 0) return *this;
        BigInt r;
        r.neg = neg;
        r.mag = mag;
        int carry = x;
        for (size_t i = 0; i < r.mag.size() && carry; i++) {
            int s = r.mag[i] + carry;
            r.mag[i] = s % BASE;
            carry = s / BASE;
        }
        while (carry) { r.mag.push_back(carry % BASE); carry /= BASE; }
        r.normalize();
        return r;
    }

    BigInt divmodSmall(int x, int& rem) const {
        BigInt r;
        r.neg = neg;
        r.mag.clear();
        r.mag.reserve(mag.size());
        rem = 0;
        for (int i = (int)mag.size() - 1; i >= 0; i--) {
            long long cur = (long long)rem * BASE + mag[i];
            r.mag.push_back((int)(cur / x));
            rem = (int)(cur % x);
        }
        reverse(r.mag.begin(), r.mag.end());
        r.normalize();
        return r;
    }

    string toBase(int b) const {
        if (isZero()) return "0";
        string out;
        BigInt cur = *this;
        bool negative = cur.neg;
        cur.neg = false;
        while (!cur.isZero()) {
            int rem;
            cur = cur.divmodSmall(b, rem);
            char c = (rem < 10) ? (char)('0' + rem) : (char)('a' + rem - 10);
            out = c + out;
        }
        if (negative) out = "-" + out;
        return out;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string line;
    while (getline(cin, line)) {
        while (!line.empty() && (line.back() == '\r' || line.back() == '\n'))
            line.pop_back();
        if (line.empty()) continue;

        size_t eq = line.find('=');
        if (eq == string::npos) continue;
        string expr = line.substr(0, eq);
        string after = line.substr(eq + 1);

        int outBase = 0;
        for (size_t i = 0; i < after.size(); i++) {
            if (after[i] >= '0' && after[i] <= '9')
                outBase = outBase * 10 + (after[i] - '0');
        }

        vector<BigInt> values;
        vector<char> ops;

        size_t i = 0;
        bool negateNext = false;
        if (i < expr.size() && expr[i] == '-') { negateNext = true; i++; }
        else if (i < expr.size() && expr[i] == '+') { i++; }

        while (i < expr.size()) {
            string digits;
            while (i < expr.size() && expr[i] != '^' && expr[i] != '+' &&
                   expr[i] != '-' && expr[i] != '*') {
                digits += expr[i];
                i++;
            }
            int numBase = 0;
            if (i < expr.size() && expr[i] == '^') {
                i++;
                while (i < expr.size() && expr[i] >= '0' && expr[i] <= '9') {
                    numBase = numBase * 10 + (expr[i] - '0');
                    i++;
                }
            }
            BigInt v;
            for (char c : digits) {
                int d = (c >= '0' && c <= '9') ? (c - '0') : (c - 'a' + 10);
                v = v.mulSmall(numBase).addSmall(d);
            }
            if (negateNext) { v = -v; negateNext = false; }
            values.push_back(v);

            if (i < expr.size() && (expr[i] == '+' || expr[i] == '-' || expr[i] == '*')) {
                ops.push_back(expr[i]);
                i++;
                if (i < expr.size() && expr[i] == '-') { negateNext = true; i++; }
                else if (i < expr.size() && expr[i] == '+') { i++; }
            }
        }

        if (values.empty()) continue;

        vector<BigInt> vals2;
        vector<char> ops2;
        vals2.push_back(values[0]);
        for (size_t k = 0; k < ops.size(); k++) {
            if (ops[k] == '*') {
                vals2.back() = vals2.back() * values[k + 1];
            } else {
                vals2.push_back(values[k + 1]);
                ops2.push_back(ops[k]);
            }
        }

        BigInt result = vals2[0];
        for (size_t k = 0; k < ops2.size(); k++) {
            if (ops2[k] == '+') result = result + vals2[k + 1];
            else result = result - vals2[k + 1];
        }

        cout << result.toBase(outBase) << "^" << outBase << "\n";
    }
    return 0;
}
